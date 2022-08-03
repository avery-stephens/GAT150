#include <iostream>
#include "Engine.h"
#include <Texture.h>


int main() 
{
	std::cout << "Hello World and to your ma" << std::endl;

	gooblegorb::InitializeMemory();
	gooblegorb::SetFilePath("../Assets");

	gooblegorb::g_renderer.Initialize();
	gooblegorb::g_inputSystem.Initialize();
	gooblegorb::g_audioSystem.Initialize();

	gooblegorb::g_renderer.CreateWindow("bullhonky. thats what this is", 800, 600);

	std::shared_ptr<gooblegorb::Texture> texture = std::make_shared<gooblegorb::Texture>();
	texture->Create(gooblegorb::g_renderer, "incrediblySadBeing.png");

	bool quit = false;
	while (!quit)
	{
		gooblegorb::g_inputSystem.Update();
		gooblegorb::g_time.tick();
		gooblegorb::g_audioSystem.Update();

		if (gooblegorb::g_inputSystem.GetKeyState(gooblegorb::key_escape) == gooblegorb::InputSystem::KeyState::Pressed) quit = true;
		//update stuff
		//title.Draw(neu::g_renderer, {400,300});

		//std::cout << neu::g_time.deltaTime << std::endl;

		//render stuff
		gooblegorb::g_renderer.BeginFrame();

		gooblegorb::g_renderer.Draw(texture, { 100,100 }, 0);

		gooblegorb::g_renderer.EndFrame();
	}

	gooblegorb::g_renderer.Shutdown();
	gooblegorb::g_audioSystem.Shutdown();
}