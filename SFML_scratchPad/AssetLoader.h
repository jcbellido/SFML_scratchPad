#pragma once

#include <fstream>
#include <map>
#include <vector>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "nlohmann\json.hpp"
using json = nlohmann::json;

#include "Animator.h"

class CharacterConfiguration
{
public:
	float Speed;
	sf::Vector2f Origin;
	
	std::map< std::string, Animator > Animators;
};

class AssetLoader
{
public:
	AssetLoader( std::string pathToJsonFile );
	std::string const & WindowName() const;
	int WindowWidth() const;
	int WindowHeight() const;

	std::shared_ptr< sf::Font > GetFont( std::string key );
	std::shared_ptr< sf::Texture > GetTexture( std::string key );
	std::shared_ptr< CharacterConfiguration > GetCharacterConfig( std::string key );

private:
	void LoadWindowConfiguration();
	void LoadResources();

private:
	json m_configuration;
	std::string m_windowName;
	int m_windowWidth;
	int m_windowHeight;

	std::map< sf::String, std::shared_ptr< sf::Font > > fonts; 
	std::map< sf::String, std::shared_ptr< sf::Texture > > textures;
	std::map< sf::String, std::shared_ptr< CharacterConfiguration > > characters;
};