#pragma once

#include "GameState.h"

class NoCoinState : public GameState
{
public:
	NoCoinState ( Game * game );

	void InsertCoin ();
	void PressButton ();
	void MoveStick ( sf::Vector2i direction );

	void HandleInput ();
	void Update ( sf::Time delta );
	void Draw ( sf::RenderWindow & window );
};

class GetReadyState : public GameState
{
public:
	GetReadyState ( Game * game );

	void InsertCoin ();
	void PressButton ();
	void MoveStick ( sf::Vector2i direction );

	void HandleInput ();
	void Update ( sf::Time delta );
	void Draw ( sf::RenderWindow & window );
};

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

class LostState : public GameState
{
public:
	LostState ( Game * game );

	void InsertCoin ();
	void PressButton ();
	void MoveStick ( sf::Vector2i direction );

	void HandleInput ();
	void Update ( sf::Time delta );
	void Draw ( sf::RenderWindow & window );
};
