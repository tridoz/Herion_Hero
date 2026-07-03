//
// Created by david on 16/11/2025.
//

#ifndef HERION_HERO_LOGGER_HPP
#define HERION_HERO_LOGGER_HPP


#include "Reflector.hpp"
#include <string>
#include <ctime>
#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
#include <iomanip>

class Logger {
private:

    static const std::string RED;
    static const std::string GREEN;
    static const std::string CLEAR;
    static const std::string MAGENTA;

    static bool file_logging_enabled;
    static bool stdout_logging_enabled;

    /**
     * @brief Return the given string with format code to make it red
     * @param message String to modify
     * @return std::string
     */
    static std::string MakeRed( const std::string& message );

    /**
     * @brief Return the given string with format code to make it green
     * @param message String to modify
     * @return std::string
     */
    static std::string MakeGreen( const std::string& message );

    /**
     * @brief Return the given string with format code to make it magenta
     * @param message String to modify
     * @return std::string
     */
    static std::string MakeMagenta( const std::string& message );

    /**
     * @brief Return a string time formatted as YY:MM:DD hh:mm::ss
     * @param time_to_format Time that needs to be formatted
     * @return std::string
     */
    static std::string FormatTime( std::time_t time_to_format);



public:
    /**
     * @brief Log that something went all right
     * @param log_time Time of the log
     * @param type Type of the thing that went all right
     * @param class_name Class name where the log is being made
     * @param function_name Function name where the log is being made
     * @param log_message Log message
     */
    static void LogOk(
        std::time_t log_time,
        const std::string& type,
        const std::string& class_name,
        const std::string& function_name,
        const std::string& log_message
        );

    /**
     * @brief Log that something went wrong
     * @param log_time Time of the log
     * @param type Type of the thing that went wrong
     * @param class_name Class name where the log is being made
     * @param function_name Function name where the log is being made
     * @param log_message Log message
     */
    static void LogErr(
        std::time_t log_time,
        const std::string& type,
        const std::string& class_name,
        const std::string& function_name,
        const std::string& log_message
        );

    /**
     * @brief Log all the Exception Stack Trace
     * @param log_time Time of the log
     * @param stack_trace Stack trace object to log
     */
    static void LogStackTrace(
        std::time_t log_time,
        const std::vector< std::string >& stack_trace
        );

    template<typename T>
    static void debug_reflection_print( const T& obj, int indent_level ) {
        std::cout << value_to_string(obj, indent_level) << std::endl;
    }


    /**
     * @brief Enable logging on the stdout
     */
    static void EnableSTDOUTLogging();

    /**
     * @brief Disable logging on the stdout
     */
    static void DisableSTDOUTLogging();

    /**
     * @brief Clear temporary logging fils
     */
    static void ClearTempLoggingFiles();

    /**
     * @brief Enable logging on logs file
     */
    static void EnableFILELogging();

    /**
     * @brief Disable logging on logs file
     */
    static void DisableFILELogging();

};


#endif //HERION_HERO_LOGGER_HPP
