#include <cstdlib>
#include <iostream>
#include <string>

#include "file_io.h"

int main(int argc, char* argv[]) {
    if (argc == 2) {
        KaparooFileIO::FileHandler handler(static_cast<std::string>(argv[1]));
        KaparooFileIO::content_t content(handler.read());

        // if (!content.empty()) {
        //     for (const auto& line : content)
        //         std::cout << line << std::endl;
        //     std::cout << "File is loaded!" << std::endl;
        //     std::cout << "----------------FILE SPLIT----------------" << std::endl;
        //     for (const auto& line : content) {
        //         KaparooFileIO::content_t splited_line(KaparooFileIO::splitLine(line));
        //         std::cout << "[BEFORE] " << line << std::endl;
        //         std::cout << "[AFTER] " << std::endl;
        //         for (auto& word : splited_line)
        //             std::cout << word << std::endl;
        //         // std::cout << std::endl;
        //     }
        //     std::cout << "----------------FILE SPLIT----------------" << std::endl;
        // } else {
        if (!content.empty()) {
            std::vector<KaparooFileIO::content_t> raw_token_list;
            for (const auto& line : content) {
                KaparooFileIO::content_t splited_line(KaparooFileIO::splitLine(line));
                raw_token_list.push_back(splited_line);
            }
            unsigned int line_num(0);
            for (const auto& line : raw_token_list) {
                std::cout << "[LINE: " << line_num << "] ";
                for (const auto& raw_token : line)
                    std::cout << raw_token << " ";
                std::cout << std::endl;
                ++line_num;
            }
        } else {
            std::cout << "[ERROR] Empty file or Invalid path!" << std::endl;
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