#pragma once
#include "Framework/Game.h"
#include "Framework/Event.h"

class theNameOfTheGame : public gooblegorb::Game, public gooblegorb::INotify
{
public:
	enum class gameState
	{
		titleScreen,
		startLevel,
		game,
		playerDead,
		gameOver
	};

public:
	virtual void Initialize() override;
	virtual void Shutdown() override;
	virtual void Update() override;
	virtual void Draw(gooblegorb::Renderer& renderer) override;
	virtual void OnNotify(const gooblegorb::Event& event) override;

	void OnAddPoints(const gooblegorb::Event& _event);
	void OnPlayerDead(const gooblegorb::Event& _event);
	void Spawn();

private:
	gameState m_gameState = gameState::titleScreen;
	float m_stateTimer = 0;
	int m_lives = 3;

	int coinTimer = 0;
	int enemyTimer = 0;

	// Inherited via INotify
};
