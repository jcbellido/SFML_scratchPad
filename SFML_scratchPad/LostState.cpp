#include < string >

#include "LostState.h"
#include "Game.h"
#include "GraphicsUtils.h"

LostState::LostState ( Game * game ) : GameState( game ),
									   m_timeBuffer( sf::Time::Zero ),
									   m_remainingSeconds( 9 )
{ 
	auto videoSize = game->GetVideoSize();

	m_textBanner.setFont( game->GetFont() );
	m_textBanner.setPosition( static_cast<float>( videoSize.x ) / 2.0f , 150 );

	m_textCounter.setFont( game->GetFont() );
	m_textCounter.setPosition( static_cast<float>( videoSize.x ) / 2.0f , 200  );
}

void LostState::InsertCoin() 
{
	GetGame()->InsertCoin();
	UpdateText();
}

void LostState::PressButton()
{
	if( GetGame()->ConsumeCoin() )
	{
		GetGame()->ChangeGameState( GameState::GetReady );
	}
}

void LostState::UpdateText()
{
	Game * game = GetGame();

	if( game->CurrentCoins() > 0 )
	{
		m_textBanner.setString( "Push start to continue" );
		centerOrigin( m_textBanner );
	}
	else
	{
		m_textBanner.setString( "Insert coin to continue" );
		centerOrigin( m_textBanner );
	}

	m_textCounter.setString( std::to_string( m_remainingSeconds ) );
	centerOrigin( m_textCounter );
}

void LostState::HandleInput () {}
void LostState::MoveStick ( sf::Vector2i direction )  { }

void LostState::Update ( sf::Time delta )
{
	m_timeBuffer += delta;
	if( m_timeBuffer > sf::seconds( 1 ) )
	{
		m_timeBuffer = sf::Time::Zero;
		m_remainingSeconds --;
		if( m_remainingSeconds < 0 )
		{
			GetGame()->ChangeGameState( GameState::NoCoin );
		}
		UpdateText();
	}
}

void LostState::Draw ( sf::RenderWindow & window ) 
{
	window.draw( m_textBanner );
	window.draw( m_textCounter );
}

void LostState::PreEnter() 
{
	m_timeBuffer = sf::Time::Zero;
	m_remainingSeconds = 9;
	UpdateText();
}