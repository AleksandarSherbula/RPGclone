#ifndef GAME_H
#define GAME_H

#include "AlexioConsoleEngine.h"

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
};

inline std::unique_ptr<Game> game = std::make_unique<Game>();


#endif // !GAME_H