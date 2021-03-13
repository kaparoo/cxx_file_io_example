#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>

#include "file_io.h"

using namespace KaparooFileIO;

void displayContent(const content_t& content) {
    std::size_t line_num(0U);
    for (auto& line : content) {
        std::cout << "[LINE: " << line_num << "] " << line << std::endl;
        ++line_num;
    }
}

void displayContent(const std::vector<content_t>& splited_content) {
    std::size_t line_num(0U);
    for (auto& line : splited_content) {
        std::cout << "[LINE: " << line_num << "] [";
        for (const auto& word : line)
            std::cout << word << " ";
        std::cout << "]" << std::endl;
        ++line_num;
    }
}

int main(int argc, char* argv[]) {
    if (argc == 2) {
        FileHandler handler(argv[1]);  // handler(static_cast<std::string>(argv[1]));
        try {
            content_t* content(handler.readContent());  // exception: FileNotFound or EmptyFile

            displayContent(*content);

            std::vector<content_t> splited_content;
            for (const auto& line : *content) {
                content_t splited_line(splitLine(line));
                splited_content.push_back(splited_line);
            }

            std::cout << std::endl;

            displayContent(splited_content);

            std::string save_path(changeExtension(argv[1], "cpp"));
            try {
                handler.saveContent(*content, save_path, false);
            } catch (file_save_error_t file_save_error) {
                switch (file_save_error) {
                    case file_save_error_t::EXIST_FILE:
                        std::cout << "[ERROR] File is already exist!" << std::endl;
                        std::cout << "Overwrite it? (Y/n)" << std::endl;
                        char c;
                        std::cin >> c;
                        if (c == 'Y' || c == 'y')
                            handler.saveContent(*content, save_path, true);
                        return EXIT_SUCCESS;  // break;
                    case file_save_error_t::EMPTY_PATH:
                        std::cout << "[ERROR] Need a path to save content!" << std::endl;
                        break;
                    default:
                        break;
                }
                return EXIT_FAILURE;
            }
        } catch (KaparooFileIO::FileException& e) {
            std::cout << e.what() << std::endl;
            return EXIT_FAILURE;
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
            return EXIT_FAILURE;
        } catch (...) {
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