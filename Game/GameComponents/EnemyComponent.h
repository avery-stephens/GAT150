#pragma once
#include "Components/CharacterComponent.h"

class EnemyComponent : public gooblegorb::CharacterComponent
{
public:
	CLASS_DECLARATION(EnemyComponent)

	virtual void Initialize() override;
	virtual void Update() override;

	virtual void onCollisionEnter(gooblegorb::Actor* other) override;
	virtual void onCollisionExit(gooblegorb::Actor* other) override;

	virtual void OnNotify(const gooblegorb::Event& event) override;

	virtual bool Write(const rapidjson::Value& value) const override;
	virtual bool Read(const rapidjson::Value& value) override;

protected:
};