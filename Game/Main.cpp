#include <iostream>
#include "Engine.h"
//#include "Renderer/Texture.h"


int main() 
{
	gooblegorb::InitializeMemory();
	gooblegorb::SetFilePath("../Assets");

	rapidjson::Document document;
	bool success = gooblegorb::json::Load("json.txt", document);
	assert(success);

	std::string str;
	gooblegorb::json::Get(document, "string", str);
	std::cout << str << std::endl;

	bool b;
	gooblegorb::json::Get(document, "boolean", b);
	std::cout << b << std::endl;

	int i1;
	gooblegorb::json::Get(document, "integer1", i1);
	std::cout << i1 << std::endl;

	int i2;
	gooblegorb::json::Get(document, "integer2", i2);
	std::cout << i2 << std::endl;

	float f;
	gooblegorb::json::Get(document, "float", f);
	std::cout << f << std::endl;

	gooblegorb::Vector2 v2;
	gooblegorb::json::Get(document, "vector2", v2);
	std::cout << v2 << std::endl;

	gooblegorb::Color color;
	gooblegorb::json::Get(document, "color", color);
	std::cout << color << std::endl;

	//initialization
	gooblegorb::g_renderer.Initialize();
	gooblegorb::g_inputSystem.Initialize();
	gooblegorb::g_audioSystem.Initialize();
	gooblegorb::g_resources.Initialize();

	gooblegorb::Engine::Instance().Register();

	//create window
	gooblegorb::g_renderer.CreateWindow("Gooblegorber", 800, 600);
	gooblegorb::g_renderer.SetClearColor(gooblegorb::Color{ 0,0,0,255 });

	gooblegorb::Scene scene;

	bool quit = false;
	while (!quit)
	{
		gooblegorb::g_time.tick();
		gooblegorb::g_inputSystem.Update();
		gooblegorb::g_audioSystem.Update();

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

	gooblegorb::g_renderer.Shutdown();
	gooblegorb::g_audioSystem.Shutdown();
}