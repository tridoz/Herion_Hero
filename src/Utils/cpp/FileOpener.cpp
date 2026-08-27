//
// Created by trida on 1/4/26.
//

#include "../hpp/FileOpener.hpp"

#include <filesystem>

auto FileOpener::OpenFileInput(std::ifstream& in, const std::string& filepath) -> void {
    in.open(filepath, std::ios::in);

    if (!in.is_open()) {
        in.open("../" + filepath, std::ios::in);
        if (!in.is_open()) {
            if (!std::filesystem::exists("../" + filepath)) {
                THROW_FILE_NOT_FOUND(filepath + " nor " + " ../" + filepath);
            } else {
                THROW_FILE_OPEN((filepath + " nor " + " ../" + filepath));
            }
        }
    }

    in.exceptions(std::ifstream::badbit);
}

auto FileOpener::OpenFileOutput(std::ofstream& out, const std::string& filepath) -> void {
    out.open(filepath, std::ios::out);
    if (!out.is_open()) {
        out.open("../" + filepath, std::ios::out);
        if (!out.is_open()) {
            if (!std::filesystem::exists("../" + filepath)) {
                THROW_FILE_NOT_FOUND(filepath + " nor " + " ../" + filepath);
            } else {
                THROW_FILE_OPEN((filepath + " nor " + " ../" + filepath));
            }
        }
    }

    out.exceptions(std::ifstream::badbit);
}
