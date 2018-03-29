#include "PacWoman.h"

PacWoman::PacWoman( sf::Texture & texture ) :	m_visual( texture ),
												m_isDead( false ),
												m_isDying( false )
{
	setOrigin( 20, 20 );

	m_runAnimator.AddFrame( sf::IntRect(  0,  32, 40, 40 ) );
	m_runAnimator.AddFrame( sf::IntRect(  0,  72, 40, 40 ) );

    m_dieAnimator.AddFrame(sf::IntRect(0, 32, 40, 40));
    m_dieAnimator.AddFrame(sf::IntRect(0, 72, 40, 40));
    m_dieAnimator.AddFrame(sf::IntRect(0, 112, 40, 40));
    m_dieAnimator.AddFrame(sf::IntRect(40, 112, 40, 40));
    m_dieAnimator.AddFrame(sf::IntRect(80, 112, 40, 40));
    m_dieAnimator.AddFrame(sf::IntRect(120, 112, 40, 40));
    m_dieAnimator.AddFrame(sf::IntRect(160, 112, 40, 40));

	m_runAnimator.Play( sf::seconds( 0.25f ), true );
}

void PacWoman::Die()
{
	if( ! IsDying() )
	{
		m_dieAnimator.Play( sf::seconds( 1 ), false );
		m_isDying = true;
	}
}

bool PacWoman::IsDying() const
{
	return m_isDying;
}

bool PacWoman::IsDead() const
{
	return m_isDead;
}

void PacWoman::draw( sf::RenderTarget & target, sf::RenderStates states ) const 
{
	states.transform *= getTransform();

	if( ! m_isDead )
	{
		target.draw( m_visual, states );
	}
}

void PacWoman::Update( sf::Time delta )
{
	if( ! m_isDead && ! m_isDying )
	{
		m_runAnimator.Update( delta );
		m_runAnimator.Animate( m_visual );
	}
	else
	{
		m_dieAnimator.Update( delta );
		m_dieAnimator.Animate( m_visual );

		if( ! m_dieAnimator.IsPlaying() )
		{
			m_isDying = false;
			m_isDead = true;
		}
	}
}