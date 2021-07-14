#include "Map.h"
#include "Game.h"

Map::Map()
{
	nWidth = game->jsonMap->GetString("Map", 0).size();
	nHeight = game->jsonMap->GetArraySize("Map");
	
	for (int i = 0; i < nHeight; i++)
		mJsonData += game->jsonMap->GetString("Map", i);
}

char Map::GetTile(int x, int y)
{
	if (x >= 0 && x < nWidth && y >= 0 && y < nHeight)
		return mJsonData[y * nWidth + x];
	else
		return ' ';
}

char Map::GetTile(const alexio::vec2& id)
{
	return GetTile(id.x, id.y);
}

void Map::SetTile(int x, int y, char c)
{
	if (x >= 0 && x < nWidth && y >= 0 && y < nHeight)
		mJsonData[y * nWidth + x] = c;
}

void Map::SetTile(const alexio::vec2& id, char c)
{
	SetTile(id.x, id.y, c);
}

bool Map::isSolid(int x, int y)
{
	return GetTile(x, y) == '8' ||
		GetTile(x, y) == '9';
}

bool Map::isSolid(const alexio::vec2& position)
{
	return isSolid(position.x, position.y);
}

void Map::Draw()
{
	for (int y = 0; y < nHeight; y++)
		for (int x = 0; x < nWidth; x++)
		{
			char tileID = GetTile(x, y);

			switch (tileID)
			{
			case '0': game->DrawWideString(alexio::vec2(x, y), L"\x2592", alexio::FG_GREEN); break;
			case '8': game->DrawWideString(alexio::vec2(x, y), L"\x2248", alexio::FG_BLUE); break;
			case '9': game->DrawWideString(alexio::vec2(x, y), L"\x2593", alexio::FG_WHITE); break;
			}
		}

}
