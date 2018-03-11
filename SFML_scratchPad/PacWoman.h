#pragma once

#include "Animator.h"
#include "Character.h"

class PacWoman : public Character
{
public:
	PacWoman( sf::Texture & texture ); 
	void Die();
	bool IsDead() const;
	bool IsDying() const;

	void Update( sf::Time delta );

private:
	void draw(	sf::RenderTarget & target, 
				sf::RenderStates states ) const;

	bool m_isDead;
	bool m_isDying;

	sf::Sprite m_visual;

	Animator m_runAnimator;
	Animator m_dieAnimator;
};