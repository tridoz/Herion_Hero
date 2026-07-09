//
// Created by david on 16/11/2025.
//

#include "../hpp/Logger.hpp"

#include <complex>

#include "../hpp/JSONParser.hpp"

const std::string Logger::RED   = "\033[31m";
const std::string Logger::GREEN = "\033[32m";
const std::string Logger::MAGENTA = "\033[35m";
const std::string Logger::CLEAR = "\033[0m";

bool Logger::file_logging_enabled = false;
bool Logger::stdout_logging_enabled = false;



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

std::string Logger::MakeMagenta( const std::string& message ) {
    return MAGENTA + message + CLEAR;
}

void Logger::LogOk( const std::time_t log_time, const std::string& type, const std::string& class_name, const std::string& function_name, const std::string& log_message) {

    const std::string time = FormatTime(log_time);
    const std::string ok_type = MakeGreen( type );

    std::string final_log_message =
        "[ " + ok_type + " ] { " + time + "} => " + class_name + "::" + function_name + "\n" +
        log_message + "\n";

    if ( file_logging_enabled ) {
        std::ofstream output( "../logs/Herion_Hero_Ok.log" , std::ios::app );
        std::ofstream output_temp( "../logs/Herion_Hero_Ok_temp.log", std::ios::app );
        output << final_log_message << std::endl;
        output_temp << final_log_message << std::endl;

        output.close();
        output_temp.close();

    }

    if ( stdout_logging_enabled ) {
        std::cout << final_log_message << std::endl;
    }

}

void Logger::LogErr( const std::time_t log_time, const std::string& type, const std::string& class_name, const std::string& function_name, const std::string& log_message) {
    const std::string time = FormatTime(log_time);
    const std::string err_type = MakeRed( type );

    std::string final_log_message =
        "[ " + err_type + " ] { " + time + "} => " + class_name + "::" + function_name + "\n" +
        log_message + "\n";


    if ( file_logging_enabled ) {
        std::ofstream output( "../logs/Herion_Hero_Err.log" , std::ios::app );
        std::ofstream output_temp( "../logs/Herion_Hero_Err_temp.log", std::ios::app );
        output << final_log_message << std::endl;
        output_temp << final_log_message << std::endl;
        output.close();
        output_temp.close();
    }

    if ( stdout_logging_enabled ) {
        std::cout << final_log_message << std::endl;
    }

}

void Logger::LogStackTrace(std::time_t log_time, const std::vector<std::string> &stack_trace) {

    const std::string type = MakeMagenta( "STACK TRACE" );
    const std::string time = FormatTime(log_time);

    std::string final_log_message = "[" + type + "] => " + time + "\n";

    for ( const auto line : stack_trace ) {
        final_log_message +=  line + "\n";
    }

    std::cout << final_log_message << std::endl;

}

void Logger::EnableFILELogging() {
    file_logging_enabled = true;
}

void Logger::DisableFILELogging() {
    file_logging_enabled = false;
}


void Logger::EnableSTDOUTLogging() {
    stdout_logging_enabled = true;
}

void Logger::DisableSTDOUTLogging() {
    stdout_logging_enabled = false;
}

void Logger::ClearTempLoggingFiles() {
    std::ofstream output_temp_ok("../logs/Herion_Hero_Ok_temp.log", std::ios::out );
    std::ofstream output_temp_err("../logs/Herion_Hero_Err_temp.log", std::ios::out );
}
