#pragma once

#include "Maze.h"
#include "GameState.h"
#include "PacWoman.h"
#include "Ghost.h"

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
	std::unique_ptr< PacWoman > m_packWoman;
	std::vector< std::shared_ptr< Ghost > > m_ghosts;
	sf::View m_camera;
};
