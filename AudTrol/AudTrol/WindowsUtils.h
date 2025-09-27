#pragma once

#include <Windows.h>
#include <Audioclient.h>
#include <Audiopolicy.h>
#include <mmdeviceapi.h>
#include <exception>
#include <iostream>
#include <vector>

#define CHECK_COM(value, string) if(S_OK != (value)) \
									{				\
										throw std::exception(string); \
									}
class IAutoAudioWriter
{
public:
	IAutoAudioWriter() ;
	virtual ~IAutoAudioWriter() = 0;
	virtual void activate() = 0;

	virtual void write_to_endpoint(const std::vector<char>& audio) = 0;
};



class DefaultAutoAudioWriter : public IAutoAudioWriter
{
	DefaultAutoAudioWriter();
	~DefaultAutoAudioWriter();

	void activate() override;
	void write_to_endpoint(const std::vector<char>& audio) override;

private:
	IMMDeviceEnumerator* m_device_enum;
	IMMDevice* m_device;
	IAudioRenderClient* m_renderer;
	IAudioClient* m_client;
	WAVEFORMATEX* m_format;
};


