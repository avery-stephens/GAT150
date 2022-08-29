#include "CollisionComponent.h"
#include "Engine.h"
#include <iostream>

namespace gooblegorb
{

    void CollisionComponent::Initialize()
    {
        auto component = m_owner->GetComponent<RBPhysicsComponent>();
        if (component)
        {
            // if data was not set, get size from render component source rect 
            if (data.size.x == 0 && data.size.y == 0)// !! check data.size.x == 0 and data.size.y == 0) 
            {
                auto renderComponent = m_owner->GetComponent<RendererComponent>();// !! check render component from the owner 
                if (renderComponent)
                {
                    data.size = Vector2{ renderComponent->GetSource().w, renderComponent->GetSource().h }; // !! render component source.w, render component source.h };
                }
            }

            g_physicsSystem.SetCollisionBox(component->m_body, data, m_owner);
        }

    }

    void CollisionComponent::Update()
    {
    }

    void CollisionComponent::onCollisionEnter(Actor* other)
    {
        if(m_enterFunction) m_enterFunction(other);
        //std::cout << other->GetName() << std::endl;
    }

    void CollisionComponent::onCollisionExit(Actor* other)
    {
        if(m_exitFunction) m_exitFunction(other);
        //std::cout << other->GetName() << std::endl;
    }

    bool CollisionComponent::Write(const rapidjson::Value& value) const
    {
        return true;
    }

    bool CollisionComponent::Read(const rapidjson::Value& value)
    {

        READ_DATA(value, data.size);
        READ_DATA(value, data.density);
        READ_DATA(value, data.friction);
        READ_DATA(value, data.restitution);
        READ_DATA(value, data.isTrigger);

        return true;
    }
}
