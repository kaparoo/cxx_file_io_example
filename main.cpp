#include <iostream>
#include <memory>  // std::unique_ptr
#include <string>

#include "file_io.h"

void displayContent(const KaparooFileIO::content_t& content) {
    std::size_t line_num(0U);
    for (auto& line : content) {
        std::cout << "[LINE: " << line_num << "] " << line << std::endl;
        ++line_num;
    }
    std::cout << std::endl;
}

void displaySplitedContent(const std::vector<KaparooFileIO::content_t>& splited_content) {
    std::size_t line_num(0U);
    for (auto& line : splited_content) {
        std::cout << "[LINE: " << line_num << "] ";
        for (const auto& word : line)
            std::cout << "[" << word << "], ";
        std::cout << std::endl;
        ++line_num;
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc == 2) {
        KaparooFileIO::FileHandler handler(argv[1]);  // handler(static_cast<std::string>(argv[1]));
        try {
            std::unique_ptr<KaparooFileIO::content_t> content{new KaparooFileIO::content_t};
            handler.readContent(*content);  // exception: FileNotFound or EmptyFile

            displayContent(*content);

            std::vector<KaparooFileIO::content_t> splited_content{};
            KaparooFileIO::content_t splited_line{};
            for (const auto& line : *content) {
                KaparooFileIO::splitLine(line, splited_line, ',', ' ');  // split by ',', remove ' '
                splited_content.push_back(splited_line);
            }

            displaySplitedContent(splited_content);

            const std::string save_path{"save.txt"};
            handler.saveContent(*content, save_path, true);  // true: overwrite file
        } catch (KaparooFileIO::FileIOException& e) {
            std::cout << e.what() << std::endl;
            return EXIT_FAILURE;
        }
    } else {
        if (argc == 1) {
            std::cout << "[ERROR] Need file!" << std::endl;
        } else {
            std::cout << "[ERROR] Too many argument!" << std::endl;
        }
    }
    return EXIT_SUCCESS;
}