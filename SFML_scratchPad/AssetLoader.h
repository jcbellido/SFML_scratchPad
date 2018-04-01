#pragma once

#include <fstream>
#include <map>
#include <vector>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "nlohmann\json.hpp"
using json = nlohmann::json;

class AssetLoader
{
public:
	AssetLoader( std::string pathToJsonFile );
	std::string const & WindowName() const;
	int WindowWidth() const;
	int WindowHeight() const;

	std::shared_ptr< sf::Font > GetFont( std::string key );
	std::shared_ptr< sf::Texture > GetTexture( std::string key );

private:
	std::string m_windowName;
	int m_windowWidth;
	int m_windowHeight;

	std::map< sf::String, std::shared_ptr< sf::Font > > fonts; 
	std::map< sf::String, std::shared_ptr< sf::Texture > > textures; 
};