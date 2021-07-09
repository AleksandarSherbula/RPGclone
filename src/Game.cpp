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
	player = std::make_unique<Player>(L"X", alexio::vec2(10, 10), alexio::FG_LIGHT_BLUE);
	map = std::make_unique<Map>();

	return true;
}

bool Game::Update()
{
	player->Behaviour();
	
	Clear();

	map->Draw();

	player->Draw();

	return !GetKeyPressed(alexio::ESCAPE);
}
