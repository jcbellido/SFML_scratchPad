#include "Game.h"
#include "GameStates.h"

void Game::InitializeGameStates ()
{
	m_states [ GameState::NoCoin ] = new NoCoinState ( this );
	m_states [ GameState::GetReady ] = new GetReadyState ( this );
	m_states [ GameState::Playing ] = new PlayingState ( this );
	m_states [ GameState::Won ] = new WonState ( this );
	m_states [ GameState::Lost ] = new LostState ( this );
}

void Game::LoadSharedResources ()
{
    sf::String filePath = "resources/font.ttf";
    if ( !m_font.loadFromFile ( filePath ) )
        throw std::runtime_error ( "Unable to load: " + filePath );
    
    filePath = "resources/logo.png";
    if ( !m_logo.loadFromFile ( filePath ) )
        throw std::runtime_error ( "Unable to load: " + filePath );
    
    filePath = "resources/texture.png";
    if ( !m_texture.loadFromFile ( filePath ) )
        throw std::runtime_error ( "Unable to load: " + filePath );
    
    filePath = "resources/audio/223241__rap2h__8-l-antre-du-diable.wav";
    if( !m_music.openFromFile( filePath ) )
        throw std::runtime_error ( "Unable to load: " + filePath );
    
    filePath = "resources/audio/341695__projectsu012__coins-1.wav";
    if( !m_soundCoinBuffer.loadFromFile( filePath ) )
        throw std::runtime_error ( "Unable to load: " + filePath );
    
    m_soundCoin.setBuffer( m_soundCoinBuffer );
}

Game::Game () : m_window ( sf::VideoMode ( 640, 480 ), "Packitty" ),
				m_coinsInserted( 0 )
{
    LoadSharedResources ();
	InitializeGameStates ();
	// Change me ...
	m_currentState = m_states[ GameState::NoCoin ];
	m_currentState->PreEnter();
	m_music.play();
}

Game::~Game ()
{
	for ( GameState * state : m_states )
		delete( state );
}

sf::Vector2u Game::GetVideoSize()
{
	return m_window.getSize();
}

void Game::Run ()
{
	sf::Clock frameClock;
	while ( m_window.isOpen () )
	{
		sf::Event event;
		while ( m_window.pollEvent ( event ) )
		{
			if ( event.type == sf::Event::Closed )
			{
				m_window.close ();
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
		if ( elapsed > sf::milliseconds ( 33 ) )
		{
			elapsed = sf::milliseconds ( 33 );
		}

		m_currentState->Update ( elapsed );
		m_window.clear ();
		m_currentState->Draw ( m_window );
		m_window.display ();
	}
}

void Game::ChangeGameState ( GameState::State gameState )
{
	m_currentState->PreLeave();
	m_currentState = m_states [ gameState ];
	m_currentState->PreEnter();
}

sf::Font & Game::GetFont ()
{
	return m_font;
}

sf::Texture & Game::GetLogo ()
{
	return m_logo;
}

sf::Texture & Game::GetTexture ()
{
	return m_texture;
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
