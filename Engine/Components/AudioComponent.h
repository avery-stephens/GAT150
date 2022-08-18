#pragma once
#include "Framework/Component.h"

namespace gooblegorb 
{
	class AudioComponent : public Component
	{
	public:
		AudioComponent() = default;

		void Update();

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		void Play();
		void Stop();

	public:
		std::string m_soundName;
		bool playOnAwake = false;
		float m_pitch = 1;
		bool loop = false;

		// Inherited via Component
	};
}