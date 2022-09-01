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
		Scene(const Scene& other) {}
		Scene(Game* game) : m_game{ game } {}

		CLASS_DECLARATION(Scene)

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
		template<typename T = Actor>
		T* GetActorFromName(const std::string& name);

		template<typename T = Actor>
		std::vector<T*> GetActorsFromTag(const std::string& tag);

	private:
		Game* m_game = nullptr;
		std::list<std::unique_ptr<Actor>> m_actors;
		
	};

	template<typename T>
	inline T* Scene::GetActorFromName(const std::string& name)
	{
		for(auto& actor : m_actors) // !! for loop (range based) through m_actors 
		{
			if (actor.get()->GetName() == name)// !! compare name to actor GetName()
			{
				return dynamic_cast<T*>(actor.get()); // !! get() actor pointer); 
			}
		}
		
		return nullptr;
	}

	template<typename T>
	inline std::vector<T*> Scene::GetActorsFromTag(const std::string& tag)
	{
		std::vector<T*> result;

		for (auto& actor : m_actors)//  !! for loop (range based) through m_actors 
		{
			if (actor.get()->GetTag() == tag)//  !! compare name to actor GetName()) 
			{
				T* tagActor = dynamic_cast<T*>(actor.get());//  !! get() actor pointer); 

				if (tagActor)
				{
					result.push_back(tagActor);
				} //  !! push back tagActor to result vector 
			}
		}
		
		return result;
	}

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
