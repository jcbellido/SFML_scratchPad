#pragma once

#include "Animator.h"
#include "Character.h"

class PacWoman : public Character
{
public:
	PacWoman( std::shared_ptr< CharacterConfiguration > config, sf::Texture & texture ); 
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

	float m_runDuration;
	Animator m_runAnimator;

	float m_dieDurantion;
	Animator m_dieAnimator;
};