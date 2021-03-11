#include "file_io.h"

#include <fstream>

namespace KaparooFileIO {

inline bool FileHandler::isFileExist() const {
    std::ifstream targetFile(file_path);
    return (targetFile.is_open()) ? true : false;
}

// content_t: std::vector<std::string>
inline bool FileHandler::read(content_t& content) const {
    if (isFileExist()) {
        content.clear();
        std::ifstream inputFile(file_path);
        std::string buffer;
        while (std::getline(inputFile, buffer))
            content.push_back(buffer);

        return true;
    }
    return false;
}

inline bool FileHandler::save(const content_t& content, const std::string& extension /*=""*/) const {
    std::size_t pos = file_path.find(".");
    std::string new_path(file_path);
    if (pos != std::string::npos)
        new_path = new_path.substr(0, pos);
    new_path = new_path + extension;

    std::ofstream outputFile(new_path);
    for (const auto& line : content)
        outputFile << line << "\n";

    return true;
}

}  // namespace KaparooFileIO