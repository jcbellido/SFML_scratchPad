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

	sf::Font & GetFont();
	sf::Texture & GetLogo();
	sf::Texture & GetTexture();

	sf::Vector2u GetVideoSize();

private:
	void InitializeGameStates();
	void LoadSharedResources();

	sf::RenderWindow m_window;
	GameState * m_currentState;
	std::array< GameState *, GameState::Count > m_states;

	sf::Font m_font;
	sf::Texture m_logo;
	sf::Texture m_texture;
};