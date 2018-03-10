#include <iostream>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main ( int argc, char* args[] )
{
	int style =  sf::Style::None | sf::Style::Resize;

	sf::Window window( sf::VideoMode( 800, 600 ), "Module Window", style );
	
	auto desktopMode = sf::VideoMode::getDesktopMode();

	std::cout << "width " << desktopMode.width << std::endl;
	std::cout << "height " << desktopMode.height << std::endl;
	std::cout << "bits per pix " << desktopMode.bitsPerPixel << std::endl;

	while( window.isOpen() )
	{
		sf::Event event;

		while( window.pollEvent( event ) )
		{
			if ( event.type == sf::Event::Closed )
				window.close();
		}

		window.display();
		sf::sleep( sf::seconds( 1.0f / 60.0f ) ) ;
	}
	return EXIT_SUCCESS;
}

int fromSFMLTutPage_main ( int argc, char* args[] )
{
	// Create the main window
	sf::RenderWindow window ( sf::VideoMode ( 800, 600 ), "SFML window" );

	// Load a sprite to display
	sf::Texture texture;
	if ( !texture.loadFromFile ( "resources/cute_image.jpg" ) )
		return EXIT_FAILURE;
	
	sf::Sprite sprite ( texture );
	
	// Create a graphical text to display
	sf::Font font;
	if ( !font.loadFromFile ( "resources/sansation.ttf" ) )
		return EXIT_FAILURE;
	sf::Text text ( "Hello SFML", font, 50 );
	
	// Load a music to play
	sf::Music music;
	if ( !music.openFromFile ( "resources/nice_music.ogg" ) )
		return EXIT_FAILURE;
	// Play the music
	music.play ();
	
	// Start the game loop
	while ( window.isOpen () )
	{
		// Process events
		sf::Event event;
		while ( window.pollEvent ( event ) )
		{
			// Close window: exit
			if ( event.type == sf::Event::Closed )
				window.close ();
		}
		// Clear screen
		window.clear ();
		// Draw the sprite
		window.draw ( sprite );
		// Draw the string
		window.draw ( text );
		// Update the window
		window.display ();
	}
	return EXIT_SUCCESS;
}