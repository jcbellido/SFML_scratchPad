#include "Dot.h"
#include "Maze.h"

Maze::Maze () : m_mazeSize ( 0, 0 ),
m_posPacWoman ( 0, 0 )
{
}

void Maze::LoadLevel ( const sf::String & name )
{
	sf::Image levelData;
	sf::String levelPath = "resources/levels/" + name + ".png";
	if ( !levelData.loadFromFile ( levelPath ) )
		throw std::runtime_error ( "Can't load level from :" + levelPath );

	m_mazeSize = sf::Vector2u ( levelData.getSize () );

	// The limit by size is absurd
	if ( m_mazeSize.x < 15 || m_mazeSize.y < 15 )
		throw std::runtime_error ( levelPath + " map is too small" );

	for ( unsigned int y = 0; y < m_mazeSize.y; y++ )
	{
		for ( unsigned int x = 0; x < m_mazeSize.x; x++ )
		{
			sf::Color cellData = levelData.getPixel ( x, y );

			if ( cellData == sf::Color::Black )
			{
				m_mazeData.push_back ( Wall );
			}
			else if ( cellData == sf::Color::White )
			{
				m_mazeData.push_back ( Dot );
			}
			else if ( cellData == sf::Color::Green )
			{
				m_mazeData.push_back ( SuperDot );
			}
			else if ( cellData == sf::Color::Blue )
			{
				// Pack woman location
				m_posPacWoman = sf::Vector2i ( x, y );
				m_mazeData.push_back ( Empty );
			}
			else if ( cellData == sf::Color::Red )
			{
				// Ghost location
				m_posGhosts.push_back ( sf::Vector2i ( x, y ) );
				m_mazeData.push_back ( Empty );
			}
			else
			{
				m_mazeData.push_back ( Empty );
			}
		}
	}

	m_renderTexture.create ( 32 * m_mazeSize.x, 32 * m_mazeSize.y );
	m_renderTexture.clear ( sf::Color::Black );

	sf::RectangleShape wall;
	wall.setSize ( sf::Vector2f ( 32, 32 ) );
	wall.setFillColor ( sf::Color::Blue );

	for ( unsigned int i = 0; i < m_mazeData.size (); i++ )
	{
		sf::Vector2i position = IndexToPosition ( i );

		if ( m_mazeData [ i ] == Wall )
		{
			wall.setPosition( static_cast<float>( 32 * position.x ), 
							  static_cast<float>( 32 * position.y ) );
			m_renderTexture.draw ( wall );
		}
	}

	// Commit changes to maze texture
	m_renderTexture.display ();
}

std::size_t Maze::PositionToIndex ( sf::Vector2i position ) const
{
	return position.y * m_mazeSize.x + position.x;
}

sf::Vector2i Maze::IndexToPosition ( std::size_t index ) const
{
	sf::Vector2i position;

	unsigned int uindex = static_cast< unsigned int >( index );

	position.x = uindex % m_mazeSize.x;
	position.y = uindex / m_mazeSize.x;

	return position;
}

sf::Vector2i Maze::getPacWomanPosition () const
{
	return m_posPacWoman;
}

std::vector< sf::Vector2i > Maze::getGhostPositions () const
{
	return m_posGhosts;
}

void Maze::draw ( sf::RenderTarget & target, sf::RenderStates states ) const
{
	target.draw ( sf::Sprite ( m_renderTexture.getTexture () ), states );

	static sf::CircleShape dot = getDot();
	static sf::CircleShape superDot = getSuperDot();
	
	for ( unsigned int i = 0; i < m_mazeData.size (); i++ )
	{
		sf::Vector2i position = IndexToPosition ( i );

		if ( m_mazeData [ i ] == Dot )
		{
			dot.setPosition ( static_cast<float>( 32 * position.x + 16 ), 
							  static_cast<float>( 32 * position.y + 16 ) );
			target.draw( dot, states );
		}
		else if ( m_mazeData [ i ] == SuperDot )
		{
			superDot.setPosition ( static_cast<float>( 32 * position.x + 16 ), 
								   static_cast<float>( 32 * position.y + 16 ) );
			target.draw( superDot, states );
		}
	}
}