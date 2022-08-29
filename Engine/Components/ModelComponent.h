#pragma once
#include "RendererComponent.h"

namespace gooblegorb
{
	class Model;

	class ModelComponent : public RendererComponent
	{
	public:
		CLASS_DECLARATION(ModelComponent)

		virtual void Update() override;
		virtual void Draw(Renderer& renderer)override;

	public:
		std::shared_ptr<Model> m_model;

		// Inherited via RendererComponent
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;
	};
}
