#include "PlayingState.h"
#include "Game.h"
#include "GraphicsUtils.h"

PlayingState::PlayingState ( Game * game ) : GameState( game ),
	m_maze( * game->GetTexture("atlas") )
{ 
	m_maze.LoadLevel( "large-level" );

	m_packWoman = std::make_unique< PacWoman >(   game->GetCharacterConfig( "PackWoman" ), 
												* game->GetTexture( "atlas" ) );
	m_packWoman->SetMaze( & m_maze );
	m_packWoman->setPosition( m_maze.MapCellToPixel( m_maze.getPacWomanPosition() ) );

	for( auto ghostPosition : m_maze.getGhostPositions() )
	{
		auto ghost = std::make_shared< Ghost >(   game->GetCharacterConfig( "Ghost" ),
												* game->GetTexture("atlas") );
		ghost->SetMaze( & m_maze );
		ghost->setPosition( m_maze.MapCellToPixel( ghostPosition ) );
		m_ghosts.push_back( ghost );
	}

	m_camera.setSize( sf::Vector2f( 480, 480 ) );
	m_camera.setCenter( m_packWoman ->getPosition() );
}

void PlayingState::InsertCoin () { 	GetGame()->InsertCoin(); }
void PlayingState::PressButton () {}

void PlayingState::MoveStick ( sf::Vector2i direction ) 
{
	m_packWoman->SetDirection( direction );
}

void PlayingState::HandleInput () 
{

}

void PlayingState::Update ( sf::Time delta ) 
{
	m_camera.setCenter( m_packWoman->getPosition() );

	if( m_camera.getCenter().x < 240 )	// Better to use the size ? 
	{ 
		m_camera.setCenter( 240, m_camera.getCenter().y );
	}

	if( m_camera.getCenter().y < 240 )
	{
		m_camera.setCenter( m_camera.getCenter().x, 240 );
	}

	if( m_camera.getCenter().x > m_maze.GetSize().x * 32 - 240 )
	{
		m_camera.setCenter( static_cast< float > ( m_maze.GetSize().x ) * 32 - 240, m_camera.getCenter().y );
	}

	if( m_camera.getCenter().y > m_maze.GetSize().y * 32 - 240 )
	{
		m_camera.setCenter( m_camera.getCenter().y , m_maze.GetSize().y * 32 - 240 );
	}

	m_packWoman->Update( delta );
	std::for_each( m_ghosts.begin(), m_ghosts.end(), 
				[ delta ] ( auto g ) { g->Update( delta );  } );
}

void PlayingState::Draw ( sf::RenderWindow & window ) 
{
	window.setView( m_camera );
	window.draw( m_maze );
	window.draw ( *m_packWoman );

	std::for_each( m_ghosts.begin(), m_ghosts.end(), 
				[ & ] ( auto g ) { window.draw( * g ); } );
}

