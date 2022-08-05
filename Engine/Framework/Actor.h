#pragma once
#include "GameObject.h"
#include "../Renderer/Model.h"
#include "Math/Vector2.h"

namespace gooblegorb 
{
	class Scene;

	class Actor : public GameObject
	{
	public:
		Actor() = default;
		Actor(const Model& model, const Transform& transform) : 
			GameObject{ transform }, 
			m_model{ model }{}

		virtual void Update() override {}
		virtual void Draw(Renderer& renderer);

		virtual void OnCollision(Actor* other) {};
		float GetRadius() { return m_model.GetRadius() * std::max(m_transform.scale.x,m_transform.scale.y); }
		std::string& GetTag() { return m_tag; }

		friend class Scene;
		
	protected:
		std::string m_tag;
		bool destroy = false;
		//physics
		float m_damping = 1;
		Vector2 m_velocity;

		Model m_model;
		Scene* m_scene = nullptr;
	};
}
