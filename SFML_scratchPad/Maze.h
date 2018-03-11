#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

class Maze : public sf::Drawable
{
public:
	Maze();
	void LoadLevel( const sf::String & name );

	sf::Vector2i getPacWomanPosition() const;
	std::vector< sf::Vector2i > getGhostPositions() const;

	inline std::size_t PositionToIndex( sf::Vector2i position ) const;
	inline sf::Vector2i IndexToPosition( std::size_t index ) const;

private:
	void draw( sf::RenderTarget & target, sf::RenderStates states ) const;

private:
	enum CellData
	{
		Empty,
		Wall,
		Dot,
		SuperDot,
		Bonus
	};

	sf::Vector2u m_mazeSize;
	std::vector< CellData > m_mazeData;
	sf::RenderTexture m_renderTexture;

	sf::Vector2i m_posPacWoman;
	std::vector< sf::Vector2i > m_posGhosts;
};