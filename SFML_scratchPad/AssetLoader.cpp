#include "AssetLoader.h"

AssetLoader::AssetLoader(  std::string pathToJsonFile  )
{
	std::ifstream configFile ( pathToJsonFile );
	configFile >> m_configuration;

	LoadWindowConfiguration();
	LoadResources();
	LoadCharacters();
}

void AssetLoader::LoadCharacters()
{
	for( auto character : m_configuration[ "Characters" ] )
	{
		std::shared_ptr< CharacterConfiguration > cc = std::make_shared< CharacterConfiguration >();
		std::string characterName = character[ "Name" ];
		cc->Origin = sf::Vector2f( character[ "Origin" ][ "x" ], character[ "Origin" ][ "x" ] );
		cc->Speed  = character[ "Speed" ];

		for( auto animator : character[ "Animators" ] ) 
		{
			Animator anim;
			for( auto frame : animator[ "Frames" ] )
			{
				anim.AddFrame( sf::IntRect( frame[ "rl" ], frame[ "rt" ], frame[ "rw" ], frame[ "rh" ] ) );
			}

			cc->Animators[ animator[ "Name"] ] = anim;
		}

		characters[ characterName ] = cc;
	}
}

void AssetLoader::LoadResources()
{
	for( auto res : m_configuration["Resources"] )
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
		else if( typeName == "Music" )
		{
			auto m = std::make_shared< sf::Music >();
			m->openFromFile( assetPath );
			musics[ assetName ] = m;
		}
		else if( typeName == "Sound" )
		{
			auto sb = std::make_shared< sf::SoundBuffer >();
			sb->loadFromFile( assetPath );
			sounds[ assetName ] = sb;
		}
	}
}

void AssetLoader::LoadWindowConfiguration()
{
	m_windowName   = m_configuration[ "GameConfig" ][ "WindowTitle" ];
	m_windowWidth  = m_configuration[ "GameConfig" ][ "WindowWidth" ];
	m_windowHeight = m_configuration[ "GameConfig" ][ "WindowHeight"];
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

std::shared_ptr< CharacterConfiguration > AssetLoader::GetCharacterConfig ( std::string key )
{
	auto result = characters.find( key );
	if( result == characters.end() )
	{
		return nullptr;
	}
	return result->second;
}

std::shared_ptr< sf::Music > AssetLoader::GetMusic ( std::string key )
{
	auto result = musics.find( key );
	if( result == musics.end() )
	{
		return nullptr;
	}
	return result->second;
}

std::shared_ptr< sf::SoundBuffer > AssetLoader::GetSound ( std::string key )
{
	auto result = sounds.find( key );
	if( result == sounds.end() )
	{
		return nullptr;
	}
	return result->second;
}
