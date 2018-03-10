#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

sf::RenderWindow  * window = nullptr;

sf::RectangleShape * rectangle = nullptr;
sf::CircleShape * circle = nullptr;
sf::ConvexShape * customShape = nullptr;

sf::Image * image;
sf::Texture * texture;
sf::Sprite * sprite;

sf::Text * text;
sf::Font * font;

void draw ()
{
	window->clear (); // Really neccessary? 

	window->draw ( *sprite );

	window->draw ( *rectangle );
	window->draw ( *circle );
	window->draw ( *customShape );

	window->draw( * text );

	window->display ();
}

void cleanup ()
{
	if ( rectangle != nullptr )
		delete( rectangle );

	if ( circle != nullptr )
		delete( circle );

	if ( customShape != nullptr )
		delete( customShape );

	if ( image != nullptr )
		delete( image );

	if ( texture != nullptr )
		delete( texture );

	if ( sprite != nullptr )
		delete( sprite );

	if ( text != nullptr )
		delete( text );

	if ( font != nullptr )
		delete( font );

	if ( window != nullptr )
		delete( window );
}

void buildAssets ()
{
	rectangle = new sf::RectangleShape ();
	rectangle->setSize ( sf::Vector2f ( 200, 100 ) );
	rectangle->setFillColor ( sf::Color::Magenta );
	rectangle->setOutlineThickness ( 3 );
	rectangle->setOutlineColor ( sf::Color::Cyan );
	rectangle->setPosition ( sf::Vector2f ( 100, 100 ) );

	circle = new sf::CircleShape ();
	circle->setRadius ( 20 );
	circle->setFillColor ( sf::Color::Blue );
	circle->setOutlineThickness ( 2 );
	circle->setPosition ( sf::Vector2f ( 220, 200 ) );

	customShape = new sf::ConvexShape ();
	customShape->setPointCount ( 3 );
	customShape->setPoint ( 0, sf::Vector2f ( 0, 0 ) );
	customShape->setPoint ( 1, sf::Vector2f ( 150, 30 ) );
	customShape->setPoint ( 2, sf::Vector2f ( 0, 60 ) );
	customShape->setFillColor ( sf::Color::Yellow );
	customShape->setPosition ( sf::Vector2f ( 300, 500 ) );

	image = new sf::Image ();
	image->loadFromFile ( "resources/cute_image.jpg" );

	texture = new sf::Texture ();
	texture->loadFromImage ( *image );
	sprite = new sf::Sprite ( *texture );

	font = new sf::Font();
	font->loadFromFile( "resources/sansation.ttf" );

	text = new sf::Text();
	text->setFont( * font );
	text->setString( " Mondogos GORDOS ");
	text->setFillColor( sf::Color::Blue );
	text->setOutlineThickness( 3 );
	text->setOutlineColor( sf::Color::Red );
	text->setPosition( sf::Vector2f( 300, 300 ) );
}

int main ( int argc, char* args[] )
{
	int style = sf::Style::Resize;	// Want to see what happens when using absolute pixel coordinates

	window = new sf::RenderWindow ( sf::VideoMode ( 800, 600 ), "SFML window", style );

	buildAssets ();

	while ( window->isOpen () )
	{
		sf::Event event;
		while ( window->pollEvent ( event ) )
		{
			if ( event.type == sf::Event::Closed )
				window->close ();
		}

		draw ();
		// simming the update ? 
		window->setFramerateLimit ( 60 );
		sf::sleep ( sf::seconds ( 1.0f / 60.0f ) );
	}
	cleanup ();
	return EXIT_SUCCESS;
}

