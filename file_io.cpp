#include "file_io.h"

#include <algorithm>  // std::remove
#include <fstream>    // std::istream, std::ostream
#include <sstream>    // std::stringstream

// in "file_io.h"
// #include <exception>
// #include <list>
// #include <string>
// #include <vector>

namespace KaparooFileIO {

//////////////////////////////////
// FileHandler Member Functions //
//////////////////////////////////

bool FileHandler::isFileExist(std::string _path) const {
    if (_path.empty())
        _path = this->path;
    std::ifstream targetFile(_path);
    return (targetFile.is_open()) ? true : false;
}

bool FileHandler::setFilePath(const std::string& _path) noexcept {
    if (_path.empty())
        return false;
    this->path = _path;
    return true;
}

// content_t: std::vector<std::string>
// TODO: Change return type from 'conent_t' to 'pointer of content_t'
void FileHandler::readContent(content_t& content_buffer) const {
    if (!this->isFileExist())
        throw NonExistentInputFile(this->path);
    std::ifstream inputFile{this->path};
    std::string line_buffer{};
    while (std::getline(inputFile, line_buffer))
        content_buffer.push_back(line_buffer);
    inputFile.close();
    if (content_buffer.empty())
        throw EmptyInputContent(this->path);
}

void FileHandler::saveContent(const content_t& content, const std::string& _path, const bool overwrite_enable) const {
    if (content.empty())
        throw EmptyOutputContent();
    if (_path.empty())
        throw EmptyOutputPath();
    if (this->isFileExist(_path) && !overwrite_enable)
        throw ExistentOutputFile(_path);
    std::ofstream outputFile(_path);
    for (auto& line : content)
        outputFile << line << '\n';
}

void FileHandler::saveContent(const content_list_t& content, const std::string& _path, const bool overwrite_enable) const {
    if (content.empty())
        throw EmptyOutputContent();
    if (_path.empty())
        throw EmptyOutputPath();
    if (this->isFileExist(_path) && !overwrite_enable)
        throw ExistentOutputFile(_path);
    std::ofstream outputFile(_path);
    for (auto& line : content)
        outputFile << line << '\n';
}

//////////////////////
// Helper Functions //
//////////////////////

void splitLine(const std::string& line, content_t& splited_line, const char delimeter, const char ignore_token, const bool ignore_empty) {
    if (!splited_line.empty())
        splited_line.clear();
    std::stringstream stream{line};
    std::string buffer{};
    while (std::getline(stream, buffer, delimeter)) {
        buffer.erase(std::remove(buffer.begin(), buffer.end(), ignore_token), buffer.end());
        if (buffer.empty()) {
            if (!ignore_empty)
                splited_line.push_back(buffer);
        } else
            splited_line.push_back(buffer);
    }
}

void changeExtension(const std::string& file_path, std::string& new_path, const std::string& extension) {
    // TODO: make isValidPath() & isValidExtension(), replace this funcation to use regex
    const std::string::size_type& pure_path_end{file_path.find_last_of(".")};
    const std::string::size_type& pure_extension_start{extension.find_first_not_of(".")};
    new_path = file_path.substr(0, pure_path_end) + '.' + extension.substr(pure_extension_start, extension.size());
}

}  // namespace KaparooFileIO