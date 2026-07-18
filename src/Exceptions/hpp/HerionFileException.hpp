#pragma once
#include <ctime>
#include <stdexcept>
#include <string>

#pragma once

#if defined(_MSC_VER)
#define HERION_FUNCTION_SIGNATURE __FUNCSIG__
#elif defined(__GNUC__) || defined(__clang__)
#define HERION_FUNCTION_SIGNATURE __PRETTY_FUNCTION__
#else
#define HERION_FUNCTION_SIGNATURE __FUNCTION__
#endif

#define HERION_RESET "\033[0m"

#define HERION_BOLD "\033[1m"

#define HERION_RED "\033[91m"
#define HERION_YELLOW "\033[93m"
#define HERION_CYAN "\033[96m"

#include "../../Utils/hpp/Logger.hpp"

namespace HerionException::File {

    class FileException : public std::runtime_error {
      protected:
        std::string type_;
        std::string location_;

        std::vector<std::string> stack_trace_;
        std::vector<std::string> stack_trace_2;

      public:
        explicit FileException(
            const std::string& msg, const std::string& type = "LOADING", const std::string& location = "UnknownLocation"
        );

        void UpdateStackTrace(const std::string& stack_line);
        [[nodiscard]] std::vector<std::string> GetStackTrace() const;
    };

    class FileNotFoundException final : public FileException {
      public:
        explicit FileNotFoundException(const std::string& path, const std::string& location = "UnknownLocation");
    };

    class FileOpenException final : public FileException {
      public:
        explicit FileOpenException(const std::string& path, const std::string& location = "UnknownLocation");
    };

    class FileReadException final : public FileException {
      public:
        explicit FileReadException(const std::string& path, const std::string& location = "UnknownLocation");
    };

    class FileWriteException final : public FileException {
      public:
        explicit FileWriteException(const std::string& path, const std::string& location = "UnknownLocation");
    };

    class FileMalformedException final : public FileException {
      public:
        explicit FileMalformedException(const std::string& path, const std::string& location = "UnknownLocation");
    };

} // namespace HerionException::File

#define THROW_FILE_NOT_FOUND(path)                                                                                     \
    throw HerionException::File::FileNotFoundException(                                                                \
        std::string(HERION_RED) + HERION_BOLD + (path) + HERION_RESET,                                                 \
        std::string(HERION_CYAN) + HERION_FUNCTION_SIGNATURE + HERION_RESET                                            \
    )

#define THROW_FILE_OPEN(path)                                                                                          \
    throw HerionException::File::FileOpenException(                                                                    \
        std::string(HERION_RED) + HERION_BOLD + (path) + HERION_RESET,                                                 \
        std::string(HERION_CYAN) + HERION_FUNCTION_SIGNATURE + HERION_RESET                                            \
    )

#define THROW_FILE_READ(path)                                                                                          \
    throw HerionException::File::FileReadException(                                                                    \
        std::string(HERION_RED) + HERION_BOLD + (path) + HERION_RESET,                                                 \
        std::string(HERION_CYAN) + HERION_FUNCTION_SIGNATURE + HERION_RESET                                            \
    )

#define THROW_FILE_WRITE(path)                                                                                         \
    throw HerionException::File::FileWriteException(                                                                   \
        std::string(HERION_RED) + HERION_BOLD + (path) + HERION_RESET,                                                 \
        std::string(HERION_CYAN) + HERION_FUNCTION_SIGNATURE + HERION_RESET                                            \
    )

#define THROW_FILE_MALFORMED(path)                                                                                     \
    throw HerionException::File::FileMalformedException(                                                               \
        std::string(HERION_RED) + HERION_BOLD + (path) + HERION_RESET,                                                 \
        std::string(HERION_CYAN) + HERION_FUNCTION_SIGNATURE + HERION_RESET                                            \
    )

#define GET_CONTEXT()                                                                                                  \
    (std::string(HERION_CYAN) + HERION_FUNCTION_SIGNATURE + HERION_RESET + " | " +                                     \
     HERION_YELLOW "Line: " + std::to_string(__LINE__) + HERION_RESET)
