#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#define PORT 8080
#define BUFFER_SIZE 1024

std::mutex mtx;
std::condition_variable cv;
std::queue<int> clientSockets;

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE];
    read(client_socket, buffer, BUFFER_SIZE);
    std::string request(buffer);

    // Parse request and extract file path
    size_t pos = request.find("GET");
    size_t end_pos = request.find("HTTP");
    std::string file_path = request.substr(pos + 5, end_pos - pos - 6); // Adjusted to remove extra characters

    // Serve static HTML file
    std::ifstream file(file_path);
    if (file.is_open()) {
        std::stringstream response;
        response << "HTTP/1.1 200 OK\r\n";
        response << "Content-Type: text/html\r\n\r\n";
        response << file.rdbuf();
        std::string response_str = response.str();
        send(client_socket, response_str.c_str(), response_str.length(), 0);
    } else {
        std::string not_found_response = "HTTP/1.1 404 Not Found\r\n\r\nFile not found.";
        send(client_socket, not_found_response.c_str(), not_found_response.length(), 0);
    }

    close(client_socket);
}

void worker_thread() {
    while (true) {
        int client_socket;
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [] { return !clientSockets.empty(); });
            client_socket = clientSockets.front();
            clientSockets.pop();
        }
        handle_request(client_socket);
    }
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_length = sizeof(client_address);

    // Create server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        std::cerr << "Error creating server socket." << std::endl;
        return 1;
    }

    // Set server address
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    // Bind server socket
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        std::cerr << "Error binding server socket." << std::endl;
        return 1;
    }

    // Listen for client connections
    if (listen(server_socket, 3) < 0) {
        std::cerr << "Error listening for client connections." << std::endl;
        return 1;
    }

    std::cout << "Server listening on port " << PORT << std::endl;

    // Create worker threads
    std::thread threads[5];
    for (int i = 0; i < 5; ++i) {
        threads[i] = std::thread(worker_thread);
    }

    while (true) {
        // Accept client connection
        client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_length);
        if (client_socket < 0) {
            std::cerr << "Error accepting client connection." << std::endl;
            continue;
        }

        // Add client socket to queue
        {
            std::lock_guard<std::mutex> lock(mtx);
            clientSockets.push(client_socket);
        }
        cv.notify_one();
    }

    // Join worker threads (not reachable in this example)
    for (int i = 0; i < 5; ++i) {
        threads[i].join();
    }

    return 0;
}