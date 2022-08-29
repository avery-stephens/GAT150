#pragma once
#include "Framework/Game.h"

class theNameOfTheGame : public gooblegorb::Game 
{
public:
	virtual void Initialize() override;
	virtual void Shutdown() override;
	virtual void Update() override;
	virtual void Draw(gooblegorb::Renderer& renderer) override;
};
