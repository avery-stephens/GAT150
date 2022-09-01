#pragma once
#include "GameObject.h"
#include "Component.h"
#include <vector>

namespace gooblegorb 
{
	class Scene;
	class Renderer;

	class Actor : public GameObject, public ISerializable
	{
	public:
		Actor() = default;
		Actor(const Actor& other);
		Actor(const Transform& transform) : m_transform{ transform } {}

		CLASS_DECLARATION(Actor)

		virtual void Update() override;
		virtual void Initialize() override;
		virtual void Draw(Renderer& renderer);

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		void AddChild(std::unique_ptr<Actor> child);

		void AddComponent(std::unique_ptr<Component> component);
		template<typename T>
		T* GetComponent();

		virtual void OnCollision(Actor* other) {};
		float GetRadius() { return 0; } // m_model.GetRadius()* std::max(m_transform.scale.x, m_transform.scale.y);

		const std::string& GetTag() { return tag; }
		void SetTag(const std::string& tag) { this->tag = tag; }

		const std::string& GetName() { return name; }
		void SetName(const std::string& name) { this->name = name; }

		void SetDestroy() { destroy = true; }
		bool isDestroyed() { return destroy; }

		void SetActive(bool active = true) { this->active = active; }
		bool isActive() { return active; }

		Scene* GetScene() { return m_scene; }

		friend class Scene;
		friend class Component;
		//friend class Component;

		Transform m_transform;
		
	protected:
		std::string name;
		std::string tag;

		bool active = true;
		bool destroy = false;

		float lifespan = 0;

		Scene* m_scene = nullptr;
		Actor* m_parent = nullptr;

		std::vector<std::unique_ptr<Component>> m_components;
		std::vector<std::unique_ptr<Actor>> m_children;
	};

	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& component : m_components)
		{
			T* result = dynamic_cast<T*>(component.get());
			if (result) return result;
		}
		return nullptr;
	}
}
