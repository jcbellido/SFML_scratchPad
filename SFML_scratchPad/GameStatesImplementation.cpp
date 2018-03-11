#include "GameStatesImplementation.h"
#include "Game.h"
#include "GraphicsUtils.h"

PlayingState::PlayingState ( Game * game ) : GameState( game ) { }

void PlayingState::InsertCoin () { 	GetGame()->InsertCoin(); }
void PlayingState::PressButton () {}
void PlayingState::MoveStick ( sf::Vector2i direction ) {}

void PlayingState::HandleInput () {}
void PlayingState::Update ( sf::Time delta ) {}
void PlayingState::Draw ( sf::RenderWindow & window ) {}


WonState::WonState ( Game * game ) : GameState( game ) { }

void WonState::InsertCoin () { 	GetGame()->InsertCoin(); }
void WonState::PressButton () {}
void WonState::MoveStick ( sf::Vector2i direction ) {}

void WonState::HandleInput () {}
void WonState::Update ( sf::Time delta ) {}
void WonState::Draw ( sf::RenderWindow & window ) {}
