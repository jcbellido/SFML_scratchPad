#pragma once

#include "Animator.h"
#include "Character.h"
#include "PacWoman.h"

class Ghost : public Character
{
public:
	Ghost( std::shared_ptr< CharacterConfiguration > config, 
		   sf::Texture & texture );

public:
	enum State
	{
		Strong,
		Weak
	};

	void SetWeak( sf::Time duration );
	bool IsWeak() const;
	void Update( sf::Time delta );

private:
	sf::Sprite m_visual;
	bool m_isWeak;
	sf::Time m_weaknessDuration;

	Animator m_strongAnimator;
	Animator m_weakAnimator;


	void draw( sf::RenderTarget & target, sf::RenderStates states ) const;
};