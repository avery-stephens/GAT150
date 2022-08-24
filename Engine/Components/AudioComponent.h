#pragma once
#include "Framework/Component.h"
#include "Audio/AudioChannel.h"

namespace gooblegorb 
{
	class AudioComponent : public Component
	{
	public:
		AudioComponent() = default;
		~AudioComponent();

		void Initialize();
		void Update();

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		void Play();
		void Stop();

	private:
		AudioChannel m_channel;

		std::string sound_name;
		bool playOnAwake = false;
		float pitch = 1;
		float volume = 1;
		bool loop = false;
	};
}