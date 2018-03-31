#include "Ghost.h"

Ghost::Ghost( sf::Texture & texture )
	: m_visual( texture ), 
	  m_isWeak( false ),
	  m_weaknessDuration( sf::Time::Zero )
{
	setOrigin( 20, 20 );

	m_strongAnimator.AddFrame( sf::IntRect( 40, 32, 40, 40 ) );
	m_strongAnimator.AddFrame( sf::IntRect( 80, 32, 40, 40 ) );

	m_weakAnimator.AddFrame( sf::IntRect( 40, 72, 40, 40 ) );
	m_weakAnimator.AddFrame( sf::IntRect( 80, 72, 40, 40 ) );

	m_strongAnimator.Play( sf::seconds( 0.25 ), true );
	m_weakAnimator.Play( sf::seconds( 1 ), true );
}

void Ghost::SetWeak( sf::Time duration )
{
	m_isWeak = true;
	m_weaknessDuration = duration;
}

bool Ghost::IsWeak() const
{
	return m_isWeak;
}

void Ghost::draw ( sf::RenderTarget & target, sf::RenderStates states ) const
{
	states.transform *= getTransform();
	target.draw( m_visual, states );
}

void Ghost::Update( sf::Time delta )
{
	if( IsWeak() )
	{
		m_weaknessDuration -= delta;

		if( m_weaknessDuration <= sf::Time::Zero )
		{
			m_isWeak = false;
			m_strongAnimator.Play( sf::seconds( 0.25 ), true );
		}
	}

	if( IsWeak() )
	{
		m_weakAnimator.Update( delta );
		m_weakAnimator.Animate( m_visual );
	}
	else
	{
		m_strongAnimator.Update( delta );
		m_strongAnimator.Animate( m_visual );
	}
	Character::Update( delta );
}