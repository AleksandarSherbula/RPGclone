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

	void SetID(const std::wstring& id);
	void SetPosition(const alexio::vec2& position);
	void SetColor(const int color);

	virtual void Behaviour();

	void Draw();
	void Draw(const std::wstring& id, const alexio::vec2& position, const int color = alexio::FG_WHITE);
};

class Player : public Object
{
private:
	alexio::vec2 mDirection;
public:
	Player();
	Player(const std::wstring& id, const alexio::vec2& position, const int color = alexio::FG_WHITE);

	void Behaviour() override;
};

#endif // !OBJECT_H