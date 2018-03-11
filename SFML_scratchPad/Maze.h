#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

class Maze : public sf::Drawable
{
public:
	Maze( sf::Texture & texture );
	void LoadLevel( const sf::String & name );

	sf::Vector2i getPacWomanPosition() const;
	std::vector< sf::Vector2i > getGhostPositions() const;

	inline std::size_t PositionToIndex( sf::Vector2i position ) const;
	inline sf::Vector2i IndexToPosition( std::size_t index ) const;

	inline bool isWall( sf::Vector2i position ) const;

	sf::Vector2i MapPixelToCell(sf::Vector2f pixel) const;
	sf::Vector2f MapCellToPixel(sf::Vector2i cell) const;

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

	sf::Texture & m_texture;
};