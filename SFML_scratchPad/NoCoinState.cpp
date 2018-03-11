#include <string>

#include "NoCoinState.h"
#include "Game.h"
#include "GraphicsUtils.h"

NoCoinState::NoCoinState ( Game * game ) : GameState( game ), 
										   m_showInsertCoin( true )
{ 
	m_sprite.setTexture( game->GetLogo() );
	centerOrigin( m_sprite );

	auto videoSize = game->GetVideoSize();

	m_sprite.setPosition( static_cast<float>( videoSize.x ) / 2.0f , 50 );

	m_text.setFont( game->GetFont() );
	m_text.setPosition( static_cast<float>( videoSize.x ) / 2.0f , 150 );
}

void NoCoinState::UpdateText()
{
	Game * game = GetGame();
	if ( game->CurrentCoins() == 0 )
	{
		m_text.setString ( "Insert coin!" );
		centerOrigin( m_text );
	}
	else
	{
		m_text.setString( "Credits: " + std::to_string( game->CurrentCoins() ) + " Press start" );
		centerOrigin( m_text );
	}
}

void NoCoinState::PreEnter ()
{
	UpdateText();
}

void NoCoinState::InsertCoin () 
{
	GetGame()->InsertCoin();
	UpdateText();
}

void NoCoinState::PressButton () 
{
	if( GetGame()->ConsumeCoin() )
	{
		UpdateText();
		GetGame()->ChangeGameState( GameState::GetReady );
	}
}

void NoCoinState::MoveStick ( sf::Vector2i direction ) {}

void NoCoinState::HandleInput () {}

void NoCoinState::Update ( sf::Time delta ) 
{
	static sf::Time timeBuffer = sf::Time::Zero;
	timeBuffer += delta;
	
	if( ( GetGame()->CurrentCoins() == 0 ) && ( timeBuffer >= sf::seconds( 0.75 ) ) )
	{
		m_showInsertCoin = ! m_showInsertCoin;
		timeBuffer = sf::Time::Zero;
	}
} 

void NoCoinState::Draw ( sf::RenderWindow & window ) 
{
	window.draw( m_sprite );

	if( GetGame()->CurrentCoins() > 0 )
	{
		window.draw( m_text );
	}
	else
	{
		if( m_showInsertCoin )
			window.draw( m_text );
	}
}