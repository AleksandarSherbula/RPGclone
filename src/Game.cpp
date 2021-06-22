#include "Game.h"

Game::Game()
{
	sAppName = L"RPG clone";
	config_json = std::make_unique<JsonParser>("data/config/config.json");

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

	Clear();

	DrawChar(pos, player, alexio::FG_BLUE);

	return !GetKeyPressed(alexio::ESCAPE);
}
