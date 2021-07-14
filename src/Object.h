#ifndef OBJECT_H
#define OBJECT_H

#include "AlexioConsoleEngine.h"

#include <string>

class Object
{
protected:
	std::wstring mID;
	alexio::vec2 mPosition;
	int mColor;
public:
	Object();
	Object(const std::wstring& id, const alexio::vec2& position, const int color);
	~Object();

	inline std::wstring GetID() { return mID; }
	inline alexio::vec2 GetPosition() { return mPosition; }
	inline int GetColor() { return mColor; }

	int GetColorFromJson(const std::string& color);

	void SetID(const std::wstring& id);
	void SetPosition(const alexio::vec2& position);
	void SetColor(const int color);

	virtual void Behaviour();

	void Draw();
	void Draw(const std::wstring& id, const alexio::vec2& position, const int color = alexio::FG_WHITE);
};

class Creature : public Object
{
protected:
	alexio::vec2 mDirection;
	int mHealth;
	int mMaxHealth;
	int mDamage;
	int mArmor;
public:
	Creature();
	Creature(const std::wstring& id, const alexio::vec2& position, const int health, const int damage, const int armor, const int color = alexio::FG_WHITE);

	inline int GetHealth() { return mHealth; }
	inline int GetMaxHealth() { return mMaxHealth; }
	inline int GetDamage() { return mDamage; }
	inline int GetArmor() { return mArmor; }

	void SetHealth(const int health);
	void SetMaxHealth(const int health);
	void SetDamage(const int damage);
	void SetArmor(const int armor);

	void SetData(const std::string& name);

	void UpdateHealth(const int health);

	void Attack(Creature* creature);
};

class Player : public Creature
{
public:
	Player();
	Player(const std::string& name);	

	void Behaviour() override;
};

class Enemy : public Creature
{
private:
	Player* mPlayer;
public:
	Enemy();
	Enemy(Player* player = nullptr);

	void Behaviour() override;
};


class Item : Object
{
private:
	std::wstring sName;
	std::wstring sDecription;

public:
	Item();
	Item(const std::wstring& id, const alexio::vec2& position, const int color = alexio::FG_WHITE);
	
	void AddToInventory();
	
	virtual void Use() = 0;
};

#endif // !OBJECT_H