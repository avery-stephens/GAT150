#pragma once
#include "Framework/Component.h"

namespace gooblegorb
{
	class Renderer;
	class RendererComponent : public Component
	{
	public:
		virtual void Draw(Renderer& renderer) = 0;

		virtual void Update() override;
	};
}