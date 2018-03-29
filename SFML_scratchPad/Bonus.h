#pragma once

#include <SFML/Graphics.hpp>

class Bonus : public sf::Drawable, public sf::Transformable
{
public:
	enum Fruit 
	{
		Banana,
		Apple,
		Cherry
	};

	Bonus( sf::Texture & texture );

	void SetFruit( Fruit fruit );

private:
	sf::Sprite m_visual;

	void draw( sf::RenderTarget& target,
			   sf::RenderStates states ) const;
};