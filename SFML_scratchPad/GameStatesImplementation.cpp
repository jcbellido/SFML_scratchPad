#include "GameStatesImplementation.h"

NoCoinState::NoCoinState ( Game * game ) : GameState( game ) { }

void NoCoinState::InsertCoin () {}
void NoCoinState::PressButton () {}
void NoCoinState::MoveStick ( sf::Vector2i direction ) {}

void NoCoinState::HandleInput () {}
void NoCoinState::Update ( sf::Time delta ) {}
void NoCoinState::Draw ( sf::RenderWindow & window ) {}


GetReadyState::GetReadyState ( Game * game ) : GameState( game ) { }

void GetReadyState::InsertCoin () {}
void GetReadyState::PressButton () {}
void GetReadyState::MoveStick ( sf::Vector2i direction ) {}

void GetReadyState::HandleInput () {}
void GetReadyState::Update ( sf::Time delta ) {}
void GetReadyState::Draw ( sf::RenderWindow & window ) {}


PlayingState::PlayingState ( Game * game ) : GameState( game ) { }

void PlayingState::InsertCoin () {}
void PlayingState::PressButton () {}
void PlayingState::MoveStick ( sf::Vector2i direction ) {}

void PlayingState::HandleInput () {}
void PlayingState::Update ( sf::Time delta ) {}
void PlayingState::Draw ( sf::RenderWindow & window ) {}



WonState::WonState ( Game * game ) : GameState( game ) { }

void WonState::InsertCoin () {}
void WonState::PressButton () {}
void WonState::MoveStick ( sf::Vector2i direction ) {}

void WonState::HandleInput () {}
void WonState::Update ( sf::Time delta ) {}
void WonState::Draw ( sf::RenderWindow & window ) {}



LostState::LostState ( Game * game ) : GameState( game ) { }

void LostState::InsertCoin () {}
void LostState::PressButton () {}
void LostState::MoveStick ( sf::Vector2i direction ) {}

void LostState::HandleInput () {}
void LostState::Update ( sf::Time delta ) {}
void LostState::Draw ( sf::RenderWindow & window ) {}
