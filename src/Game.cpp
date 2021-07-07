#include "Game.h"

#include "olcResourcePack.h"

Game::Game()
{
	//std::unique_ptr<olc::ResourcePack> pack = std::make_unique<olc::ResourcePack>();
	//pack->LoadPack("data/save_state/save.state", "SaveLexio");
	//olc::ResourceBuffer rb = pack->GetFileBuffer("data/save_state/save1.json");

	sAppName = L"RPG clone";
	config_json = std::make_unique<JsonParser>("data/config/config.json");
	save_json = std::make_unique<JsonParser>("data/save_state/save1.json");
	//save_json = std::make_unique<JsonParser>(rb.vMemory);

	//pack->AddFile("data/save_state/save1.json");
	//pack->SavePack("data/save_state/save.state", "SaveLexio");

	nConsoleScreenWidth = config_json->GetJSON()["ConsoleWidth"];
	nConsoleScreenHeight = config_json->GetJSON()["ConsoleHeight"];	
}

Game::~Game()
{
}

bool Game::Start()
{
	player = 'X';
	pos = alexio::vec2(10, 10);

	return true;
}

bool Game::Update()
{
	if (config_json->GetKeyPressed("Up"))
		pos.y--;
	if (config_json->GetKeyPressed("Down"))
		pos.y++;
	if (config_json->GetKeyPressed("Left"))
		pos.x--;
	if (config_json->GetKeyPressed("Right"))
		pos.x++;

	if (GetKeyPressed(alexio::F1))
	{
		save_json->GetJObject("Position", 0) = pos.x;
		save_json->GetJObject("Position", 1) = pos.y;
		save_json->SaveData();
	}

	if (GetKeyPressed(alexio::F2))
	{
		pos = alexio::vec2(save_json->GetInt("Position", 0), save_json->GetInt("Position", 1));
	}

	Clear();

	DrawChar(pos, player, alexio::FG_BLUE);	

	return !GetKeyPressed(alexio::ESCAPE);
}
