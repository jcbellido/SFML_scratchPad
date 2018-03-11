#include "Animator.h"

Animator::Animator() :	m_currentFrame( 0 ),
						m_isPlaying( false ),
						m_duration( sf::Time::Zero ),
						m_loop( false )
{
}

void Animator::AddFrame( sf::IntRect frame )
{
	m_frames.push_back( frame );
}

void Animator::Play( sf::Time duration, bool loop )
{
	m_isPlaying = true;
	m_duration = duration;
	m_loop = loop;
}

bool Animator::IsPlaying() const
{
	return m_loop;
}

void Animator::Update( sf::Time delta )
{
	if( ! IsPlaying() )
		return;

	static sf::Time timeBuffer = sf::Time::Zero;
	timeBuffer += delta;

	sf::Time frameDuration = m_duration / static_cast< float >( m_frames.size() );

	// I guess this is here to consume a lot of frames in case a biiig delta comes
	while( timeBuffer > frameDuration )
	{
		m_currentFrame ++;
		if( m_currentFrame == m_frames.size() )
		{
			if (! m_loop )
				m_isPlaying = false;

			m_currentFrame = 0;
		}
		timeBuffer -= frameDuration;
	}
}

void Animator::Animate( sf::Sprite & sprite )
{
	sprite.setTextureRect( m_frames[ m_currentFrame ] );
}
