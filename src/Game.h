#ifndef GAME_H
#define GAME_H

#include "AlexioConsoleEngine.h"
#include "JsonParser.h"

#include "Object.h"
#include "Map.h"

#include <memory>

class Game : public alexio::ConsoleEngine
{
public:
	Game();
	~Game();

	bool Start() override;
	bool Update() override;
private:
	std::array<bool, 5> mInput;
public:
	std::unique_ptr<JsonParser> jsonConfig;
	std::unique_ptr<JsonParser> jsonSave;	

	std::unique_ptr<Player> player;
	std::unique_ptr<Map> map;
};

inline std::unique_ptr<Game> game = std::make_unique<Game>();


#endif // !GAME_H