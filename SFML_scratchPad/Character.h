#pragma once

#include <SFML/Graphics.hpp>

#include "Maze.h"
#include "AssetLoader.h"	// Nope, but for now

class Character : public sf::Drawable, public sf::Transformable
{
public:
	Character( std::shared_ptr< CharacterConfiguration > config );

	virtual void Update( sf::Time delta );

	void SetDirection( sf::Vector2i direction );
	sf::Vector2i GetDirection() const;
	
	void SetMaze( Maze * maze );

	void SetSpeed ( float speed );
	float GetSpeed () const;

private:
	float m_speed;
	Maze * m_maze;
	sf::Vector2i m_currentDirection;
	sf::Vector2i m_nextDirection;
};