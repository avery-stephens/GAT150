#include "theNameOfTheGame.h"
#include "Engine.h"
#include "Framework/Event.h"
#include "GameComponents/EnemyComponent.h"

void theNameOfTheGame::Initialize()
{
	REGISTER_CLASS(EnemyComponent);

	gooblegorb::g_audioSystem.AddAudio("enemyDeath", "sounds/explosion.wav");
	gooblegorb::g_audioSystem.AddAudio("coin", "sounds/coinPickup.wav");
	gooblegorb::g_audioSystem.AddAudio("jump", "sounds/jumpyjump.wav");

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
	gooblegorb::g_eventManager.Subscribe("EVENT ADD_POINTS", std::bind(&theNameOfTheGame::OnNotify, this, std::placeholders::_1));
	gooblegorb::g_eventManager.Subscribe("EVENT_PLAYER_DEAD", std::bind(&theNameOfTheGame::OnNotify, this, std::placeholders::_1));
}

void theNameOfTheGame::Shutdown()
{
	m_scene->RemoveAll();
}

void theNameOfTheGame::Update()
{
	switch (m_gameState)
	{
	case gameState::titleScreen:
		if (gooblegorb::g_inputSystem.GetKeyState(gooblegorb::key_space) == gooblegorb::InputSystem::KeyState::Pressed)
		{
			m_scene->GetActorFromName("Title")->SetActive(false);
			m_gameState = gameState::startLevel;
		}

		if (gooblegorb::g_inputSystem.GetKeyState(gooblegorb::key_W) == gooblegorb::InputSystem::KeyState::Pressed)
		{
			m_scene->GetActorFromName("Title")->SetActive(false);
			m_gameState = gameState::startLevel;
		}

		break;

	case gameState::startLevel:
	{

		m_scene->GetActorFromName("Title2")->SetActive(false);

		for (int i = 0; i < 2; i++)
		{
			auto actor = gooblegorb::Factory::Instance().Create<gooblegorb::Actor>("Creature");
			actor->m_transform.position = { gooblegorb::randomf(0,1000), 100.0f };
			actor->Initialize();
			m_scene->Add(std::move(actor));
		}

		for (int i = 0; i < 5; i++)
		{
			auto actor = gooblegorb::Factory::Instance().Create<gooblegorb::Actor>("Coin");
			actor->m_transform.position = { gooblegorb::randomf(0,1000), 200.0f };
			actor->Initialize();
			m_scene->Add(std::move(actor));
		}

		{
			auto actor = gooblegorb::Factory::Instance().Create<gooblegorb::Actor>("Player");
			actor->m_transform.position = { 500.0f, 550.0f };
			actor->Initialize();
			m_scene->Add(std::move(actor));

		}

		/*for (int i = 0; i < gooblegorb::randomf(0, 5); i++)
			{
				auto actor = gooblegorb::Factory::Instance().Create<gooblegorb::Actor>("HealthFoods");
				actor->m_transform.position = { gooblegorb::randomf(0,800), 100.0f };
				actor->Initialize();
				spawner = gooblegorb::random(6, 10);
				m_scene->Add(std::move(actor));
			}*/

		m_lives = 3;

		m_gameState = gameState::game;
		break;
	}
	case gameState::game:
	{
		auto actor = m_scene->GetActorFromName("Score");
		auto component = actor->GetComponent<gooblegorb::TextComponent>();

		component->SetText(std::to_string(m_score));

		m_scene->GetActorFromName("Score")->SetActive(true);
	}
	{
		auto actor2 = m_scene->GetActorFromName("Health");
		auto component2 = actor2->GetComponent<gooblegorb::TextComponent>();

		auto player = m_scene->GetActorFromName("Player");
		if (player)
		{
			auto playercomponent = player->GetComponent<gooblegorb::PlayerComponent>();
			component2->SetText(std::to_string((int)playercomponent->health));
		}

		m_scene->GetActorFromName("Health")->SetActive(true);
	}

	Spawn();
	break;

	case gameState::playerDead:
		m_stateTimer -= gooblegorb::g_time.deltaTime;

		if (m_stateTimer <= 0)
		{
			m_gameState = gameState::startLevel;
			m_gameState = (m_lives > 0) ? gameState::startLevel : gameState::gameOver;
		}

		m_scene->GetActorFromName("Title2")->SetActive(true);

		break;

	case gameState::gameOver:
		m_scene->GetActorFromName("Title2")->SetActive(true);
		break;

	default:
		break;
	}

	m_scene->Update();
}

void theNameOfTheGame::Draw(gooblegorb::Renderer& renderer)
{
	m_scene->Draw(renderer);
}

void theNameOfTheGame::OnAddPoints(const gooblegorb::Event& event)
{
	AddPoints(std::get<int>(event.data));

	std::cout << event.name << std::endl;
	std::cout << GetScore() << std::endl;
}

void theNameOfTheGame::OnPlayerDead(const gooblegorb::Event& event)
{
	m_gameState = gameState::playerDead;
	m_lives--;
	m_stateTimer = 3;
}

void theNameOfTheGame::Spawn()
{
	coinTimer -= gooblegorb::g_time.deltaTime;
	if (coinTimer <= 0)
	{
		//coins
		for (int i = 0; i < gooblegorb::randomf(1, 4); i++)
		{
			auto actor = gooblegorb::Factory::Instance().Create<gooblegorb::Actor>("Coin");
			actor->m_transform.position = { gooblegorb::randomf(0, 1000), 100.0f };
			actor->Initialize();

			m_scene->Add(std::move(actor));
		}
		coinTimer = gooblegorb::random(100, 350);
	}

	enemyTimer -= gooblegorb::g_time.deltaTime;
	if (enemyTimer <= 0)
	{
		//ENEMIES
		for (int i = 0; i < 2; i++)
		{
			auto actor = gooblegorb::Factory::Instance().Create<gooblegorb::Actor>("Creature");
			actor->m_transform.position = { gooblegorb::randomf(0, 1000), 100.0f };
			actor->Initialize();

			m_scene->Add(std::move(actor));
		}
		enemyTimer = gooblegorb::random(300, 550);
	}
}

void theNameOfTheGame::OnNotify(const gooblegorb::Event& event)
{
	if (event.name == "EVENT ADD_POINTS") 
	{
		AddPoints(std::get<int>(event.data));
	}

	if (event.name == "EVENT_PLAYER_DEAD")
	{
		OnPlayerDead(event);
	}
}
