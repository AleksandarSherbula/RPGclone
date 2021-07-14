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

int Object::GetColorFromJson(const std::string& color)
{
	if (color == "BLACK")               return 0x0000;
	else if (color == "BLUE")           return 0x0001;
	else if (color == "GREEN")          return 0x0002;
	else if (color == "CYAN")           return 0x0003;
	else if (color == "RED")            return 0x0004;
	else if (color == "MAGENTA")        return 0x0005;
	else if (color == "YELLOW")         return 0x0006;
	else if (color == "LIGHT_GREY")     return 0x0007;
	else if (color == "GREY")           return 0x0008;
	else if (color == "LIGHT_BLUE")     return 0x0009;
	else if (color == "LIGHT_GREEN")    return 0x000A;
	else if (color == "LIGHT_CYAN")     return 0x000B;
	else if (color == "LIGHT_RED")      return 0x000C;
	else if (color == "LIGHT_MAGENTA")  return 0x000D;
	else if (color == "LIGHT_YELLOW")   return 0x000E;
	else if (color == "WHITE")          return 0x000F;

	return -1;
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

Creature::Creature()
{
	mID = L"x";
	mPosition = alexio::vec2(0, 0);
	mColor = alexio::FG_WHITE;
	mDirection = alexio::vec2(0, 0);
}

Creature::Creature(const std::wstring& id, const alexio::vec2& position, const int health, const int damage, const int armor, const int color)
{
	mID = id;
	mPosition = position;
	mHealth = health;
	mMaxHealth = health;
	mDamage = damage;
	mArmor = armor;
	mColor = color;
	mDirection = alexio::vec2(0, 0);
}

void Creature::SetHealth(const int health)
{
	mHealth = health;
}

void Creature::SetMaxHealth(const int health)
{
	mMaxHealth = health;
}

void Creature::SetDamage(const int damage)
{
	mDamage = damage;
}

void Creature::SetArmor(const int armor)
{
	mArmor = armor;
}

void Creature::SetData(const std::string& name)
{
	nlohmann::json& j = game->jsonConfig->GetJSON();

	std::string tempID = j[name]["ID"].get<std::string>();
	mID = L" ";
	std::copy(tempID.begin(), tempID.end(), mID.begin());

	mColor = GetColorFromJson(j[name]["Color"].get<std::string>());
	mHealth = j[name]["Health"].get<int>();
	mMaxHealth = j[name]["Health"].get<int>();
	mDamage = j[name]["Damage"].get<int>();
	mArmor = j[name]["Armor"].get<int>();
}

void Creature::UpdateHealth(const int health)
{
	mHealth += health;
}

void Creature::Attack(Creature* creature)
{
	creature->UpdateHealth((this->mDamage - creature->GetArmor()) * -1);
}

Player::Player() : Creature()
{
}

Player::Player(const std::string& name) : Creature()
{
	nlohmann::json& j = game->jsonConfig->GetJSON();

	std::string tempID = j[name]["ID"].get<std::string>();
	mID = L" ";
	std::copy(tempID.begin(), tempID.end(), mID.begin());

	mPosition.x = j[name]["Position"][0].get<int>();
	mPosition.y = j[name]["Position"][1].get<int>();
	mColor = GetColorFromJson(j[name]["Color"].get<std::string>());
	mHealth = j[name]["Health"].get<int>();
	mMaxHealth = j[name]["Health"].get<int>();
	mDamage = j[name]["Damage"].get<int>();
	mArmor = j[name]["Armor"].get<int>();
}

void Player::Behaviour()
{
	mDirection = alexio::vec2(0, 0);

	if (game->jsonConfig->GetKeyPressed("Up") &&
		!game->map->isSolid(alexio::vec2(mPosition.x, mPosition.y - 1)))
	{		
		mDirection.y--;
		game->turns++;
		game->start = game->Now();
	}
	if (game->jsonConfig->GetKeyPressed("Down") &&
		!game->map->isSolid(alexio::vec2(mPosition.x, mPosition.y + 1)))
	{
		mDirection.y++;
		game->turns++;
		game->start = game->Now();
	}
	if (game->jsonConfig->GetKeyPressed("Left") &&
		!game->map->isSolid(alexio::vec2(mPosition.x - 1, mPosition.y)))
	{
		mDirection.x--;
		game->turns++;
		game->start = game->Now();
	}
	if (game->jsonConfig->GetKeyPressed("Right") &&
		!game->map->isSolid(alexio::vec2(mPosition.x + 1, mPosition.y)))
	{
		mDirection.x++;
		game->turns++;
		game->start = game->Now();
	}

	mPosition += mDirection;
}

Enemy::Enemy() : Creature()
{
	mPlayer = nullptr;
}

Enemy::Enemy(Player* player)
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

Item::Item() : Object()
{
}

Item::Item(const std::wstring& id, const alexio::vec2& position, const int color)
	: Object(id, position, color)
{
}

void Item::AddToInventory()
{

}
