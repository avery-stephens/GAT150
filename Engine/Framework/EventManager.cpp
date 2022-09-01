#include "EventManager.h"

void gooblegorb::EventManager::Initialize()
{
	//
}

void gooblegorb::EventManager::Shutdown()
{
	//
}

void gooblegorb::EventManager::Update()
{
	//
}

void gooblegorb::EventManager::Subscribe(const std::string& name, Event::functionPtr function, GameObject* receiver)
{
	Observer observer;
	observer.reciever = receiver;
	observer.function = function;

	m_events[name].push_back(observer);
}

void gooblegorb::EventManager::Unsubscribe(const std::string& name, GameObject* reciever)
{
	// get list of observers for event
	auto& observers = m_events[name];

	// remove observer with matching receiver from observers
	for (auto iter = observers.begin(); iter != observers.end(); iter++)
	{
		if (iter->reciever == reciever)
		{
			observers.erase(iter);
			break;
		}
	}
}

void gooblegorb::EventManager::Notify(const Event& _event)
{
	auto& observers = m_events[_event.name];

	for (auto& observer : observers)
	{
		if (_event.reciever == nullptr || _event.reciever == observer.reciever)
		{
			observer.function(_event);
		}
	}
}
