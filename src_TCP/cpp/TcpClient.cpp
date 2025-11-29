#include "../hpp/TcpClient.hpp"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>

TcpClient& TcpClient::GetInstance() {
    static TcpClient instance;
    return instance;
}

TcpClient::TcpClient() {}
TcpClient::~TcpClient() { CloseAll(); }

bool TcpClient::Init() {
#ifdef _WIN32
    WSADATA w;
    return WSAStartup(MAKEWORD(2,2), &w) == 0;
#else
    return true;
#endif
}

bool TcpClient::ConnectAll(const std::string& ip) {
    // chiudi socket già aperti
    CloseAll();

    const std::string portNames[] = {
        "LOG_PORT",
    };

    for (const auto& name : portNames) {

        const char* portStr = std::getenv(name.c_str());
        if (!portStr) {
            Logger::DisableHTTPLogging();
            Logger::EnableSTDOUTLogging();
            Logger::EnableFILELogging();

            Logger::LogErr(
                std::time(nullptr),
                "ENVS",
                "TcpClient",
                "ConnectAll",
                "Failed to get env key = " + name
                );
            continue;
        }

        const uint16_t port = std::stoi(portStr);

        SocketType sock;
#ifdef _WIN32
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == INVALID_SOCKET) continue;
#else
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) continue;
#endif

        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);

#ifdef _WIN32
        InetPtonA(AF_INET, ip.c_str(), &addr.sin_addr);
#else
        inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);
#endif

        if (connect(sock, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) != 0) {

#ifdef _WIN32
            closesocket(sock);
#else
            close(sock);
#endif
            Logger::DisableHTTPLogging();
            Logger::EnableSTDOUTLogging();
            Logger::EnableFILELogging();

            Logger::LogErr(
                std::time(nullptr),
                "CONNECTION",
                "TcpClient",
                "ConnectAll",
                "Failed to connect to " + name + " on port " + std::to_string(port) + " : " + strerror( errno)
                );
            continue;
        }

        sockets[name] = sock;
        std::cout << "Connected to " << name << " on port " << port << "\n";
    }

    return !sockets.empty();
}

void TcpClient::Send(const std::string& portName, const std::string& data) {
    auto it = sockets.find(portName);

    if (it == sockets.end() ) return ;

#ifdef _WIN32
    send(it->second, data.c_str(), (int)data.size(), 0);
#else
    send(it->second, data.c_str(), data.size(), 0);
#endif
}

int TcpClient::Receive(const std::string& portName, char* buffer, const int buffer_size) {
    auto it = sockets.find(portName);
    if (it == sockets.end()) return -1;

    return recv(it->second, buffer, buffer_size, 0);
}

void TcpClient::CloseAll() {
    for (auto& p : sockets) {
#ifdef _WIN32
        closesocket(p.second);
#else
        close(p.second);
#endif
    }
    sockets.clear();
}
