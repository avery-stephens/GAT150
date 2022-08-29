#include "PlayerComponent.h"
#include "Engine.h"
#include <iostream>

namespace gooblegorb
{
	void PlayerComponent::Initialize()
	{
		auto component = m_owner->GetComponent<CollisionComponent>();
		if (component)
		{
			component->SetCollisionEnter(std::bind(&PlayerComponent::onCollisionEnter, this, std::placeholders::_1));
			component->SetCollisionExit(std::bind(&PlayerComponent::onCollisionExit, this, std::placeholders::_1));
		}
	}

	void PlayerComponent::Update()
	{
		//std::cout << "hello from the moon or sum shit" << std::endl;

		//move left and right
		Vector2 direction = Vector2::zero;

		if (g_inputSystem.GetKeyState(key_left) == InputSystem::KeyState::Held)
		{
			direction = Vector2::left;
			//direction = Vector2::left;
		}

		if (g_inputSystem.GetKeyState(key_right) == InputSystem::KeyState::Held)
		{
			direction = Vector2::right;
			//direction = Vector2::right;
		}


		if (g_inputSystem.GetKeyState(key_A) == InputSystem::KeyState::Held)
		{
			direction = Vector2::left;
		}

		if (g_inputSystem.GetKeyState(key_D) == InputSystem::KeyState::Held)
		{
			direction = Vector2::right;
		}


		auto component = m_owner->GetComponent<PhysicsComponent>();
		if (component)
		{
			component->ApplyForce(direction * speed);
		}

		if (g_inputSystem.GetKeyState(key_space) == InputSystem::KeyState::Pressed)
		{
			auto component = m_owner->GetComponent<PhysicsComponent>();

			if (component)
			{
				component->ApplyForce(Vector2::up * 500);
			}
		}

		if (g_inputSystem.GetKeyState(key_W) == InputSystem::KeyState::Pressed)
		{
			auto component = m_owner->GetComponent<PhysicsComponent>();

			if (component)
			{
				component->ApplyForce(Vector2::up * 500);
			}
		}
	}

	bool PlayerComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool PlayerComponent::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, speed);

		return true;
	}

	void PlayerComponent::onCollisionEnter(Actor* other)
	{
		if (other->GetTag() == "Pickup")
		{
			other->SetDestroy();
		}
		//std::cout << "player enter\n";
	}

	void PlayerComponent::onCollisionExit(Actor* other)
	{
		//std::cout << "player exit\n";
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

	

