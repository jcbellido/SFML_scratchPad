#include "Game.h"
#include "GameStates.h"

void Game::InitializeGameStates ()
{
	m_states [ GameState::NoCoin ]   = std::make_shared< NoCoinState >( this );
	m_states [ GameState::GetReady ] = std::make_shared< GetReadyState > ( this );
	m_states [ GameState::Playing ]  = std::make_shared< PlayingState > ( this );
	m_states [ GameState::Won ]      = std::make_shared< WonState > ( this );
	m_states [ GameState::Lost ]     = std::make_shared< LostState > ( this );
}

void Game::LoadSharedResources ()
{
    std::string filePath = "resources/audio/223241__rap2h__8-l-antre-du-diable.wav";
    if( !m_music.openFromFile( filePath ) )
        throw std::runtime_error ( "Unable to load: " + filePath );
    
    filePath = "resources/audio/341695__projectsu012__coins-1.wav";
    if( !m_soundCoinBuffer.loadFromFile( filePath ) )
        throw std::runtime_error ( "Unable to load: " + filePath );
    
    m_soundCoin.setBuffer( m_soundCoinBuffer );
}

void Game::ConstructWindow()
{
	m_window = std::make_shared< sf::RenderWindow >( sf::VideoMode ( m_assetLoader.WindowWidth(), 
													 m_assetLoader.WindowHeight() ), 
													 m_assetLoader.WindowName() );
}

Game::Game () : m_coinsInserted( 0 ),
				m_assetLoader( "resources/Packitty.json" )
{
    ConstructWindow();

	LoadSharedResources ();
	InitializeGameStates ();

	// Change me ...
	m_currentState = m_states[ GameState::NoCoin ];
	m_currentState = m_states[ GameState::Playing ];

	m_currentState->PreEnter();
	// m_music.play();
}

sf::Vector2u Game::GetVideoSize()
{
	return m_window->getSize();
}

void Game::Run ()
{
	sf::Clock frameClock;
	while ( m_window->isOpen () )
	{
		sf::Event event;
		while ( m_window->pollEvent ( event ) )
		{
			if ( event.type == sf::Event::Closed )
			{
				m_window->close ();
			}

			if ( event.type == sf::Event::KeyReleased )
			{
				if ( event.key.code == sf::Keyboard::I )
				{
					m_currentState->InsertCoin ();
					m_soundCoin.play();
				}
				if ( event.key.code == sf::Keyboard::S )
				{
					m_currentState->PressButton ();
				}
			}

			if ( event.type == sf::Event::KeyPressed )
			{
				if ( event.key.code == sf::Keyboard::Left )
					m_currentState->MoveStick ( sf::Vector2i ( -1, 0 ) );

				if ( event.key.code == sf::Keyboard::Right )
					m_currentState->MoveStick ( sf::Vector2i ( 1, 0 ) );

				if ( event.key.code == sf::Keyboard::Up )
					m_currentState->MoveStick ( sf::Vector2i ( 0, -1 ) );

				if ( event.key.code == sf::Keyboard::Down )
					m_currentState->MoveStick ( sf::Vector2i ( 0, 1 ) );
			}
		}

		// Silly implementation 
		sf::Time elapsed = frameClock.restart ();
		if ( elapsed.asSeconds() > sf::milliseconds( 33 ).asSeconds() )
		{
			elapsed = sf::milliseconds ( 33 );
		}

		m_currentState->Update ( elapsed );
		m_window->clear ();
		m_currentState->Draw ( * m_window );
		m_window->display ();
	}
}

void Game::ChangeGameState ( GameState::State gameState )
{
	m_currentState->PreLeave();
	m_currentState = m_states [ gameState ];
	m_currentState->PreEnter();
}

std::shared_ptr< sf::Font > Game::GetFont( sf::String key )
{
	return m_assetLoader.GetFont( key );
}

std::shared_ptr< sf::Texture > Game::GetTexture( sf::String key )
{
	return m_assetLoader.GetTexture( key );
}

std::shared_ptr< CharacterConfiguration > Game::GetCharacterConfig( sf::String key )
{
	return m_assetLoader.GetCharacterConfig( key );
}

void Game::InsertCoin()
{
	m_coinsInserted ++;
}

bool Game::ConsumeCoin()
{
	if( m_coinsInserted > 0)
	{
		m_coinsInserted --;
		return true;
	}
	return false;
}

int Game::CurrentCoins()
{
	return m_coinsInserted;
}
