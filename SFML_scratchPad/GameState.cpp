#include "GameState.h"

GameState::GameState( Game * game ) : m_game( game )
{

}

Game* GameState::GetGame() 
{ 
	return m_game; 
}