#include <Windows.h>
#include <memory>
#include "WindowsUtils.h"


#define REFTIMES_PER_SECOND 10000000

DefaultAutoAudioWriter::DefaultAutoAudioWriter() : m_format(nullptr)
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
}
