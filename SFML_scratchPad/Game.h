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
	~Game();
	void Run ();

	void ChangeGameState( GameState::State gameState );

	std::shared_ptr< sf::Font > GetFont( sf::String key );
	std::shared_ptr< sf::Texture > GetTexture( sf::String key );

	sf::Vector2u GetVideoSize();

	void InsertCoin();
	bool ConsumeCoin();
	// TODO?: A coin and a credit are not neccessarily the same
	int CurrentCoins();

private:
	void ConstructWindow();

private:
	void InitializeGameStates();
    void LoadSharedResources();

	AssetLoader m_assetLoader;

	sf::RenderWindow * m_window;
	GameState * m_currentState;
	std::array< GameState *, GameState::Count > m_states;
	
	sf::Music m_music;
	sf::SoundBuffer m_soundCoinBuffer;
	sf::Sound m_soundCoin;
	int m_coinsInserted = 0;	
};
