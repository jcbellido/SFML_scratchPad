#include <iostream>

#include <SFML/System.hpp>

int windowModule_main ( int argc, char* args[] )
{
	sf::Time time;
	sf::Clock clock;

	sf::Time time1 = sf::seconds( 1.2f );
	sf::Time time2 = sf::milliseconds( 1200 );
	sf::Time time3 = sf::microseconds( 1000000 );

	time = time1 + time2 - time3;

	auto timeInSeconds = time.asSeconds();
	auto timeInMilliseconds = time.asMilliseconds();
	auto timeInMicroseconds = time.asMicroseconds();

	std::cout << timeInSeconds << std::endl;
	std::cout << timeInMilliseconds << std::endl;
	std::cout << timeInMicroseconds << std::endl;

	return 0;
}