#include "Character.h"

Character::Character( std::shared_ptr< CharacterConfiguration > config )
: m_speed( config->Speed ),
  m_currentDirection( 1, 0 ),
  m_nextDirection( 0, 0 ),
  m_maze( nullptr  )
{
}

void Character::SetSpeed(float speed)
{
	m_speed = speed;
}

float Character::GetSpeed() const 
{
	return m_speed;
}

void Character::SetMaze( Maze * maze )
{
	m_maze = maze;
}

void Character::SetDirection( sf::Vector2i direction ) 
{
	m_nextDirection = direction;
}

sf::Vector2i Character::GetDirection() const
{
	return m_currentDirection;
}

void Character::Update( sf::Time delta )
{
	sf::Vector2f pixelPosition = getPosition();

	float pixelTraveled = GetSpeed() * delta.asSeconds();

	sf::Vector2f nextPixelPos = pixelPosition + sf::Vector2f( m_currentDirection ) * pixelTraveled;
	setPosition( nextPixelPos );

	sf::Vector2i cellPosition = m_maze->MapPixelToCell( pixelPosition );

	sf::Vector2f offset;
	offset.x = static_cast< float >( std::fmod( pixelPosition.x, 32 ) ) - 16;
	offset.y = static_cast< float >( std::fmod( pixelPosition.y, 32 ) ) - 16;

	if( m_maze->isWall( cellPosition + m_currentDirection ) ) 
	{
		if( 
			( m_currentDirection.x ==  1 && offset.x > 0 ) ||
			( m_currentDirection.x == -1 && offset.x < 0 ) ||
			( m_currentDirection.y ==  1 && offset.y > 0 ) ||
			( m_currentDirection.y == -1 && offset.y < 0 )
			)
		{
			setPosition( m_maze->MapCellToPixel( cellPosition ) );
		}
	}

	if ( ! m_maze->isWall( cellPosition + m_nextDirection ) &&
		m_currentDirection != m_nextDirection )
	{
		if( 
			( ! m_currentDirection.y && ( offset.x > -2 && offset.x < 2 ) ) ||
			( ! m_currentDirection.x && ( offset.y > -2 && offset.y < 2 ) )
		)
		{
			setPosition( m_maze->MapCellToPixel( cellPosition ) );
			m_currentDirection = m_nextDirection;

			if( m_currentDirection == sf::Vector2i( 1, 0 ) )
			{
				setRotation( 0 );
				setScale( -1, 1 );
			} 
			else if( m_currentDirection == sf::Vector2i( 0, 1 ) ) 
			{
				setRotation( 90 );
				setScale( -1, 1 );			
			}
			else if( m_currentDirection == sf::Vector2i( - 1, 0 ) ) 
			{
				setRotation( 0 );
				setScale( 1, 1 );			
			}
			else if( m_currentDirection == sf::Vector2i( 0, -1 ) ) 
			{
				setRotation( 90 );
				setScale( 1, 1 );			
			}
		}
	}
}