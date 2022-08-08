#include "AudioComponent.h"
#include "Engine.h"

void gooblegorb::AudioComponent::Update()
{

}

void gooblegorb::AudioComponent::Play()
{
	g_audioSystem.PlayAudio(m_soundName, loop);
}

void gooblegorb::AudioComponent::Stop()
{

}
