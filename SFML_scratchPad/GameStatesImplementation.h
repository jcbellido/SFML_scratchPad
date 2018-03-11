#pragma once

#include "GameState.h"

class PlayingState : public GameState
{
public:
	PlayingState ( Game * game );

	void InsertCoin ();
	void PressButton ();
	void MoveStick ( sf::Vector2i direction );

	void HandleInput ();
	void Update ( sf::Time delta );
	void Draw ( sf::RenderWindow & window );
};

class WonState : public GameState
{
public:
	WonState ( Game * game );

	void InsertCoin ();
	void PressButton ();
	void MoveStick ( sf::Vector2i direction );

	void HandleInput ();
	void Update ( sf::Time delta );
	void Draw ( sf::RenderWindow & window );
};
