#include "AudioTrol.h"


constexpr char SERVER_IP[] = "127.0.0.1";
constexpr char SERVER_PORT[] = "8089";
constexpr size_t SIZE = 1500;





AudioTrol::AudioTrol() : m_client(SERVER_IP, SERVER_PORT)
{
}

std::vector<char> AudioTrol::get_audio_from_server()
{
	m_client.connect_client();

	std::vector<char> audio_data;
	std::vector<char> current_data_batch;

	do
	{
		current_data_batch = m_client.recieve_data(SIZE);
		std::copy(current_data_batch.begin(), current_data_batch.end(), std::back_inserter(audio_data));
	} while (current_data_batch.size() < SIZE);

	return std::move(audio_data);
}

void AudioTrol::make_audio(const std::vector<char>& audio)
{
	CoCreateInstance(CLSID_MMDeviceEnumerator, nullptr, )
}
