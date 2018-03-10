#pragma once

#include <SFML/Graphics.hpp>

class Game;

class GameState
{
public:
	enum State
	{
		NoCoin,
		GetReady,
		Playing,
		Won,
		Lost,
		Count
	};

	GameState( Game * game );

	virtual void InsertCoin () =0;
	virtual void PressButton () =0;
	virtual void MoveStick ( sf::Vector2i direction ) =0;

	virtual void HandleInput() =0;
	virtual void Update( sf::Time delta ) =0;
	virtual void Draw( sf::RenderWindow & window ) =0;

	Game * GetGame();

private:
	Game * m_game;
};