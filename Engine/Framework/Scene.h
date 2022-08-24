#pragma once
#include "Actor.h"
#include <list>
#include <memory>

namespace gooblegorb
{
	//class Actor;
	class Actor;
	class Renderer;
	class Game;

	class Scene : public GameObject, public ISerializable
	{
	public:
		Scene() = default;
		~Scene() = default;
		Scene(Game* game) : m_game{ game } {}

		void Update() override;
		void Initialize() override;
		void Draw(Renderer& renderer);

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		void Add(std::unique_ptr<Actor> actor);
		void RemoveAll();

		template<typename T>
		T* GetActor();

		Game* GetGame() { return m_game; }

	private:
		Game* m_game = nullptr;
		std::list<std::unique_ptr<Actor>> m_actors;
		
		// Inherited via ISerializable

	};

	template<typename T>
	inline T* Scene::GetActor()
	{
		//int i = 45;
		//float f = static_cast<float>(i);
		for (auto& actor : m_actors)
		{
			T* result = dynamic_cast<T*>(actor.get());
			if (result) return result;
		}
		return nullptr;
	}
}
