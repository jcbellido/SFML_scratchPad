#pragma once

#include <SFML/Graphics.hpp>

class Character : public sf::Drawable, public sf::Transformable
{
public:
	Character ();

	void SetSpeed ( float speed );
	float GetSpeed () const;

private:
	float m_speed;
};