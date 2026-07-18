#include "../hpp/HerionFileException.hpp"

#include <stack>

// ================= FileException base =================
HerionException::File::FileException::FileException(
    const std::string& msg, const std::string& type, const std::string& location
)
    : std::runtime_error(msg), type_(type), location_(location) {
    stack_trace_.insert(stack_trace_.begin(), location + " => " + msg);
}

std::vector<std::string> HerionException::File::FileException::GetStackTrace() const {
    return stack_trace_;
}

void HerionException::File::FileException::UpdateStackTrace(const std::string& stack_line) {
    stack_trace_.insert(stack_trace_.begin(), stack_line);
}

// ================= FileNotFoundException =================
HerionException::File::FileNotFoundException::FileNotFoundException(
    const std::string& path, const std::string& location
)
    : HerionException::File::FileException("\033[91mFile not found\033[0m: " + path, "FILE", location) {
}

// ================= FileOpenException =================
HerionException::File::FileOpenException::FileOpenException(const std::string& path, const std::string& location)
    : HerionException::File::FileException("\033[91mUnable to open file\033[0m: " + path, "OPENING", location) {
}

// ================= FileReadException =================
HerionException::File::FileReadException::FileReadException(const std::string& path, const std::string& location)
    : HerionException::File::FileException("\033[91mUnable to read file\033[0m: " + path, "READING", location) {
}

// ================= FileWriteException =================
HerionException::File::FileWriteException::FileWriteException(const std::string& path, const std::string& location)
    : HerionException::File::FileException("\033[91mUnable to write file\033[0m: " + path, "WRITING", location) {
}

HerionException::File::FileMalformedException::FileMalformedException(
    const std::string& path, const std::string& location
)
    : HerionException::File::FileException("\033[91mMalformed file\033[0m: " + path, "PARSING", location) {
}
