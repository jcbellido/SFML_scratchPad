#include "Ghost.h"

Ghost::Ghost( sf::Texture & texture )
	: m_visual( texture ), 
	  m_isWeak( false ),
	  m_weaknessDuration( sf::Time::Zero )
{
	setOrigin( 20, 20 );


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
