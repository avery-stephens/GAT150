#include "theNameOfTheGame.h"
#include "Engine.h"

void theNameOfTheGame::Initialize()
{
	m_scene = std::make_unique<gooblegorb::Scene>();

	rapidjson::Document document;
	std::vector<std::string>sceneNames = { "scenes/prefabs.txt", "scenes/Tilemap.txt", "scenes/level.txt" };

	for (auto& sceneName : sceneNames)
	{
		bool success = gooblegorb::json::Load(sceneName, document);
		if (!success)
		{
			LOG("!! ERROR !! could not load scene %s", sceneName.c_str());
			continue;
		}

		m_scene->Read(document);
	}
	
	m_scene->Initialize();

	for (int i = 0; i < 10; i++)
	{
		auto actor = gooblegorb::Factory::Instance().Create<gooblegorb::Actor>("Coin");
		actor->m_transform.position = { gooblegorb::randomf(0,800), 100.0f };
		actor->Initialize();

		m_scene->Add(std::move(actor));
	}
}

void theNameOfTheGame::Shutdown()
{
	m_scene->RemoveAll();
}

void theNameOfTheGame::Update()
{
	m_scene->Update();
}

void theNameOfTheGame::Draw(gooblegorb::Renderer& renderer)
{
	m_scene->Draw(renderer);
}
