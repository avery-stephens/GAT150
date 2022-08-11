#pragma once
#include "RendererComponent.h"

namespace gooblegorb
{
	class Model;

	class ModelComponent : public RendererComponent
	{
	public:
		virtual void Update() override;
		virtual void Draw(Renderer& renderer)override;
	public:
		std::shared_ptr<Model> m_model;
	};
}
