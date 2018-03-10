#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <array>

#include "GameState.h"

class Game
{
public:
	Game ();
	~Game();
	void Run ();

	void ChangeGameState( GameState::State gameState );

private:
	sf::RenderWindow m_window;
	GameState * m_currentState;
	std::array< GameState *, GameState::Count > m_states;
};