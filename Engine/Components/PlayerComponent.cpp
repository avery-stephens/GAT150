#include "PlayerComponent.h"
#include "Engine.h"
#include <iostream>

namespace gooblegorb
{
	void PlayerComponent::Initialize()
	{
		CharacterComponent::Initialize();
	}

	void PlayerComponent::Update()
	{
		//std::cout << "hello from the moon or sum shit" << std::endl;

		//move left and right
		Vector2 direction = Vector2::zero;

		if (g_inputSystem.GetKeyState(key_left) == InputSystem::KeyState::Held)
		{
			direction = Vector2::left;
		}

		if (g_inputSystem.GetKeyState(key_right) == InputSystem::KeyState::Held)
		{
			direction = Vector2::right;
		}


		if (g_inputSystem.GetKeyState(key_A) == InputSystem::KeyState::Held)
		{
			direction = Vector2::left;
		}

		if (g_inputSystem.GetKeyState(key_D) == InputSystem::KeyState::Held)
		{
			direction = Vector2::right;
		}

		Vector2 velocity;
		auto component = m_owner->GetComponent<PhysicsComponent>();
		if (component)
		{
			// if in the air (m_groundCount == 0) then reduce force 
			float multiplier = (m_groundCount > 0) ? 1 : 0.2f;

			component->ApplyForce(direction * speed * multiplier);
			velocity = component->velocity;
		}

		if (m_groundCount > 0 && g_inputSystem.GetKeyState(key_space) == InputSystem::KeyState::Pressed)
		{
			Vector2 velocity;
			auto component = m_owner->GetComponent<PhysicsComponent>();

			gooblegorb::g_audioSystem.PlayAudio("jump");

			if (component)
			{
				component->ApplyForce(Vector2::up * jump);
			}

			auto renderComponent = m_owner->GetComponent <RendererComponent>();
			if (renderComponent)
			{
				if (velocity.x != 0) renderComponent->SetFlipHorizontal(velocity.x < 0);
			}
		}

		if (m_groundCount > 0 && g_inputSystem.GetKeyState(key_W) == InputSystem::KeyState::Pressed)
		{
			Vector2 velocity;
			auto component = m_owner->GetComponent<PhysicsComponent>();

			gooblegorb::g_audioSystem.PlayAudio("jump");

			if (component)
			{
				component->ApplyForce(Vector2::up * jump);
			}

			auto renderComponent = m_owner->GetComponent <RendererComponent>();
			if (renderComponent)
			{
				if (velocity.x != 0) renderComponent->SetFlipHorizontal(velocity.x < 0);
			}
		}

		auto animComponent = m_owner->GetComponent<SpriteAnimComponent>();
		if (animComponent)
		{
			if (velocity.x != 0) animComponent->SetFlipHorizontal(velocity.x < 0);
			if (std::fabs(velocity.x) > 0)
			{
				animComponent->SetSequence("run");
			}
			else
			{
				animComponent->SetSequence("idle");
			}
		}

		auto camera = m_owner->GetScene()->GetActorFromName("Camera");
		if (camera)
		{
			camera->m_transform.position = m_owner->m_transform.position;
		}
	}

	bool PlayerComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool PlayerComponent::Read(const rapidjson::Value& value)
	{
		CharacterComponent::Read(value);
		READ_DATA(value, jump);

		return true;
	}

	void PlayerComponent::OnNotify(const Event& event)
	{
		if (event.name == "EVENT_DAMAGE")
		{
			health -= std::get<float>(event.data);
			std::cout << health << std::endl;
			if (health <= 0)
			{
				m_owner->SetDestroy();

				Event event;
				event.name = "EVENT_PLAYER_DEAD";

				g_eventManager.Notify(event);
			}
		}
	}

	void PlayerComponent::onCollisionEnter(Actor* other)
	{
		if (other->GetName() == "Coin")
		{
			Event event;
			event.name = "EVENT ADD_POINTS";
			event.data = 100;

			g_eventManager.Notify(event);

			gooblegorb::g_audioSystem.PlayAudio("coin");

			other->SetDestroy();
		}

		if (other->GetTag() == "Enemy")
		{
			Event event;
			event.name = "EVENT_DAMAGE";
			event.data = damage;
			event.reciever = other;

			g_eventManager.Notify(event);
		}

		//if (other->GetName() == "HealthFood")
		//{
		//	Event event;
		//	event.name = "EVENT ADD_POINTS";
		//	event.name = "EVENT_ADD_HEALTH";
		//	event.data = 50;
		//	event.reciever = other;

		//	g_eventManager.Notify(event);

		//	other->SetDestroy();
		//}

		if (other->GetTag() == "Ground")
		{
			m_groundCount++;
		}
		//std::cout << "player enter\n";
	}

	void PlayerComponent::onCollisionExit(Actor* other)
	{
		if (other->GetTag() == "Ground")
		{
			m_groundCount--;
		}

		//std::cout << "player exit\n";
	}
}