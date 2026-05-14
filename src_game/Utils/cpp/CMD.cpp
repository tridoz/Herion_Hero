//
// Created by tridoz on 14/05/26.
//

#include "../hpp/CMD.hpp"

std::string CMD::exec( const std::string& command ) {
    std::array< char, 128> buffer;
    std::string result;

    FILE* pipe = popen(command.c_str(), "r");

    if ( pipe == nullptr ) {
        return "";
    }

    while ( fgets( buffer.data(), buffer.size(), pipe ) != nullptr ) {
        result += buffer.data();
    }

    return result;
}

#include <vector>
#include <string>
#include <array>
#include <cstdio>

std::vector<std::string> CMD::multiline_exec(const std::string& command) {
    std::array<char, 128> buffer;
    std::string result;

    FILE* pipe = popen(command.c_str(), "r");
    if (pipe == nullptr) {
        return {};
    }

    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }

    pclose(pipe);

    std::vector<std::string> lines;
    std::string current;

    for (char c : result) {
        if (c == '\n') {
            if (!current.empty() && current.back() == '\r')
                current.pop_back(); // remove \r (Windows-style)

            lines.push_back(current);
            current.clear();
        } else {
            current += c;
        }
    }

    // ultima linea (se non termina con \n)
    if (!current.empty()) {
        if (!current.empty() && current.back() == '\r')
            current.pop_back();

        lines.push_back(current);
    }

    return lines;
}