//
// Created by david on 16/11/2025.
//

#ifndef HERION_HERO_LOGGER_HPP
#define HERION_HERO_LOGGER_HPP

#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

class Logger {
  private:
    static const std::string RED;
    static const std::string GREEN;
    static const std::string CLEAR;
    static const std::string MAGENTA;

    static bool file_logging_enabled;
    static bool stdout_logging_enabled;
    static auto MakeRed(const std::string&) -> std::string;
    static auto MakeGreen(const std::string&) -> std::string;
    static auto MakeMagenta(const std::string&) -> std::string;
    static auto FormatTime(std::time_t) -> std::string;

  public:
    static auto LogOk(std::time_t, const std::string&, const std::string&, const std::string&, const std::string&)
        -> void;
    static auto LogErr(std::time_t, const std::string&, const std::string&, const std::string&, const std::string&)
        -> void;

    static auto LogStackTrace(std::time_t, const std::vector<std::string>&) -> void;

    static auto EnableSTDOUTLogging() -> void;
    static auto DisableSTDOUTLogging() -> void;
    static auto ClearTempLoggingFiles() -> void;
    static auto EnableFILELogging() -> void;
    static auto DisableFILELogging() -> void;
};

#endif // HERION_HERO_LOGGER_HPP
