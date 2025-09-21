#include <iostream>

#include "Client.h"

constexpr char SERVER_PORT[] = "8089";
constexpr char SERVER_IP[] = "127.0.0.1";
int main()
{

	char HOLD[sizeof(in_addr)];

	//memset(&addr, 0, sizeof(sockaddr_in));

	//addr.sin_family = AF_INET;
	//addr.sin_port = htons(SERVER_PORT);
	//inet_pton(AF_INET, , &addr.sin_addr.S_un.S_addr);
	try
	{


	}
	catch(const std::exception& e)
	{
		
		std::cout << e.what();
		return WSAGetLastError();
	}


	//std::cout << addr.sin_family << " " << addr.sin_port << " " << addr.sin_addr.S_un.S_addr << std::endl;

	try
	{
		Client some_client(SERVER_IP, SERVER_PORT);
 		std::string some_string = "some string";
		some_client.connect_client();
		some_client.send_data(some_string.data(), some_string.size());
		std::vector<char> data = some_client.recieve_data(1500);
		std::string message = data.data();

	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		return WSAGetLastError();
	}

}

