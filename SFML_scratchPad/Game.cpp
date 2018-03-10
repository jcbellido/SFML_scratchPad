#include "Game.h"

#include "GameStatesImplementation.h"

Game::Game() : m_window( sf::VideoMode ( 640, 480 ), "Packitty" )
{
	m_states[ GameState::NoCoin ] = new NoCoinState( this );
	m_states[ GameState::GetReady ] = new GetReadyState( this );
	m_states[ GameState::Playing ] = new PlayingState( this );
	m_states[ GameState::Won ] = new WonState( this );
	m_states[ GameState::Lost ] = new LostState( this );

	ChangeGameState( GameState::NoCoin );
}

Game::~Game()
{
	for( GameState * state : m_states )
		delete( state );
}

void Game::Run ()
{
	while ( m_window.isOpen () )
	{
		sf::Event event;
		while ( m_window.pollEvent ( event ) )
		{
			if ( event.type == sf::Event::Closed )
			{
				m_window.close ();
			}

			if ( event.type == sf::Event::KeyPressed )
			{
				if ( event.key.code == sf::Keyboard::I )
					m_currentState->InsertCoin ();

				if ( event.key.code == sf::Keyboard::S )
					m_currentState->PressButton ();

				if ( event.key.code == sf::Keyboard::Left )
					m_currentState->MoveStick ( sf::Vector2i ( -1, 0 ) );

				if ( event.key.code == sf::Keyboard::Right )
					m_currentState->MoveStick ( sf::Vector2i (  1, 0 ) );

				if ( event.key.code == sf::Keyboard::Up )
					m_currentState->MoveStick ( sf::Vector2i ( 0, -1 ) );

				if ( event.key.code == sf::Keyboard::Down)
					m_currentState->MoveStick ( sf::Vector2i ( 0, 1 ) );
			}
		}
		m_currentState->Update( sf::seconds( 1 ) );

		m_window.clear();
		
		m_currentState->Draw( m_window );
		
		m_window.display ();
		
		sf::sleep ( sf::seconds ( 1.0f / 60.0f ) );
	}
}

void Game::ChangeGameState( GameState::State gameState )
{
	m_currentState = m_states[ gameState ];
}