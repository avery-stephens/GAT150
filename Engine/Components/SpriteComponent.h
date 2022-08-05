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

	public:
		std::shared_ptr<Texture> m_texture;
	};
}