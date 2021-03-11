#include <cstdlib>
#include <iostream>
#include <string>

#include "file_io.h"

int main(int argc, char* argv[]) {
    if (argc == 2) {
        KaparooFileIO::FileHandler handler(static_cast<std::string>(argv[1]));
        std::vector<std::string> content;

        if (handler.read(content)) {
            for (const auto& line : content)
                std::cout << line << std::endl;
            std::cout << "File is loaded!" << std::endl;
        } else {
            std::cout << "[ERROR] Empty or Invalid file path!" << std::endl;
            return EXIT_FAILURE;
        }
        if (handler.save(content, "test2.txt", true))
            std::cout << "File is saved!" << std::endl;
        else {
            std::cout << "[ERROR] File is already exist!" << std::endl;
            return EXIT_FAILURE;
        }
    } else {
        if (argc == 1)
            std::cout << "[ERROR] Need file name!" << std::endl;
        else  // argc > 2
            std::cout << "[ERROR] Too many arguments!" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}