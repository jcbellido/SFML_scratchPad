#include "AssetLoader.h"

AssetLoader::AssetLoader(  std::string pathToJsonFile  )
{
	json configuration;
	std::ifstream configFile ( pathToJsonFile );
	configFile >> configuration;

	m_windowName   = configuration[ "GameConfig" ][ "WindowTitle" ];
	m_windowWidth  = configuration[ "GameConfig" ][ "WindowWidth" ];
	m_windowHeight = configuration[ "GameConfig" ][ "WindowHeight"];

	for( auto res : configuration["Resources"] )
	{
		std::string typeName = res[ "Type" ];
		std::string assetName = res[ "Name" ];
		std::string assetPath = res[ "File" ];

		if( typeName == "Font" )
		{
			auto f = std::make_shared< sf::Font >();
			f->loadFromFile( assetPath );
			fonts[ assetName ] = f;
		}
		else if( typeName == "Texture" )
		{
			auto t = std::make_shared< sf::Texture >();
			t->loadFromFile( assetPath );
			textures[ assetName ] = t;
		}
	}
}

std::string const & AssetLoader::WindowName () const
{
	return m_windowName;
}

int AssetLoader::WindowWidth () const
{
	return m_windowWidth;

}
int AssetLoader::WindowHeight () const
{
	return m_windowHeight;
}

std::shared_ptr< sf::Font > AssetLoader::GetFont( std::string key ) 
{
	auto result = fonts.find( key );
	if ( result == fonts.end() )
	{
		return nullptr;
	}
	return result->second;
}
	
std::shared_ptr< sf::Texture > AssetLoader::GetTexture( std::string key )
{
	auto result = textures.find( key );
	if ( result == textures.end() )
	{
		return nullptr;
	}
	return result->second;
}
