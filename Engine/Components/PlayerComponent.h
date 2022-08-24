#pragma once
#include "Framework/Component.h"
#include "Physics/Collision.h"

namespace gooblegorb
{
	class PlayerComponent : public Component, public ICollision
	{
	public:
		PlayerComponent() = default;

		void Initialize() override;
		void Update() override;

		virtual void onCollisionEnter(Actor* other) override;
		virtual void onCollisionExit(Actor* other) override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		float speed = 0;

	};
}