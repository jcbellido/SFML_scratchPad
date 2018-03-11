#pragma once

#include "Maze.h"
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
private: 
	Maze m_maze;
};
