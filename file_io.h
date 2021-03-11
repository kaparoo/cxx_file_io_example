#pragma once

#ifndef KAPAROO_FILE_IO_H
#define KAPAROO_FILE_IO_H

#include <string>
#include <vector>

namespace KaparooFileIO {

typedef std::vector<std::string> content_t;

class FileHandler {
   protected:
    std::string file_path;

   public:
    FileHandler() noexcept : file_path(""){};
    FileHandler(const char _path[]) noexcept : file_path(static_cast<std::string>(_path)){};
    FileHandler(std::string _path) noexcept : file_path(_path){};
    virtual ~FileHandler(){};

    FileHandler(const FileHandler&) = delete;
    FileHandler& operator=(const FileHandler&) = delete;

    bool setFilePath(const char _path[]);
    bool setFilePath(std::string _path);
    std::string getFilePath() const;

    bool isEmptyPath() const;
    bool isFileExist(std::string _path = "") const;

    bool read(content_t& content) const;
    bool save(const content_t& content, std::string save_path, bool overwrite_enable = true) const;
};
}  // namespace KaparooFileIO

#endif