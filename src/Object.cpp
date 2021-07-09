#include "Object.h"
#include "Game.h"

Object::Object()
{
}

Object::Object(const std::wstring& id, const alexio::vec2& position, const int color)
{
	mID = id;
	mPosition = position;
	mColor = color;
}

Object::~Object()
{
}

void Object::SetID(const std::wstring& id)
{
	mID = id;
}

void Object::SetPosition(const alexio::vec2& position)
{
	mPosition = position;
}

void Object::SetColor(const int color)
{
	mColor = color;
}

void Object::Behaviour()
{
}

void Object::Draw()
{
	game->DrawWideString(mPosition, mID, mColor);
}

void Object::Draw(const std::wstring& id, const alexio::vec2& position, const int color)
{
	game->DrawWideString(position, id, color);
}

Player::Player()
{
	mID = L"X";
	mPosition = alexio::vec2(0, 0);
	mColor = alexio::FG_WHITE;
}

Player::Player(const std::wstring& id, const alexio::vec2& position, const int color)
{
	mID = id;
	mPosition = position;
	mColor = color;
}

void Player::Behaviour()
{
	mDirection = alexio::vec2(0, 0);

	if (game->jsonConfig->GetKeyPressed("Up") &&
		!game->map->isSolid(alexio::vec2(mPosition.x, mPosition.y - 1)))
	{
		mDirection.y--;
	}
	if (game->jsonConfig->GetKeyPressed("Down") &&
		!game->map->isSolid(alexio::vec2(mPosition.x, mPosition.y + 1)))
	{
		mDirection.y++;
	}
	if (game->jsonConfig->GetKeyPressed("Left") &&
		!game->map->isSolid(alexio::vec2(mPosition.x - 1, mPosition.y)))
	{
		mDirection.x--;
	}
	if (game->jsonConfig->GetKeyPressed("Right") &&
		!game->map->isSolid(alexio::vec2(mPosition.x + 1, mPosition.y)))
	{
		mDirection.x++;
	}

	mPosition += mDirection;
}