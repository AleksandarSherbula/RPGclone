#include "MVC.h"
#include "Game.h"

Model::Model()
{
}

Model::Model(const std::wstring& id, const alexio::vec2& position, const alexio::COLOR& color)
{
	mID = id;
	mPosition = position;
	mColor = color;
}

void Model::SetID(const std::wstring& id)
{
	mID = id;
}

void Model::SetPosition(const alexio::vec2& position)
{
	mPosition = position;
}

void Model::SetColor(const alexio::COLOR& color)
{
	mColor = color;
}

View::View()
{
}

void View::Run(const std::wstring& id, const alexio::vec2& position, const alexio::COLOR& color)
{
	game->DrawWideString(position, id, color);
}

Controller::Controller()
{
	
}

void Controller::Update()
{
}