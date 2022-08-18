#pragma once
#include "RendererComponent.h"

namespace gooblegorb
{
	class Texture;

	class SpriteComponent : public RendererComponent
	{
	public:
		// Inherited via RendererComponent
		virtual void Update() override;
		virtual void Draw(Renderer& renderer) override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;
	public:
		std::shared_ptr<Texture> m_texture;
	};
}