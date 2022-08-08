#pragma once
#include "Framework/Component.h"

namespace gooblegorb 
{
	class AudioComponent : public Component
	{
	public:
		AudioComponent() = default;

		void Update();

		void Play();
		void Stop();

	public:
		std::string m_soundName;
		bool playOnAwake = false;
		float m_pitch = 1;
		bool loop = false;
	};
}