#include "Game.h"

#include "olcResourcePack.h"

Game::Game()
{
	//std::unique_ptr<olc::ResourcePack> pack = std::make_unique<olc::ResourcePack>();
	//pack->LoadPack("data/save_state/save.state", "SaveLexio");
	//olc::ResourceBuffer rb = pack->GetFileBuffer("data/save_state/save1.json");

	sAppName = L"RPG clone";
	jsonConfig = std::make_unique<JsonParser>("data/config/config.json");
	jsonMap = std::make_unique<JsonParser>("data/config/mapData.json");
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

	player = std::make_unique<Player>("Player");

	for (int y = 0; y < map->nHeight; y++)
		for (int x = 0; x < map->nWidth; x++)
		{
			char tileID = map->GetTile(x, y);
			switch (tileID)
			{
			case 'x': objects.push_back(std::make_unique<Enemy>("SmallEnemies", alexio::vec2(x, y))); map->SetTile(x, y, '0'); break;
			case 'X': objects.push_back(std::make_unique<Enemy>("Enemies", alexio::vec2(x, y))); map->SetTile(x, y, '0'); break;
			case 'p': objects.push_back(std::make_unique<HealthBoost>("SmallHealthBoost", L"\x2022", alexio::vec2(x, y))); break;
			case 'P': objects.push_back(std::make_unique<HealthBoost>("HealthBoost", L"\x2665", alexio::vec2(x, y))); break;
			}
		}

	showAdvancedStats = false;

	return true;
}

bool Game::Update()
{
	if (jsonConfig->GetKeyPressed("AdvancedStats"))
		showAdvancedStats = !showAdvancedStats;

	if (turns == 0)
		player->Behaviour();
	else
	{
		if (turns <= objects.size())
		{
			if ((objects[turns - 1]->GetName() == "Enemies" || objects[turns - 1]->GetName() == "SmallEnemies"))
			{
				if (timer >= 1)
				{
					objects[turns - 1]->Behaviour();
					turns++;
					start = Now();
				}
			}
			else
				turns++;

			CurrentTime end = Now();
			timer = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
		}
		else
			turns = 0;
	}	
	
	Clear();

	map->Draw();

	for (auto& obj : objects)
		obj->Draw();

	player->Draw();

	DrawStats();

	return !GetKeyPressed(alexio::ESCAPE);
}

void Game::DrawStats()
{
	DrawWideString(alexio::vec2(0, 0), L"-----------------");	
	DrawWideString(alexio::vec2(0, 1), L"|   HP: " + std::to_wstring(player->GetHealth()) + L"/" + std::to_wstring(player->GetMaxHealth()) + L"   |");
	DrawWideString(alexio::vec2(0, 2), L"-----------------");

	if (showAdvancedStats)
	{
		DrawWideString(alexio::vec2(0, 30), L"-----------------");
		DrawWideString(alexio::vec2(0, 31), L"| Health: " + std::to_wstring(player->GetHealth()) + L"/" + std::to_wstring(player->GetMaxHealth()) + L" |");
		DrawWideString(alexio::vec2(0, 32), L"| Damage: " + std::to_wstring(player->GetDamage()) + L"     |");
		DrawWideString(alexio::vec2(0, 33), L"| Armor:  " + std::to_wstring(player->GetArmor()) + L"     |");
		DrawWideString(alexio::vec2(0, 34), L"-----------------");
	}
}
