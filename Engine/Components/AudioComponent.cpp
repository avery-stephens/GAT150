#include "AudioComponent.h" 
#include "Engine.h"

namespace gooblegorb
{
	AudioComponent::~AudioComponent()
	{
		// !! call Stop() to stop the audio channel when destroyed 
		Stop();
	}

	void AudioComponent::Initialize()
	{
		if (playOnAwake)
		{
			// !! call Play() to start the audio if playing on awake (start) 
			Play();
		}
	}

	void AudioComponent::Update()
	{
	}

	void AudioComponent::Play()
	{
		// !! call Stop() to stop the current audio channel
		m_channel.Stop();
		m_channel = g_audioSystem.PlayAudio(sound_name, volume, pitch, loop);
	}

	void AudioComponent::Stop()
	{
		m_channel.Stop();
	}

	bool AudioComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool AudioComponent::Read(const rapidjson::Value& value)
	{
		// !! READ_DATA on sound_name, volume, ... 
		READ_DATA(value, sound_name);
		READ_DATA(value, volume);
		READ_DATA(value, pitch);
		READ_DATA(value, playOnAwake);
		READ_DATA(value, loop);

		g_audioSystem.AddAudio(sound_name, sound_name);

		return true;
	}
}