#ifndef OBJECT_H
#define OBJECT_H

#include "AlexioConsoleEngine.h"

#include <string>

class Object
{
protected:
	std::wstring mID;
	std::string mName;
	alexio::vec2 mPosition;
	int mColor;
public:
	Object();
	Object(const std::string& name);
	~Object();

	inline std::wstring GetID() { return mID; }
	inline std::string GetName() { return mName; }
	inline alexio::vec2 GetPosition() { return mPosition; }
	inline int GetColor() { return mColor; }

	int GetColorFromJson(const std::string& color);

	void SetID(const std::wstring& id);
	void SetPosition(const alexio::vec2& position);
	void SetColor(const int color);

	virtual void Behaviour();

	virtual void Draw();
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
	Creature(const std::string& name);

	inline int GetHealth() { return mHealth; }
	inline int GetMaxHealth() { return mMaxHealth; }
	inline int GetDamage() { return mDamage; }
	inline int GetArmor() { return mArmor; }

	void SetHealth(const int health);
	void SetMaxHealth(const int health);
	void SetDamage(const int damage);
	void SetArmor(const int armor);

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
public:
	Enemy();
	Enemy(const std::string& name, const alexio::vec2& position);

	void Behaviour() override;
};


class Item : public Object
{
private:
	std::wstring mDecription;
public:
	Item();
	Item(const std::string& name, const std::wstring& id, const alexio::vec2& position);
	
	void AddToInventory();

	void SetDescription(const std::wstring& description);
	
	virtual void Use() = 0;
};

class HealthBoost : public Item
{
private:
	int mAmount;
public:
	HealthBoost();
	HealthBoost(const std::string& name, const std::wstring& id, const alexio::vec2& position);

	void Use() override;
};

#endif // !OBJECT_H