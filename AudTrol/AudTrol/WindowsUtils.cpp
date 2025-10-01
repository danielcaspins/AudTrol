#include <Windows.h>
#include <memory>
#include "WindowsUtils.h"


#define REFTIMES_PER_SECOND 10000000
#define REFTIMES_PER_MILLISEC  10000

DefaultAutoAudioWriter::DefaultAutoAudioWriter() : m_format(nullptr), m_audio_buffer(nullptr), m_audio_buffer_size(0)
{
	CHECK_COM(CoCreateInstance(CLSID_MMDeviceEnumerator,
		nullptr,
		CLSCTX_ALL,
		IID_IMMDeviceEnumerator,
		reinterpret_cast<void**>(&m_device_enum)), "couldn't create MMDevice");
	m_device_enum->AddRef();
    CHECK_COM(m_device_enum->GetDefaultAudioEndpoint(eRender, eConsole, &m_device), "couldn't create default audio");
	m_device->AddRef();
}

DefaultAutoAudioWriter::~DefaultAutoAudioWriter()
{
	CoTaskMemFree(m_format);
	m_device_enum->Release();
	m_device->Release();
	m_renderer->Release();
	m_client->Release();
}

void DefaultAutoAudioWriter::activate()
{
	CHECK_COM(m_device->Activate(IID_IAudioClient, CLSCTX_ALL, nullptr, reinterpret_cast<void**>(m_client)),
		"couldn't activate")
	CHECK_COM(m_client->GetMixFormat(&m_format), "couldn't get format");
	CHECK_COM(m_client->Initialize(AUDCLNT_SHAREMODE_SHARED, 0, REFTIMES_PER_SECOND, 0, m_format, nullptr), "couldnn't init m_client");
	CHECK_COM(m_client->GetService(IID_IAudioRenderClient, reinterpret_cast<void**>(m_renderer)), "coulnd't get renderer");
}

void DefaultAutoAudioWriter::write_to_endpoint(const std::vector<char>& audio)
{
	if (nullptr == m_audio_buffer)
	{
		CHECK_COM(m_client->GetBufferSize(&m_audio_buffer_size), "coudln't get buffer size");
		CHECK_COM(m_renderer->GetBuffer(m_audio_buffer_size, &m_audio_buffer), "couldn't get buffer");
	}

	size_t flags = 0;
	UINT32 num_of_padding = 0;
	UINT32 num_of_available_frames = 0;
	REFERENCE_TIME actual_time = REFTIMES_PER_SECOND * m_audio_buffer_size / m_format->nSamplesPerSec;
	size_t offset = 0;
	CHECK_COM(m_client->Start(), "couldn't start client");

	std::memcpy(m_audio_buffer,audio.data(), m_audio_buffer_size);
	offset = m_audio_buffer_size;

	while(offset < audio.size())
	{
		Sleep(actual_time / REFTIMES_PER_MILLISEC / 2);
		CHECK_COM(m_client->GetCurrentPadding(&num_of_padding), "couldn't get num of padding");
		num_of_available_frames = m_audio_buffer_size - num_of_padding;
		CHECK_COM(m_renderer->GetBuffer(num_of_available_frames, &m_audio_buffer));
		std::memcpy(m_audio_buffer, audio.data(), num_of_available_frames);
		CHECK_COM(m_renderer->ReleaseBuffer(num_of_available_frames, 0), "couldn't realse the buffer");
	}

	Sleep(actual_time / REFTIMES_PER_MILLISEC / 2);
	CHECK_COM(m_client->Stop(), "couldn't stop");
}
