#include "Ghost.h"

Ghost::Ghost( std::shared_ptr< CharacterConfiguration > config, sf::Texture & texture )
	: Character( config ),
	  m_visual( texture ), 
	  m_isWeak( false ),
	  m_weaknessDuration( sf::Time::Zero )
{
	setOrigin( config->Origin );

	m_strongAnimator = config->Animators[ "strong" ];
	m_weakAnimator = config->Animators[ "weak" ];

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