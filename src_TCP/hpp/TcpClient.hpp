#pragma once
#include <string>
#include <unordered_map>
#include <memory>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <Ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
using SocketType = SOCKET;
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
using SocketType = int;
#endif

#include "../../src_game/Utils/hpp/Logger.hpp"

class TcpClient {

public:
	static TcpClient& GetInstance();

	bool Init();
	bool ConnectAll(const std::string& ip);       // apre tutte le socket sulle porte dal .env
	void Send(const std::string& portName, const std::string& data);
	int Receive(const std::string &portName, char *buffer, int buffer_size);
	void CloseAll();

private:
	TcpClient();
	~TcpClient();
	TcpClient(const TcpClient&) = delete;
	TcpClient& operator=(const TcpClient&) = delete;

	std::unordered_map<std::string, SocketType> sockets; // mappa portName -> socket
};
