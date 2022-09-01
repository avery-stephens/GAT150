#pragma once
#include "Framework/Component.h"
#include "Physics/Collision.h"
#include "Physics/PhysicsSystem.h"
#include <functional>

namespace gooblegorb
{
	class CollisionComponent : public Component, public ICollision
	{
	public:
		using functionPtr = std::function<void(Actor*)>;

	public:
		virtual void Initialize() override;
		virtual void Update() override;

		CLASS_DECLARATION(CollisionComponent)

		// Inherited via Component
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;
		
		void SetCollisionEnter(functionPtr function) { m_enterFunction = function; }
		void SetCollisionExit(functionPtr function) { m_exitFunction = function; }

		// Inherited via ICollision
		virtual void onCollisionEnter(Actor* other) override;
		virtual void onCollisionExit(Actor* other) override;

	private:
		PhysicsSystem::CollisionData data;
		Vector2 scaleOffset = Vector2{ 1,1 };

		functionPtr m_enterFunction;
		functionPtr m_exitFunction;
	};
}