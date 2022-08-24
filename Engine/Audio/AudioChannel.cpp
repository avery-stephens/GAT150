#include "Audio/AudioChannel.h"
#include <fmod.hpp>


namespace gooblegorb
{
	bool AudioChannel::IsPlaying()
	{
		// !! if channel is null, return false 
		bool isPlaying;
		m_channel->isPlaying(&isPlaying);

		if (m_channel == nullptr) return false;

		return isPlaying;
	}

	void AudioChannel::Stop()
	{
		if (IsPlaying()) m_channel->stop();
	}

	void AudioChannel::SetPitch(float pitch)
	{
		if (IsPlaying()) m_channel->setPitch(pitch);// !! call setPitch on channel (pass pitch) 
	}

	float AudioChannel::GetPitch()
	{
		float pitch = 0;

		if (IsPlaying()) m_channel->getPitch(&pitch); // !! call getPitch (pass pointer to pitch &) 
		return pitch;
	}

	void AudioChannel::SetVolume(float volume)
	{
		if (IsPlaying()) m_channel->setVolume(volume); // !! call setVolume on channel (pass volume) 
	}

	float AudioChannel::GetVolume()
	{
		float volume = 0;
		if (IsPlaying()) m_channel->getVolume(&volume); // !! call getVolume (pass pointer to volume &) 

		return volume;
	}
}