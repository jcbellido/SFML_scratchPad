#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <array>

#include "AssetLoader.h"
#include "GameState.h"

class Game
{
public:
	Game ();
	void Run ();

	void ChangeGameState( GameState::State gameState );

	std::shared_ptr< sf::Font > GetFont( sf::String key );
	std::shared_ptr< sf::Texture > GetTexture( sf::String key );
	std::shared_ptr< CharacterConfiguration > GetCharacterConfig( sf::String key );

	sf::Vector2u GetVideoSize();

	void InsertCoin();
	bool ConsumeCoin();
	// TODO?: A coin and a credit are not neccessarily the same
	int CurrentCoins();

private:
	void ConstructWindow();

private:
	void InitializeGameStates();

	AssetLoader m_assetLoader;

	std::shared_ptr< sf::RenderWindow > m_window;
	std::shared_ptr< GameState > m_currentState;
	std::array< std::shared_ptr< GameState >, GameState::Count > m_states;
	
	sf::Sound m_soundCoin;
	std::shared_ptr< sf::Music > m_music;
	int m_coinsInserted = 0;	
};
