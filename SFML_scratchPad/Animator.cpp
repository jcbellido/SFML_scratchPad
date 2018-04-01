#include "Animator.h"

Animator::Animator() :	m_currentFrame( 0 ),
						m_isPlaying( false ),
						m_duration( sf::Time::Zero ),
						m_timeBuffer( sf::Time::Zero ),
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
	m_frameDuration = m_duration / static_cast< float >( m_frames.size() );
	m_timeBuffer = sf::Time::Zero;
}

bool Animator::IsPlaying() const
{
	return m_loop;
}

void Animator::Update( sf::Time delta )
{
	if( ! IsPlaying() )
		return;

	m_timeBuffer += delta;

	while( m_timeBuffer > m_frameDuration )
	{
		m_currentFrame ++;
		if( m_currentFrame == m_frames.size() )
		{
			if (! m_loop )
				m_isPlaying = false;

			m_currentFrame = 0;
		}
		m_timeBuffer -= m_frameDuration;
	}
}

void Animator::Animate( sf::Sprite & sprite )
{
	sprite.setTextureRect( m_frames[ m_currentFrame ] );
}
