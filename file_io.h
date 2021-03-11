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
    FileHandler(const char* _path) noexcept : file_path(static_cast<std::string>(_path)){};
    FileHandler(std::string _path) noexcept : file_path(_path){};
    virtual ~FileHandler(){};

    bool isFileExist() const;

    bool read(content_t& content) const;
    bool save(const content_t& content, const std::string& extension = "") const;
};
}  // namespace KaparooFileIO

#endif