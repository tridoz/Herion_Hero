#include "../hpp/HerionFileException.hpp"

#include <stack>


// ================= FileException base =================
HerionException::File::FileException::FileException(
    const std::string& msg,
    const std::string& type,
    const std::string& location
)
    : std::runtime_error(msg),
      type_(type),
      location_(location)
{
    stack_trace_.insert(
        stack_trace_.begin(),
        location + " => " + msg
    );

}

std::vector < std::string > HerionException::File::FileException::GetStackTrace() const {
    return stack_trace_;
}


void HerionException::File::FileException::UpdateStackTrace(const std::string& stack_line) {
    stack_trace_.insert(
    stack_trace_.begin(),
        stack_line
    );

}


// ================= FileNotFoundException =================
HerionException::File::FileNotFoundException::FileNotFoundException(
    const std::string& path,
    const std::string& location
)
    : HerionException::File::FileException("File not found: " + path,
                                           "LOADING",
                                           location)
{}


// ================= FileOpenException =================
HerionException::File::FileOpenException::FileOpenException(
    const std::string& path,
    const std::string& location
)
    : HerionException::File::FileException("Unable to open file: " + path,
                                           "LOADING",
                                           location)
{}


// ================= FileReadException =================
HerionException::File::FileReadException::FileReadException(
    const std::string& path,
    const std::string& location
)
    : HerionException::File::FileException("Unable to read file: " + path,
                                           "LOADING",
                                           location)
{}


// ================= FileWriteException =================
HerionException::File::FileWriteException::FileWriteException(
    const std::string& path,
    const std::string& location
)
    : HerionException::File::FileException("Unable to write file: " + path,
                                           "LOADING",
                                           location)
{}
