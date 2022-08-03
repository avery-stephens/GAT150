#pragma once
#include "Core/Memory.h"
#include "Core/File.h"

#include "Math/MathUtils.h"
#include "Math/Random.h"

#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Core/Time.h"

#include "Framework/Scene.h"
#include "Framework/Game.h"

#include "Renderer/Text.h"
#include "Renderer/Font.h"

#include "Audio/AudioSystem.h"

#include <memory>
#include <vector>
#include <list>

namespace gooblegorb
{
	extern InputSystem g_inputSystem;

	extern Renderer g_renderer;

	extern Time g_time;

	extern AudioSystem g_audioSystem;
}