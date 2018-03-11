#include "PlayingState.h"
#include "Game.h"
#include "GraphicsUtils.h"

PlayingState::PlayingState ( Game * game ) : GameState( game ) 
{ 
	m_maze.LoadLevel( "level" );
}

void PlayingState::InsertCoin () { 	GetGame()->InsertCoin(); }
void PlayingState::PressButton () {}

void PlayingState::MoveStick ( sf::Vector2i direction ) {}

void PlayingState::HandleInput () {}
void PlayingState::Update ( sf::Time delta ) {}
void PlayingState::Draw ( sf::RenderWindow & window ) 
{
	window.draw( m_maze );
}
