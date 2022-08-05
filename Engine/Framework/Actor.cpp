#include "Actor.h"
#include "Components/RendererComponent.h"

namespace gooblegorb 
{
	void Actor::Update()
	{
		for (auto& component : m_components)
		{
			component->Update();
		}
	}
	void gooblegorb::Actor::Draw(Renderer& renderer)
	{
		for (auto& component : m_components)
		{
			auto renderComponent = dynamic_cast<RendererComponent*>(component.get());
			if (renderComponent)
			{
				renderComponent->Draw(renderer);
			}
			//component->Update();
		}


		//m_model.Draw(renderer, m_transform.position, m_transform.rotation, m_transform.scale);
	}
	void Actor::AddComponent(std::unique_ptr<Component> component)
	{
		component->m_owner = this;
		m_components.push_back(std::move(component));
	}
}
