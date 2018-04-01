#include <cmath>

#include "Dot.h"
#include "Maze.h"

Maze::Maze ( sf::Texture & texture ) : m_mazeSize ( 0, 0 ),
m_texture ( texture ),
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

	sf::Sprite border ( m_texture );
	border.setTextureRect ( sf::IntRect ( 16, 0, 16, 32 ) );
	border.setOrigin ( 0, 16 );

	sf::Sprite innerCorner ( m_texture );
	innerCorner.setTextureRect ( sf::IntRect ( 0, 0, 16, 16 ) );
	innerCorner.setOrigin ( 0, 16 );

	sf::Sprite outerCorner ( m_texture );
	outerCorner.setTextureRect ( sf::IntRect ( 0, 16, 16, 16 ) );
	outerCorner.setOrigin ( 0, 16 );

	sf::RectangleShape wall;
	wall.setSize ( sf::Vector2f ( 32, 32 ) );
	wall.setFillColor ( sf::Color::Blue );

	m_renderTexture.display ();

	for ( unsigned int i = 0; i < m_mazeData.size (); i++ )
	{
		sf::Vector2i position = IndexToPosition ( i );

		if ( isWall ( position ) )
		{
			wall.setPosition ( static_cast< float >( 32 * position.x ),
							   static_cast< float >( 32 * position.y ) );
			m_renderTexture.draw( wall );

			border.setPosition ( MapCellToPixel ( position ) );
			innerCorner.setPosition ( MapCellToPixel ( position ) );
			outerCorner.setPosition ( MapCellToPixel ( position ) );
			
			// Plain borders
			if ( !isWall ( position + sf::Vector2i ( 1, 0 ) ) )
			{
				border.setRotation ( 0 );
				m_renderTexture.draw ( border );
			}

			if ( !isWall ( position + sf::Vector2i ( 0, 1 ) ) )
			{
				border.setRotation ( 90 );
				m_renderTexture.draw ( border );
			}

			if ( !isWall ( position + sf::Vector2i ( -1, 0 ) ) )
			{
				border.setRotation ( 180 );
				m_renderTexture.draw ( border );
			}

			if ( !isWall ( position + sf::Vector2i ( 0, -1 ) ) )
			{
				border.setRotation ( 270 );
				m_renderTexture.draw ( border );
			}
			// Inner Corner section
			if ( isWall ( position + sf::Vector2i ( 1, 0 ) ) &&
				  isWall ( position + sf::Vector2i ( 0, -1 ) ) )
			{
				innerCorner.setRotation ( 0 );
				m_renderTexture.draw ( innerCorner );
			}

			if ( isWall ( position + sf::Vector2i ( 0, 1 ) ) &&
				  isWall ( position + sf::Vector2i ( 1, 0 ) ) )
			{
				innerCorner.setRotation ( 90 );
				m_renderTexture.draw ( innerCorner );
			}

			if ( isWall ( position + sf::Vector2i ( -1, 0 ) ) &&
				  isWall ( position + sf::Vector2i ( 0, 1 ) ) )
			{
				innerCorner.setRotation ( 180 );
				m_renderTexture.draw ( innerCorner );
			}

			if ( isWall ( position + sf::Vector2i ( 0, -1 ) ) &&
				  isWall ( position + sf::Vector2i ( -1, 0 ) ) )
			{
				innerCorner.setRotation ( 270 );
				m_renderTexture.draw ( innerCorner );
			}
			// Outer Corner section
			if ( ! isWall ( position + sf::Vector2i ( 1, 0 ) ) &&
				 ! isWall ( position + sf::Vector2i ( 0, -1 ) ) )
			{
				outerCorner.setRotation ( 0 );
				m_renderTexture.draw ( outerCorner );
			}

			if ( ! isWall ( position + sf::Vector2i ( 0, 1 ) ) &&
				 ! isWall ( position + sf::Vector2i ( 1, 0 ) ) )
			{
				outerCorner.setRotation ( 90 );
				m_renderTexture.draw ( outerCorner );
			}

			if ( ! isWall ( position + sf::Vector2i ( -1, 0 ) ) &&
				 ! isWall ( position + sf::Vector2i ( 0, 1 ) ) )
			{
				outerCorner.setRotation ( 180 );
				m_renderTexture.draw ( outerCorner );
			}

			if ( ! isWall ( position + sf::Vector2i ( 0, -1 ) ) &&
				 ! isWall ( position + sf::Vector2i ( -1, 0 ) ) )
			{
				outerCorner.setRotation ( 270 );
				m_renderTexture.draw ( outerCorner );
			}
		}
	}
	// Commit changes to maze texture
	// m_renderTexture.display ();
}

sf::Vector2i Maze::MapPixelToCell ( sf::Vector2f pixel ) const
{
	sf::Vector2i cell;
	cell.x = static_cast< int >( std::floor ( pixel.x / 32.f ) );
	cell.y = static_cast< int >( std::floor ( pixel.y / 32.f ) );

	return cell;
}

sf::Vector2f Maze::MapCellToPixel ( sf::Vector2i cell ) const
{
	sf::Vector2f pixel;
	pixel.x = static_cast< float >( cell.x ) * 32 + 16;
	pixel.y = static_cast< float >( cell.y ) * 32 + 16;

	return pixel;
}

bool Maze::isWall ( sf::Vector2i position ) const
{
	if ( position.x < 0 || 
		 position.y < 0 || 
		 position.x >= static_cast< int >( m_mazeSize.x ) || 
		 position.y >= static_cast< int >( m_mazeSize.y ) )
	{
		return false;
	}
	return m_mazeData [ PositionToIndex ( position ) ] == Wall;
}

sf::Vector2i Maze::GetSize() const
{
	return sf::Vector2i( m_mazeSize.x, m_mazeSize.y );
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

	static sf::CircleShape dot = getDot ();
	static sf::CircleShape superDot = getSuperDot ();

	for ( unsigned int i = 0; i < m_mazeData.size (); i++ )
	{
		sf::Vector2i position = IndexToPosition ( i );

		if ( m_mazeData [ i ] == Dot )
		{
			dot.setPosition ( static_cast< float >( 32 * position.x + 16 ),
				static_cast< float >( 32 * position.y + 16 ) );
			target.draw ( dot, states );
		}
		else if ( m_mazeData [ i ] == SuperDot )
		{
			superDot.setPosition ( static_cast< float >( 32 * position.x + 16 ),
				static_cast< float >( 32 * position.y + 16 ) );
			target.draw ( superDot, states );
		}
	}
}
