#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // For exit()
#include <cctype>  // For std::isdigit

// Function to compress a string using Run-Length Encoding
std::string compressRLE(const std::string& input) {
    std::string compressed;
    int n = input.length();

    for (int i = 0; i < n; ++i) {
        int count = 1;
        while (i + 1 < n && input[i] == input[i + 1]) {
            ++count;
            ++i;
        }
        compressed += input[i];
        compressed += std::to_string(count);
    }
    return compressed;
}

// Function to decompress a string that was compressed using Run-Length Encoding
std::string decompressRLE(const std::string& input) {
    std::string decompressed;
    int n = input.length();

    for (int i = 0; i < n; ++i) {
        char ch = input[i];
        ++i;

        std::string countStr;
        while (i < n && std::isdigit(input[i])) {
            countStr += input[i++];
        }
        int count = std::stoi(countStr);

        decompressed.append(count, ch);
        --i; // Correct the index after while loop
    }
    return decompressed;
}

// Function to read the content of a file into a string
std::string readFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return content;
}

// Function to write a string content to a file
void writeFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    file << content;
    file.close();
}

// Main function to handle command-line arguments and perform compression or decompression
int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <compress|decompress> <input file> <output file>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string mode = argv[1];
    std::string inputFile = argv[2];
    std::string outputFile = argv[3];

    std::string content = readFile(inputFile);

    if (mode == "compress") {
        std::string compressed = compressRLE(content);
        writeFile(outputFile, compressed);
    } else if (mode == "decompress") {
        std::string decompressed = decompressRLE(content);
        writeFile(outputFile, decompressed);
    } else {
        std::cerr << "Invalid mode. Use 'compress' or 'decompress'." << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}