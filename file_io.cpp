#include "file_io.h"

#include <fstream>
#include <sstream>

namespace KaparooFileIO {

content_t splitLine(const std::string& line, const char delimeter /*=' '*/, bool ignore_empty /*=true*/) {
    content_t content;
    std::stringstream stream(line);
    std::string buffer;
    while (std::getline(stream, buffer, delimeter)) {
        if (buffer.empty()) {
            if (!ignore_empty)
                content.push_back(buffer);
        } else {
            content.push_back(buffer);
        }
    }
    return content;
}

bool FileHandler::setFilePath(const char _path[]) {
    std::string new_path(static_cast<std::string>(_path));
    return this->setFilePath(new_path);
}

bool FileHandler::setFilePath(std::string _path) {
    if (_path.empty())
        return false;
    file_path = _path;
    return true;
}

std::string FileHandler::getFilePath() const {
    return file_path;
}

bool FileHandler::isEmptyPath() const {
    return file_path.empty();
}

bool FileHandler::isFileExist(std::string _path /*=""*/) const {
    if (_path.empty()) _path = file_path;
    std::ifstream targetFile(_path);
    return (targetFile.is_open()) ? true : false;
}

// content_t: std::vector<std::string>
content_t FileHandler::read() const {
    content_t content;
    if ((!isEmptyPath()) && isFileExist()) {
        std::ifstream inputFile(file_path);
        std::string buffer;
        while (std::getline(inputFile, buffer))
            content.push_back(buffer);
    }
    return content;
}

bool FileHandler::save(const content_t& content, std::string save_path, bool overwrite_enable /*=true*/) const {
    if (save_path.empty())
        return false;

    if (isFileExist(save_path) && !overwrite_enable)
        return false;

    std::ofstream outputFile(save_path);
    for (const auto& line : content)
        outputFile << line << '\n';

    return true;
}

}  // namespace KaparooFileIO