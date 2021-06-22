#include "Game.h"

Game::Game()
{
	sAppName = L"RPG clone";
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
	if (GetKeyPressed(alexio::W))
		pos.y--;
	if (GetKeyPressed(alexio::S))
		pos.y++;
	if (GetKeyPressed(alexio::A))
		pos.x--;
	if (GetKeyPressed(alexio::D))
		pos.x++;

	Clear();

	DrawChar(pos, player, alexio::FG_BLUE);

	return !GetKeyPressed(alexio::ESCAPE);
}
