#ifndef GAME_H
#define GAME_H

#include "AlexioConsoleEngine.h"
#include "JsonParser.h"

#include "Object.h"
#include "Map.h"

#include <memory>
#include <vector>
#include <chrono>
#include <thread>

typedef std::chrono::time_point<std::chrono::system_clock> CurrentTime;

class Game : public alexio::ConsoleEngine
{
public:
	std::unique_ptr<JsonParser> jsonConfig;
	std::unique_ptr<JsonParser> jsonMap;
	std::unique_ptr<JsonParser> jsonSave;

	std::unique_ptr<Map> map;

	std::unique_ptr<Player> player;
	std::vector<std::unique_ptr<Object>> objects;

	int timer;
	unsigned int turns;
	CurrentTime start;
	CurrentTime end;

	bool showAdvancedStats;
public:
	Game();
	~Game();

	bool Start() override;
	bool Update() override;

	inline CurrentTime Now() { return std::chrono::system_clock::now(); }

	void DrawStats();
};

inline std::unique_ptr<Game> game = std::make_unique<Game>();


#endif // !GAME_H