#pragma once
#include <WinSock2.h>
#include <iostream>
#include <exception>
#include <vector>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

#define CHECK(value, expected, string) if((value) == (expected)) \
{															     \
	std::cout << WSAGetLastError() << std::endl;                    \
	throw std::exception((string));							     \
}



class Client
{
public:

	Client(const std::string& server_ip, const std::string& server_port);
	~Client();
	Client(const Client& other) = delete;
	Client(Client&& other) = delete;
	Client& operator=(Client&& other) = delete;
	Client& operator=(Client& other) = delete;

	void send_data(const std::vector<char>& data) const;
	void send_data(const std::string& data) const;

	template<typename T>
	void send_data(const T* data, const size_t size_of_data);

	std::vector<char> recieve_data(const size_t size) const;

	void connect_client();
private:
	WSADATA m_wsadata;
	SOCKET m_sock;
	addrinfo* m_server_address_info;
};

template<typename T>
inline void Client::send_data(const T* data, const size_t size_of_data)
{
	CHECK(send(m_sock, data, size_of_data, 0), SOCKET_ERROR, "couldn't send data");
}
