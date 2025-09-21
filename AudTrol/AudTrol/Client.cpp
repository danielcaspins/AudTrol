#include "Client.h"


Client::Client(const std::string& server_ip, const std::string& server_port) : m_server_address_info(nullptr)
{
	
	addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	CHECK(WSAStartup(MAKEWORD(2, 2), &m_wsadata), !0, "couldn't start wsa");
	m_sock = socket(AF_UNSPEC, SOCK_STREAM, IPPROTO_TCP);
	CHECK(m_sock, SOCKET_ERROR, "coultn't init sock")
	CHECK(getaddrinfo(server_ip.c_str(), server_port.c_str(), &hints, &m_server_address_info), true, "couldn't get address info");
}

Client::~Client()
{
	if (m_sock != INVALID_SOCKET)
	{
		closesocket(m_sock);
		WSACleanup();
		m_sock = INVALID_SOCKET;
	}
}

std::vector<char> Client::recieve_data(const size_t size) const
{

	std::vector<char> data(size);
	CHECK(recv(m_sock, data.data(), size, 0), SOCKET_ERROR, "couldn't recive data");
}

void Client::send_data(const std::vector<char>& data) const
{
	CHECK(send(m_sock, data.data(), data.size(), 0), SOCKET_ERROR, "couldn't send data");
}

void Client::connect_client()
{
	std::cout << m_server_address_info << std::endl;
	CHECK(connect(m_sock, m_server_address_info->ai_addr, (int)m_server_address_info->ai_addrlen), SOCKET_ERROR, "couldn't connect to socket")
}
 