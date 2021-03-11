#include <cstdlib>
#include <iostream>
#include <string>

#include "file_io.h"

int main(int argc, char* argv[]) {
    if (argc == 2) {
        KaparooFileIO::FileHandler handler(static_cast<std::string>(argv[1]));
        std::vector<std::string> content;

        handler.read(content);
        for (const auto& line : content) {
            std::cout << line << std::endl;
        }
        handler.save(content, ".c");

    } else {
        if (argc == 1)
            std::cout << "[ERROR] Need file name!" << std::endl;
        else  // argc > 2
            std::cout << "[ERROR] Too many arguments!" << std::endl;
    }

    return EXIT_SUCCESS;
}