#pragma once
#include <stdexcept>
#include <string>
#include <ctime>


#include "../../Utils/hpp/Logger.hpp"

namespace HerionException::File {

    class FileException : public std::runtime_error {
    protected:
        std::string type_;
        std::string location_;

        std::vector < std::string > stack_trace_;
        std::vector < std::string > stack_trace_2;


    public:
        explicit FileException(
            const std::string& msg,
            const std::string& type = "LOADING",
            const std::string& location = "UnknownLocation"
        );

        void UpdateStackTrace( const std::string& stack_line );
        [[nodiscard]] std::vector< std::string > GetStackTrace() const;

    };

    class FileNotFoundException final : public FileException {
    public:
        explicit FileNotFoundException(
            const std::string& path,
            const std::string& location = "UnknownLocation"
        );
    };

    class FileOpenException final : public FileException {
    public:
        explicit FileOpenException(
            const std::string& path,
            const std::string& location = "UnknownLocation"
        );
    };

    class FileReadException final : public FileException {
    public:
        explicit FileReadException(
            const std::string& path,
            const std::string& location = "UnknownLocation"
        );
    };

    class FileWriteException final : public FileException {
    public:
        explicit FileWriteException(
            const std::string& path,
            const std::string& location = "UnknownLocation"
        );
    };

    class FileMalformedException final : public FileException {
    public:
        explicit FileMalformedException (
            const std::string& path,
            const std::string& location = "UnknownLocation"
            );
    };

}

#define THROW_FILE_NOT_FOUND(path) \
    throw  HerionException::File::FileNotFoundException( "\033[1m" + path + "\033[22m", __PRETTY_FUNCTION__)

#define THROW_FILE_OPEN(path) \
    throw  HerionException::File::FileOpenException( "\033[1m" + path + "\033[22m", __PRETTY_FUNCTION__)

#define THROW_FILE_READ(path) \
    throw  HerionException::File::FileReadException( "\033[1m" + path + "\033[22m", __PRETTY_FUNCTION__)

#define THROW_FILE_WRITE(path) \
    throw  HerionException::File::FileWriteException( "\033[1m" + path + "\033[22m", __PRETTY_FUNCTION__)

#define THROW_FILE_MALFORMED(path) \
    throw HerionException::File::FileMalformedException( "\033[1m" + path + "\033[22m", __PRETTY_FUNCTION__)

#define GET_CONTEXT() (  std::string(__PRETTY_FUNCTION__) + " at line=> " + std::to_string(__LINE__) )
