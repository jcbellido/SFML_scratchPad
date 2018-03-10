#pragma once

#include <SFML/Graphics.hpp>

template < typename T >
void centerOrigin( T& drawable )
{
	sf::FloatRect bound = drawable.getLocalBounds();
	drawable.setOrigin( bound.width / 2, 
						bound.height / 2 );
}