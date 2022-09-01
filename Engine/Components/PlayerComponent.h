#pragma once
#include "Framework/Component.h"
#include "Physics/Collision.h"
#include "CharacterComponent.h"

namespace gooblegorb
{
	class PlayerComponent : public CharacterComponent
	{
	public:
		PlayerComponent() = default;
		CLASS_DECLARATION(PlayerComponent)

		void Initialize() override;
		void Update() override;

		virtual void OnNotify(const Event& event) override;
		virtual void onCollisionEnter(Actor* other) override;
		virtual void onCollisionExit(Actor* other) override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		float jump = 2000;
		int m_groundCount = 0;
	};
}