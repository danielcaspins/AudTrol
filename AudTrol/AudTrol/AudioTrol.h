#pragma once
#include "Client.h"


class AudioTrol
{
public:
	AudioTrol();
	std::vector<char> get_audio_from_server();
	void make_audio(const std::vector<char>& audio);
	void run();
private:
	Client m_client;
};