#include "EnemyComponent.h"
#include "Engine.h"
#include <iostream>

void EnemyComponent::Initialize()
{
    CharacterComponent::Initialize();
}

void EnemyComponent::Update()
{
    auto actor = m_owner->GetScene()->GetActorFromName("Player");
    if (actor)
    {
        gooblegorb::Vector2 direction = actor->m_transform.position - m_owner->m_transform.position;
        gooblegorb::Vector2 force = direction.Normalized() * speed;

        auto component = m_owner->GetComponent<gooblegorb::PhysicsComponent>();
        if (component) component->ApplyForce(force);
    }
}

void EnemyComponent::onCollisionEnter(gooblegorb::Actor* other)
{
    if (other->GetTag() == "Player")
    {
        gooblegorb::Event event;
        event.name = "EVENT_DAMAGE";
        event.data = damage;
        event.reciever = other;

        gooblegorb::g_eventManager.Notify(event);
    }
}

void EnemyComponent::onCollisionExit(gooblegorb::Actor* other)
{
    //
}

void EnemyComponent::OnNotify(const gooblegorb::Event& event)
{
    if (event.name == "EVENT_DAMAGE")
    {
        health -= std::get<float>(event.data);
        if (health <= 0)
        {
            gooblegorb::g_audioSystem.PlayAudio("enemyDeath");
            m_owner->SetDestroy();
        }
    }

}

bool EnemyComponent::Write(const rapidjson::Value& value) const
{
    return true;
}

bool EnemyComponent::Read(const rapidjson::Value& value)
{
    CharacterComponent::Read(value);

    return true;
}