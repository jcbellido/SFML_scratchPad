#include "GetReadyState.h"
#include "Game.h"
#include "GraphicsUtils.h"

GetReadyState::GetReadyState ( Game * game ) : GameState( game ),
											   m_showText( true ),
											   m_timeBuffer( sf::Time::Zero )
{ 
	auto videoSize = game->GetVideoSize();
	m_text.setFont( * game->GetFont( "mainFont" ) );
	m_text.setPosition( static_cast<float>( videoSize.x ) / 2.0f, 
						static_cast<float>( videoSize.y ) / 2.0f );

	m_text.setString ( "Get ready" );
	centerOrigin( m_text );
}

void GetReadyState::HandleInput () {}

void GetReadyState::InsertCoin () 
{
	GetGame()->InsertCoin();
}

void GetReadyState::PreLeave() 
{
	m_timeBuffer = sf::Time::Zero;
}

void GetReadyState::MoveStick ( sf::Vector2i direction ) {}

void GetReadyState::PressButton () 
{
	GetGame()->ChangeGameState( GameState::Playing );
}

void GetReadyState::Update ( sf::Time delta ) 
{
	m_timeBuffer += delta;

	if ( m_timeBuffer > sf::seconds( 2.5f ) )
	{
		GetGame()->ChangeGameState( GameState::Playing );
	}
}

void GetReadyState::Draw ( sf::RenderWindow & window ) 
{
	window.draw( m_text );
}
