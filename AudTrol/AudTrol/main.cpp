#include <iostream>

#include "Client.h"

constexpr char SERVER_PORT[] = "8089";
constexpr char SERVER_IP[] = "127.0.0.1";



int main()
{
	try
	{
		Client some_client(SERVER_IP, SERVER_PORT);
 		std::string some_string = "some string";
		some_client.connect_client();
		some_client.send_data(some_string.data(), some_string.size());
		std::vector<char> string = some_client.recieve_data(1500);
		std::string message = string.data();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		return WSAGetLastError();
	}
}

