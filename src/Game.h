#ifndef GAME_H
#define GAME_H

#include "AlexioConsoleEngine.h"
#include "JsonParser.h"

#include <memory>

class Game : public alexio::ConsoleEngine
{
public:
	Game();
	~Game();

	bool Start() override;
	bool Update() override;
public:
	char player;	
	alexio::vec2 pos;
	std::unique_ptr<JsonParser> config_json;
	std::unique_ptr<JsonParser> save_json;
};

inline std::unique_ptr<Game> game = std::make_unique<Game>();


#endif // !GAME_H