#include "PlayerComponent.h"
#include "Engine.h"
#include <iostream>

void gooblegorb::PlayerComponent::Update()
{
	//std::cout << "hello from the moon or sum shit" << std::endl;

	Vector2 direction = Vector2::zero;

	if (g_inputSystem.GetKeyState(key_left) == InputSystem::KeyState::Held)
	{
		m_owner->m_transform.rotation -= 180 * g_time.deltaTime;
		//direction = Vector2::left;
	}

	if (g_inputSystem.GetKeyState(key_right) == InputSystem::KeyState::Held)
	{
		m_owner->m_transform.rotation += 180 * g_time.deltaTime;
		//direction = Vector2::right;
	}
	
	float thrust = 0;

	if (g_inputSystem.GetKeyState(key_up) == InputSystem::KeyState::Held)
	{
		thrust = 250;
		//direction = Vector2::up;
	}

	auto component = m_owner->GetComponent<PhysicsComponent>();

	if (component)
	{
		//thrust
		Vector2 force = Vector2::Rotate({ 1, 0 },(math::DegtoRad(m_owner->m_transform.rotation))) * thrust;
		component->ApplyForce(force);

		//gravity
		force = (Vector2{ 400,300 } - m_owner->m_transform.position).Normalized() * 100.0f;
		component->ApplyForce(force);
	}

	m_owner->m_transform.position += direction * 300 * g_time.deltaTime;

	if (g_inputSystem.GetKeyState(key_space) == InputSystem::KeyState::Pressed)
	{
		auto component = m_owner->GetComponent<AudioComponent>();
		if (component)
		{
			component->Play();
		}
	}
	//if (g_inputSystem.GetKeyState(key_down) == InputSystem::KeyState::Held)
	//{
	//	direction = Vector2::down;
	//}

	/*
	auto leftArrow = gooblegorb::g_inputSystem.GetKeyState(gooblegorb::key_left) == gooblegorb::InputSystem::KeyState::Held;
	auto leftA = gooblegorb::g_inputSystem.GetKeyState(gooblegorb::key_A) == gooblegorb::InputSystem::KeyState::Held;
	if (leftArrow || leftA)
	{
		m_owner->m_transform.position.x -= m_speed * gooblegorb::g_time.deltaTime;
	}

	auto rightArrow = gooblegorb::g_inputSystem.GetKeyState(gooblegorb::key_right) == gooblegorb::InputSystem::KeyState::Held;
	auto rightD = gooblegorb::g_inputSystem.GetKeyState(gooblegorb::key_D) == gooblegorb::InputSystem::KeyState::Held;
	if (rightArrow || rightD)
	{
		m_owner->m_transform.position.x += m_speed * gooblegorb::g_time.deltaTime;
	}

	auto upArrow = gooblegorb::g_inputSystem.GetKeyState(gooblegorb::key_up) == gooblegorb::InputSystem::KeyState::Held;
	auto upW = gooblegorb::g_inputSystem.GetKeyState(gooblegorb::key_W) == gooblegorb::InputSystem::KeyState::Held;

	if(upArrow || upW)
	{
		m_owner->m_transform.position.y -= m_speed * gooblegorb::g_time.deltaTime;
	}

	auto downArrow = gooblegorb::g_inputSystem.GetKeyState(gooblegorb::key_right) == gooblegorb::InputSystem::KeyState::Held;
	auto downS = gooblegorb::g_inputSystem.GetKeyState(gooblegorb::key_S) == gooblegorb::InputSystem::KeyState::Held;

	if (downArrow || downS)
	{
		m_owner->m_transform.position.y += m_speed * gooblegorb::g_time.deltaTime;
	}
	*/

	
}