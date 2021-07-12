#include "Game.h"

#include "olcResourcePack.h"

Game::Game()
{
	//std::unique_ptr<olc::ResourcePack> pack = std::make_unique<olc::ResourcePack>();
	//pack->LoadPack("data/save_state/save.state", "SaveLexio");
	//olc::ResourceBuffer rb = pack->GetFileBuffer("data/save_state/save1.json");

	sAppName = L"RPG clone";
	jsonConfig = std::make_unique<JsonParser>("data/config/config.json");
	jsonSave = std::make_unique<JsonParser>("data/save_state/save1.json");
	//jsonSave = std::make_unique<JsonParser>(rb.vMemory);

	//pack->AddFile("data/save_state/save1.json");
	//pack->SavePack("data/save_state/save.state", "SaveLexio");

	nConsoleScreenWidth = jsonConfig->GetJSON()["ConsoleWidth"];
	nConsoleScreenHeight = jsonConfig->GetJSON()["ConsoleHeight"];	
}

Game::~Game()
{
}

bool Game::Start()
{
	map = std::make_unique<Map>();

	turns = 0;

	start = Now();

	player = std::make_unique<Player>(L"B", alexio::vec2(10, 10), alexio::FG_LIGHT_BLUE);

	objects.push_back(std::make_unique<Enemy>(L"X", alexio::vec2(40, 20), alexio::FG_RED, player.get()));
	objects.push_back(std::make_unique<Enemy>(L"X", alexio::vec2(50, 2), alexio::FG_RED,  player.get()));
	objects.push_back(std::make_unique<Enemy>(L"X", alexio::vec2(58, 24), alexio::FG_RED, player.get()));

	return true;
}

bool Game::Update()
{
	if (turns == 0)
		player->Behaviour();
	else
	{
		if (turns <= objects.size() && timer >= 1)
		{
			objects[turns - 1]->Behaviour();
			turns++;
			start = Now();
		}

		if (turns > objects.size())
			turns = 0;

		CurrentTime end = Now();
		timer = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
	}	
	
	Clear();

	map->Draw();

	for (auto& obj : objects)
		obj->Draw();

	player->Draw();

	return !GetKeyPressed(alexio::ESCAPE);
}
