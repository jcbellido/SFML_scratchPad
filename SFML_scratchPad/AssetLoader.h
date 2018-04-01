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
	std::map< std::string, float > Parameters;
};

using spFont = std::shared_ptr< sf::Font >;
using spCharConfig = std::shared_ptr< CharacterConfiguration >;
using spMusic = std::shared_ptr< sf::Music >;
using spSoundBuffer = std::shared_ptr< sf::SoundBuffer >;
using spTexture = std::shared_ptr< sf::Texture >;

using characterConfigurationMap = std::map< sf::String, spCharConfig >;
using fontMap = std::map< sf::String, spFont >;
using musicMap = std::map< sf::String, spMusic >;
using soundBufferMap = std::map< sf::String, spSoundBuffer >;
using textureMap = std::map< sf::String, spTexture >;

class AssetLoader
{
public:
	AssetLoader( std::string pathToJsonFile );
	std::string const & WindowName() const;
	int WindowWidth() const;
	int WindowHeight() const;

	spFont GetFont( std::string key );
	spMusic GetMusic( std::string key );
	spTexture GetTexture( std::string key );
	spSoundBuffer GetSound( std::string key );
	spCharConfig GetCharacterConfig( std::string key );

private:
	void LoadWindowConfiguration();
	void LoadResources();
	void LoadCharacters();

private:
	json m_configuration;
	std::string m_windowName;
	int m_windowWidth;
	int m_windowHeight;

	characterConfigurationMap characters;
	fontMap fonts; 
	musicMap musics;
	soundBufferMap sounds;
	textureMap textures;
};
