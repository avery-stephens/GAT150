#include "PhysicsComponent.h"
#include "Engine.h"

void gooblegorb::PhysicsComponent::Update()
{
	velocity += acceleration * g_time.deltaTime;
	m_owner->m_transform.position += velocity * g_time.deltaTime;
	velocity *= damping;

	acceleration = Vector2::zero;
}

bool gooblegorb::PhysicsComponent::Write(const rapidjson::Value& value) const
{

	return true;
}

bool gooblegorb::PhysicsComponent::Read(const rapidjson::Value& value)
{
	READ_DATA(value, damping);

	return true;
}
