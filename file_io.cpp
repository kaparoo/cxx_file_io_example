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

std::string changeExtension(std::string file_path /*="file"*/, std::string extension /*="txt"*/) {
    std::string::size_type dot_pos = file_path.find(".");
    if (dot_pos != std::string::npos) {
        return file_path.substr(0, dot_pos) + '.' + extension;
    }
    return file_path + '.' + extension;
}

// FileHandler member functions
bool FileHandler::isFileExist(std::string _path /*=""*/) const {
    if (_path.empty()) _path = file_path;
    std::ifstream targetFile(_path);
    return (targetFile.is_open()) ? true : false;
}

bool FileHandler::setFilePath(std::string _path) noexcept {
    if (_path.empty())
        return false;
    this->file_path = _path;
    return true;
}

// content_t: std::vector<std::string>
content_t* FileHandler::readContent() const {
    if (!isFileExist())
        throw FileNotFound(this->file_path);

    content_t* content = new content_t;
    std::ifstream inputFile(this->file_path);
    std::string buffer;

    while (std::getline(inputFile, buffer))
        content->push_back(buffer);

    inputFile.close();

    if (content->empty())
        throw EmptyFile(this->file_path);

    return content;
}

void FileHandler::saveContent(const content_t& content, std::string save_path, bool overwrite_enable /*=true*/) const {
    if (save_path.empty())
        throw file_save_error_t::EMPTY_PATH;

    if (isFileExist(save_path) && !overwrite_enable)
        throw file_save_error_t::EXIST_FILE;

    std::ofstream outputFile(save_path);
    for (auto& line : content)
        outputFile << line << '\n';
}

}  // namespace KaparooFileIO