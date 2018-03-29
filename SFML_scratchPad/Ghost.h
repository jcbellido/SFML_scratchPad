#pragma once

#include "Character.h"
#include "PacWoman.h"

class Ghost : public Character
{
public:
	enum State
	{
		Strong,
		Weak
	};

	void SetWeak( sf::Time duration );
	bool IsWeak() const;

	Ghost( sf::Texture & texture );

private:
	sf::Sprite m_visual;
	bool m_isWeak;
	sf::Time m_weaknessDuration;

	void draw( sf::RenderTarget & target, sf::RenderStates states ) const;
};