#pragma once
#include "Serialization/json.h"

#include "Core/Memory.h"
#include "Core/File.h"
#include "Core/Time.h"

#include "Math/MathUtils.h"
#include "Math/Random.h"

#include "Renderer/Renderer.h"
#include "Core/Time.h"

#include "Framework/Scene.h"
#include "Framework/Game.h"
#include "Framework/Factory.h"
#include "Framework/Singleton.h"

#include "Components/PlayerComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/AudioComponent.h"
#include "Components/CollisionComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/ModelComponent.h"
#include "Components/SpriteAnimComponent.h"
#include "Components/RBPhysicsComponent.h"
#include "Components/TextComponent.h"

#include "Renderer/Text.h"
#include "Renderer/Font.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Renderer/Texture.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Resource/ResourceManager.h"

#include "Physics/PhysicsSystem.h"

#include <memory>
#include <vector>
#include <list>

namespace gooblegorb
{
	extern InputSystem g_inputSystem;

	extern Renderer g_renderer;

	extern Time g_time;

	extern AudioSystem g_audioSystem;

	extern ResourceManager g_resources;

	extern PhysicsSystem g_physicsSystem;

	class Engine : public Singleton<Engine>
	{
	public:
		void Register();
	};
}