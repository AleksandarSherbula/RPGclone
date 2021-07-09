#ifndef MAP_H
#define MAP_H

#include <string>

#include "AlexioConsoleEngine.h"

class Map
{
private:
	std::string mJsonData;
public:
	int nWidth;
	int nHeight;
public:
	Map();

	char GetTile(int x, int y);
	char GetTile(const alexio::vec2& id);

	void SetTile(int x, int y, char c);
	void SetTile(const alexio::vec2& id, char c);

	bool isSolid(const alexio::vec2& position);

	void Draw();
};


#endif // !MAP_H