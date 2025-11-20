//
// Created by david on 16/11/2025.
//

#ifndef HERION_HERO_LOGGER_HPP
#define HERION_HERO_LOGGER_HPP

#include <string>
#include <ctime>
#include <iostream>
#include <sstream>
#include <chrono>
#include <iomanip>




class Logger
{
private:

    static const std::string RED;
    static const std::string GREEN;
    static const std::string CLEAR;

    static std::string MakeRed( const std::string& message );
    static std::string MakeGreen( const std::string& message );
    static std::string FormatTime( std::time_t time_to_format);

public:
    static void LogOK(
        std::time_t log_time,
        const std::string& type,
        const std::string& class_name,
        const std::string& function_name,
        const std::string& log_message
        );

    static void LogErr(
        std::time_t log_time,
        const std::string& type,
        const std::string& class_name,
        const std::string& function_name,
        const std::string& log_message
        );

};


#endif //HERION_HERO_LOGGER_HPP