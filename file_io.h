#pragma once

#ifndef KAPAROO_FILE_IO_H
#define KAPAROO_FILE_IO_H

#include <exception>
#include <list>
#include <string>
#include <vector>

namespace KaparooFileIO {

typedef std::vector<std::string> content_t;
typedef std::list<std::string> content_list_t;

/////////////////
// FileHandler //
/////////////////

class FileHandler final {
   protected:
    std::string path;  // file name with its path

   public:
    FileHandler() noexcept : path(static_cast<std::string>("")) {}
    FileHandler(const std::string& _path) noexcept : path(_path) {}
    FileHandler(const char* _path) noexcept : path(static_cast<std::string>(_path)) {}
    virtual ~FileHandler() {}

    FileHandler(const bool*) = delete;
    FileHandler(const short*) = delete;
    FileHandler(const FileHandler&) = delete;
    FileHandler& operator=(const FileHandler&) = delete;

    bool isEmptyPath() const noexcept { return this->path.empty(); }
    bool isFileExist(std::string _path = "") const;

    bool setFilePath(const std::string& _path) noexcept;
    std::string getFilePath() const noexcept { return this->path; }

    virtual void readContent(content_t& content_buffer) const;

    void saveContent(const content_t& content, const std::string& save_path, const bool overwrite_enable = true) const;
    void saveContent(const content_list_t& content, const std::string& save_path, const bool overwrite_enable = true) const;
};

///////////////////////
// Custom Exceptions //
///////////////////////

class FileIOException {
   protected:
    std::string path;
    std::string message;

   public:
    FileIOException(const std::string& _path = "", const std::string& _msg = "File exception!") noexcept : path(_path), message(_msg) {}
    virtual ~FileIOException() {}

    virtual const std::string what() const noexcept {
        std::string description{"[FILE I/O ERROR] " + message};
        if (!path.empty())
            description += " (path: " + path + ")";
        return description;
    }
};

//////////////////////
// Input Exceptions //
//////////////////////

class NonExistentInputFile final : public FileIOException {
   public:
    NonExistentInputFile(const std::string& _path) noexcept : FileIOException(_path, "Cannot Read Non-Existent File!") {}
    ~NonExistentInputFile() {}
};

class EmptyInputContent final : public FileIOException {
   public:
    EmptyInputContent(const std::string& _path) noexcept : FileIOException(_path, "Cannot Use Empty File!") {}
    ~EmptyInputContent() {}
};

///////////////////////
// Output Exceptions //
///////////////////////

class ExistentOutputFile final : public FileIOException {
   public:
    ExistentOutputFile(const std::string& _path) noexcept : FileIOException(_path, "Cannot Overwrite Already Existed File!") {}
    ~ExistentOutputFile() {}
};

class EmptyOutputPath final : public FileIOException {
   public:
    EmptyOutputPath() noexcept : FileIOException("", "Cannot Save File Without Path!") {}
    ~EmptyOutputPath() {}
};

class EmptyOutputContent final : public FileIOException {
   public:
    EmptyOutputContent() noexcept : FileIOException("", "Cannot Save File Without Content!") {}
    ~EmptyOutputContent() {}
};

//////////////////////
// Helper Functions //
//////////////////////

void splitLine(const std::string& line, content_t& content, const char delimter = ' ', const char ignore_token = ',', const bool ignore_empty = true);

void changeExtension(const std::string& old_path, std::string& new_path, const std::string& extension = "txt");

}  // namespace KaparooFileIO

#endif