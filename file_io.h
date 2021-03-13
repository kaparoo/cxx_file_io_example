#pragma once

#ifndef KAPAROO_FILE_IO_H
#define KAPAROO_FILE_IO_H

#include <exception>
#include <string>
#include <vector>

namespace KaparooFileIO {

typedef std::vector<std::string> content_t;

content_t splitLine(const std::string& line, const char delimter = ' ', bool ignore_empty = true);

std::string changeExtension(std::string file_path = "file", std::string extension = "txt");

enum class file_save_error_t {
    EMPTY_PATH,
    EXIST_FILE
};

class FileException : public std::exception {
   protected:
    std::string file_path;

   public:
    FileException(std::string _path = "") noexcept : file_path(_path) {}
    virtual ~FileException() {}

    virtual const char* what() const noexcept override {
        std::string message("[ERROR] File exception! (path: " + file_path + ")");
        return message.c_str();
    }
};

class FileNotFound final : public FileException {
   public:
    FileNotFound(std::string _path = "") noexcept : FileException(_path) {}
    virtual ~FileNotFound() {}

    virtual const char* what() const noexcept override {
        std::string message("[ERROR] File not found! (path: " + file_path + ")");
        return message.c_str();
    }
};

class EmptyFile final : public FileException {
   public:
    EmptyFile(std::string _path = "") noexcept : FileException(_path) {}
    virtual ~EmptyFile() {}

    virtual const char* what() const noexcept override {
        std::string message("[ERROR] File is empty! (path: " + file_path + ")");
        return message.c_str();
    }
};

class FileHandler {
   protected:
    std::string file_path;

   public:
    FileHandler() noexcept : FileHandler(std::string("")) {}
    FileHandler(std::string _path) noexcept : file_path(_path) {}
    virtual ~FileHandler() {}

    FileHandler(const FileHandler&) = delete;
    FileHandler& operator=(const FileHandler&) = delete;

    bool isEmptyPath() const noexcept { return this->file_path.empty(); }
    bool isFileExist(std::string _path = "") const;

    bool trimFilePath();
    bool setFilePath(std::string _path) noexcept;
    std::string getFilePath() const noexcept { return this->file_path; }

    virtual content_t* readContent() const;
    virtual void saveContent(const content_t& content, std::string save_path, bool overwrite_enable = true) const;
};
}  // namespace KaparooFileIO

#endif