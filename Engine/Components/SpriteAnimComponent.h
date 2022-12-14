#pragma once
#include "RendererComponent.h"
#include "Math/Rect.h"
#include <map>

namespace gooblegorb
{
	class Texture;

	class SpriteAnimComponent : public RendererComponent
	{
	public:
		struct Sequence
		{
			std::string name;

			float fps = 0;
			int num_columns = 0;
			int num_rows = 0;

			int start_frame = 0;
			int end_frame = 0;

			bool loop = true;

			std::shared_ptr<Texture> texture;
		};

	public:
		CLASS_DECLARATION(SpriteAnimComponent)

		// Inherited via RendererComponent
		virtual void Update() override;
		virtual void Draw(Renderer& renderer) override;

		virtual void SetSequence(const std::string& name);
		Rect& GetSource() override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		int frame = 0;
		float frameTimer = 0;

		std::map<std::string, Sequence> m_sequences;
		Sequence* m_sequence = nullptr;
	};
}