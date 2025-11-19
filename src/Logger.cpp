//
// Created by david on 16/11/2025.
//

#include "Logger.hpp"

const std::string Logger::RED   = "\033[31m";
const std::string Logger::GREEN = "\033[32m";
const std::string Logger::CLEAR = "\033[0m";

std::string Logger::FormatTime(const std::time_t time_to_format) {
    const std::tm *lt = std::localtime(&time_to_format);
    std::stringstream ss;

    ss << std::setfill('0')
          << (lt->tm_year + 1900) << ":"
          << std::setw(2) << (lt->tm_mon + 1) << ":"
          << std::setw(2) << lt->tm_mday << " "
          << std::setw(2) << lt->tm_hour << ":"
          << std::setw(2) << lt->tm_min << ":"
          << std::setw(2) << lt->tm_sec;

    return ss.str();

}

std::string Logger::MakeRed( const std::string& message ) {
    return RED + message + CLEAR;
}

std::string Logger::MakeGreen( const std::string& message ) {
    return GREEN + message + CLEAR;
}

void Logger::LogOK( const std::time_t log_time, const std::string& type, const std::string& class_name, const std::string& function_name, const std::string& log_message) {
    const std::string time = FormatTime(log_time);
    const std::string ok_type = MakeGreen( type );

    const std::string final_log_message =
        "[ " + ok_type + " ] { " + time + "} => " + class_name + "::" + function_name + "\n" +
        log_message + "\n";

    std::cout << final_log_message << std::endl;
}

void Logger::LogErr( const std::time_t log_time, const std::string& type, const std::string& class_name, const std::string& function_name, const std::string& log_message) {
    const std::string time = FormatTime(log_time);
    const std::string ok_type = MakeRed( type );

    const std::string final_log_message =
        "[ " + ok_type + " ] { " + time + "} => " + class_name + "::" + function_name + "\n" +
        log_message + "\n";

    std::cout << final_log_message << std::endl;
}






