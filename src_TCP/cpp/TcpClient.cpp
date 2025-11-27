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
    std::cout << ip << std::endl;
    // esempio: lista di nomi di porte da cercare nel .env
    const std::string portNames[] = {
        "LOG_PORT",
    };

    for (const auto& name : portNames) {

        const char* portStr = std::getenv(name.c_str());
        if (!portStr) {
            std::cerr << "Env var not found: " << name << "\n";
            continue;
        }

        int port = std::stoi(portStr);

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

        if (connect(sock, (sockaddr*)&addr, sizeof(addr)) != 0) {
#ifdef _WIN32
            closesocket(sock);
#else
            close(sock);
#endif
            std::cerr << "Failed to connect to " << name << " on port " << port << " : " << strerror( errno)<< "\n";
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

int TcpClient::Receive(const std::string& portName, char* buffer, int size) {
    auto it = sockets.find(portName);
    if (it == sockets.end()) return -1;

    return recv(it->second, buffer, size, 0);
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
