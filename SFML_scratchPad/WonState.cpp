#include "WonState.h"
#include "Game.h"
#include "GraphicsUtils.h"

WonState::WonState ( Game * game ) : GameState( game ) { }

void WonState::InsertCoin () { 	GetGame()->InsertCoin(); }
void WonState::PressButton () {}
void WonState::MoveStick ( sf::Vector2i direction ) {}

void WonState::HandleInput () {}
void WonState::Update ( sf::Time delta ) {}
void WonState::Draw ( sf::RenderWindow & window ) {}

