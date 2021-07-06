#ifndef MVC_H
#define MVC_H

#include "AlexioConsoleEngine.h"

#include "boost/signals2.hpp"

#include <string>

///////////////////////////////////////////////////////////////////
////////////////////////////// MODEL //////////////////////////////
///////////////////////////////////////////////////////////////////

class Model
{
protected:
	std::wstring mID;
	alexio::vec2 mPosition;
	int mColor;
public:
	Model();
	Model(const std::wstring& id, const alexio::vec2& position, const alexio::COLOR& color);

	void SetID(const std::wstring& id);
	void SetPosition(const alexio::vec2& position);
	void SetColor(const alexio::COLOR& color);

	inline std::wstring GetID() { return mID; }
	inline alexio::vec2 GetPosition() { return mPosition; }
	inline int GetColor() { return mColor; }	
};


class PlayerModel : public Model
{
private:
	alexio::vec2 direction;
};


///////////////////////////////////////////////////////////////////
////////////////////////////// VIEW ///////////////////////////////
///////////////////////////////////////////////////////////////////

class View
{
public:
	View();

	void Run(const std::wstring& id, const alexio::vec2& position, const alexio::COLOR& color);
};


///////////////////////////////////////////////////////////////////
//////////////////////////// CONTROLLER ///////////////////////////
///////////////////////////////////////////////////////////////////

class Controller
{
private:
	Model mModel;
	View mView;
public:
	Controller();

	void Update();
};

#endif // MVC_H

