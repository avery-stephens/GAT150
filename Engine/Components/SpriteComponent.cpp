#include "SpriteComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"

namespace gooblegorb 
{
	void gooblegorb::SpriteComponent::Update()
	{

	}

	void gooblegorb::SpriteComponent::Draw(Renderer& renderer)
	{
		renderer.Draw(m_texture, m_owner->m_transform);
	}
	bool SpriteComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}
	bool SpriteComponent::Read(const rapidjson::Value& value)
	{
		return false;
	}
}
