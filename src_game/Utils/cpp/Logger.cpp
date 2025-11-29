//
// Created by david on 16/11/2025.
//

#include "../hpp/Logger.hpp"

#include <complex>

const std::string Logger::RED   = "\033[31m";
const std::string Logger::GREEN = "\033[32m";
const std::string Logger::CLEAR = "\033[0m";
bool Logger::http_logging_enabled = false;
bool Logger::file_logging_enabled = false;
bool Logger::cout_logging_enabled = false;

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

    std::string final_log_message =
        "[ " + ok_type + " ] { " + time + "} => " + class_name + "::" + function_name + "\n" +
        log_message + "\n";


    if ( http_logging_enabled ) {
        auto& client = TcpClient::GetInstance();
        final_log_message += "\n<end>\n";
        client.Send( "LOG_PORT", final_log_message);
    }

    if ( file_logging_enabled ) {
        std::ofstream output( "log_ok.txt" , std::ios::app );
        output << final_log_message << std::endl;
        output.close();
    }

    if ( cout_logging_enabled ) {
        std::cout << final_log_message << std::endl;
    }

}

void Logger::LogErr( const std::time_t log_time, const std::string& type, const std::string& class_name, const std::string& function_name, const std::string& log_message) {
    const std::string time = FormatTime(log_time);
    const std::string err_type = MakeRed( type );

    std::string final_log_message =
        "[ " + err_type + " ] { " + time + "} => " + class_name + "::" + function_name + "\n" +
        log_message + "\n";

    if ( http_logging_enabled ) {
        auto& client = TcpClient::GetInstance();
        final_log_message += "\n<end>\n";
        client.Send( "LOG_PORT", final_log_message);
    }

    if ( file_logging_enabled ) {
        std::ofstream output( "log_err.txt" , std::ios::app );
        output << final_log_message << std::endl;
        output.close();
    }

    if ( cout_logging_enabled ) {
        std::cout << final_log_message << std::endl;
    }

}

void Logger::EnableFILELogging() {
    file_logging_enabled = true;
}

void Logger::DisableFILELogging() {
    file_logging_enabled = false;
}


void Logger::EnableSTDOUTLogging() {
    cout_logging_enabled = true;
}

void Logger::DisableSTDOUTLogging() {
    cout_logging_enabled = false;
}


void Logger::EnableHTTPLogging() {
    http_logging_enabled = true;
}

void Logger::DisableHTTPLogging() {
    http_logging_enabled = false;
}



