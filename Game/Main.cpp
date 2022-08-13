#include <iostream>
#include "Engine.h"
//#include "Renderer/Texture.h"

int main() 
{
	//constexpr int i = 5;

	int i = 10;
	float f = 3.5f;
	bool b = false;

	const char* s = "jo mama mf";

	//std::cout << NAME << std::endl;
	//std::cout << __FILE__ << std::endl;
	//std::cout << __LINE__ << std::endl;
	//std::cout << __FUNCTION__ << std::endl;

	//printf("hello foolish fools %d %.2f %s\n",i,f,s);

	std::cout << "Hallo hallo" << std::endl;

	gooblegorb::InitializeMemory();
	gooblegorb::SetFilePath("../Assets");

	//initialization
	gooblegorb::g_renderer.Initialize();
	gooblegorb::g_inputSystem.Initialize();
	gooblegorb::g_audioSystem.Initialize();
	gooblegorb::g_resources.Initialize();

	//create window
	gooblegorb::g_renderer.CreateWindow("bullhonky. thats what this is", 800, 600);
	gooblegorb::g_renderer.SetClearColor(gooblegorb::Color{ 0,0,0,255 });

	//load assets
	//std::shared_ptr<gooblegorb::Texture> texture = std::make_shared<gooblegorb::Texture>();
	//texture->Create(gooblegorb::g_renderer, "Textures/spaceShips_004.png");
	std::shared_ptr<gooblegorb::Texture> texture = gooblegorb::g_resources.Get<gooblegorb::Texture>("Textures/spaceShips_004.png",&gooblegorb::g_renderer);

	//std::shared_ptr<gooblegorb::Model> model = std::make_shared<gooblegorb::Model>();
	//model->Create("Model.txt");

	//std::shared_ptr<gooblegorb::Model> model = gooblegorb::g_resources.Get<gooblegorb::Model>("Model.txt");
	//std::shared_ptr<gooblegorb::Model> model2 = gooblegorb::g_resources.Get<gooblegorb::Model>("Model.txt");

	gooblegorb::g_audioSystem.AddAudio("laser", "Laser_Shoot33.wav");

	//create actors
	gooblegorb::Scene scene;

	gooblegorb::Transform transform{ gooblegorb::Vector2{400,300}, 90, {3,3}} ;

	std::unique_ptr<gooblegorb::Actor> actor = std::make_unique <gooblegorb::Actor>(transform);
	std::unique_ptr<gooblegorb::PlayerComponent> pcomponent = std::make_unique <gooblegorb::PlayerComponent>();
	actor->AddComponent(std::move(pcomponent));
	
	std::unique_ptr<gooblegorb::ModelComponent> mcomponent = std::make_unique <gooblegorb::ModelComponent>();
	mcomponent->m_model = gooblegorb::g_resources.Get<gooblegorb::Model>("Model.txt");
	actor->AddComponent(std::move(mcomponent));

	//std::unique_ptr<gooblegorb::SpriteComponent> scomponent = std::make_unique <gooblegorb::SpriteComponent>();
	//scomponent->m_texture = texture;
	//actor->AddComponent(std::move(scomponent));

	std::unique_ptr<gooblegorb::AudioComponent> acomponent = std::make_unique<gooblegorb::AudioComponent>();
	acomponent->m_soundName = "laser";
	actor->AddComponent(std::move(acomponent));

	std::unique_ptr<gooblegorb::PhysicsComponent> phcomponent = std::make_unique<gooblegorb::PhysicsComponent>();
	actor->AddComponent(std::move(phcomponent));

	//childrens
	gooblegorb::Transform transformC{ gooblegorb::Vector2{10,10}, 0, {1,1} };
	std::unique_ptr<gooblegorb::Actor> child = std::make_unique <gooblegorb::Actor>(transformC);

	std::unique_ptr<gooblegorb::ModelComponent> mcomponentC = std::make_unique <gooblegorb::ModelComponent>();
	mcomponentC->m_model = gooblegorb::g_resources.Get<gooblegorb::Model>("Model.txt");
	child->AddComponent(std::move(mcomponentC));

	actor->AddChild(std::move(child));

	scene.Add(std::move(actor));

	float angle = 0;

	bool quit = false;
	while (!quit)
	{
		gooblegorb::g_time.tick();
		gooblegorb::g_inputSystem.Update();
		gooblegorb::g_audioSystem.Update();

		if (gooblegorb::g_inputSystem.GetKeyState(gooblegorb::key_escape) == gooblegorb::InputSystem::KeyState::Pressed) quit = true;
		
		//update scene
		angle += 180.0f * gooblegorb::g_time.deltaTime;
		scene.Update();

		//title.Draw(neu::g_renderer, {400,300});

		//std::cout << neu::g_time.deltaTime << std::endl;

		//render stuff
		gooblegorb::g_renderer.BeginFrame();

		scene.Draw(gooblegorb::g_renderer);

		gooblegorb::g_renderer.EndFrame();
	}

	gooblegorb::g_renderer.Shutdown();
	gooblegorb::g_audioSystem.Shutdown();
}