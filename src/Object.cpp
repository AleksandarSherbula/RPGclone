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

DynamicObject::DynamicObject()
{
	mID = L"X";
	mPosition = alexio::vec2(0, 0);
	mColor = alexio::FG_WHITE;
	mDirection = alexio::vec2(0, 0);
}

DynamicObject::DynamicObject(const std::wstring& id, const alexio::vec2& position, const int color)
{
	mID = id;
	mPosition = position;
	mColor = color;
	mDirection = alexio::vec2(0, 0);
}

Player::Player() : DynamicObject()
{
}

Player::Player(const std::wstring& id, const alexio::vec2& position, const int color) : DynamicObject(id, position, color)
{
}

void Player::Behaviour()
{
	mDirection = alexio::vec2(0, 0);

	if (game->jsonConfig->GetKeyPressed("Up") &&
		!game->map->isSolid(alexio::vec2(mPosition.x, mPosition.y - 1)))
	{
		mDirection.y--;
		game->turns++;
		game->start = std::chrono::system_clock::now();
	}
	if (game->jsonConfig->GetKeyPressed("Down") &&
		!game->map->isSolid(alexio::vec2(mPosition.x, mPosition.y + 1)))
	{
		mDirection.y++;
		game->turns++;
		game->start = std::chrono::system_clock::now();
	}
	if (game->jsonConfig->GetKeyPressed("Left") &&
		!game->map->isSolid(alexio::vec2(mPosition.x - 1, mPosition.y)))
	{
		mDirection.x--;
		game->turns++;
		game->start = std::chrono::system_clock::now();
	}
	if (game->jsonConfig->GetKeyPressed("Right") &&
		!game->map->isSolid(alexio::vec2(mPosition.x + 1, mPosition.y)))
	{
		mDirection.x++;
		game->turns++;
		game->start = std::chrono::system_clock::now();
	}

	mPosition += mDirection;
}

Enemy::Enemy() : DynamicObject()
{
	mPlayer = nullptr;
}

Enemy::Enemy(const std::wstring& id, const alexio::vec2& position, const int color, Player* player) : DynamicObject(id, position, color)
{
	mPlayer = player;
}

void Enemy::Behaviour()
{
	mDirection = alexio::vec2(0, 0);
	
	alexio::vec2 targetToUp = mPlayer->GetPosition() - alexio::vec2(mPosition.x, mPosition.y - 1);
	alexio::vec2 targetToLeft = mPlayer->GetPosition() - alexio::vec2(mPosition.x - 1, mPosition.y);
	alexio::vec2 targetToDown = mPlayer->GetPosition() - alexio::vec2(mPosition.x, mPosition.y + 1);
	alexio::vec2 targetToRight = mPlayer->GetPosition() - alexio::vec2(mPosition.x + 1, mPosition.y);
	
	float distanceUp = targetToUp.length();
	float distanceLeft = targetToLeft.length();
	float distanceDown = targetToDown.length();
	float distanceRight = targetToRight.length();
	
	if (game->map->isSolid(mPosition.x, mPosition.y - 1)) distanceUp = 9999.0f;
	if (game->map->isSolid(mPosition.x - 1, mPosition.y)) distanceLeft = 9999.0f;
	if (game->map->isSolid(mPosition.x, mPosition.y + 1)) distanceDown = 9999.0f;
	if (game->map->isSolid(mPosition.x + 1, mPosition.y)) distanceRight = 9999.0f;
	
	float shortestDistance = min(min(distanceUp, distanceLeft), min(distanceDown, distanceRight));
	
	if (shortestDistance == distanceUp)	   mDirection = alexio::vec2( 0, -1);
	if (shortestDistance == distanceLeft)  mDirection = alexio::vec2(-1,  0);
	if (shortestDistance == distanceDown)  mDirection = alexio::vec2( 0,  1);
	if (shortestDistance == distanceRight) mDirection = alexio::vec2( 1,  0);
	
	mPosition += mDirection;
}
