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

	void InsertCoin();
	bool ConsumeCoin();
	// TODO?: A coin and a credit are not neccessarily the same
	int CurrentCoins();

private:
	void InitializeGameStates();
	void LoadSharedResources();

	sf::RenderWindow m_window;
	GameState * m_currentState;
	std::array< GameState *, GameState::Count > m_states;
	
	// This is not even funny
	sf::Font m_font;
	sf::Texture m_logo;
	sf::Texture m_texture;

	int m_coinsInserted = 0;	
};