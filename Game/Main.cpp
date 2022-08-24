#include <iostream>
#include "Engine.h"
//#include "Renderer/Texture.h"


int main() 
{
	gooblegorb::InitializeMemory();
	gooblegorb::SetFilePath("../Assets");

	//initialization
	gooblegorb::g_renderer.Initialize();
	gooblegorb::g_inputSystem.Initialize();
	gooblegorb::g_audioSystem.Initialize();
	gooblegorb::g_resources.Initialize();
	gooblegorb::g_physicsSystem.Initialize();

	gooblegorb::Engine::Instance().Register();

	//create window
	gooblegorb::g_renderer.CreateWindow("Gooblegorber", 800, 600);
	gooblegorb::g_renderer.SetClearColor(gooblegorb::Color{ 0,0,0,255 });
	
	//create scene
	gooblegorb::Scene scene;

	rapidjson::Document document;
	bool success = gooblegorb::json::Load("level.txt", document);

	scene.Read(document);
	scene.Initialize();

	bool quit = false;
	while (!quit)
	{
		gooblegorb::g_time.tick();
		gooblegorb::g_inputSystem.Update();
		gooblegorb::g_audioSystem.Update();
		gooblegorb::g_physicsSystem.Update();

		if (gooblegorb::g_inputSystem.GetKeyState(gooblegorb::key_escape) == gooblegorb::InputSystem::KeyState::Pressed) quit = true;
		
		//update scene
		scene.Update();

		//title.Draw(gooblegorb::g_renderer, {400,300});

		//std::cout << gooblegorb::g_time.deltaTime << std::endl;

		//render stuff
		gooblegorb::g_renderer.BeginFrame();

		scene.Draw(gooblegorb::g_renderer);

		gooblegorb::g_renderer.EndFrame();
	}
	scene.RemoveAll();

	gooblegorb::g_resources.Shutdown();
	gooblegorb::g_audioSystem.Shutdown();
	gooblegorb::g_inputSystem.Shutdown();
	gooblegorb::g_physicsSystem.Shutdown();
	gooblegorb::g_renderer.Shutdown();
}