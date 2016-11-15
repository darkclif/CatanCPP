#pragma once
#include <SFML/Graphics.hpp>

#include <map>
#include <memory>

#include "resources/Textures.h"
#include "resources/Fonts.h"

class ResourceManager
{
public:
	static ResourceManager& getInstance() {
		static ResourceManager instance;
		return instance;
	};

	// Resource acccesors 
	sf::Texture& getTexture( Catan::Textures::Name _texName );
	sf::Font& getFont(Catan::Fonts::Name _fontName );

private:

	// Resource conteners 
	std::map< Catan::Textures::Name, std::unique_ptr<sf::Texture> > mTextureMap;
	std::map< Catan::Fonts::Name, std::unique_ptr<sf::Font> > mFontMap;

	// Clear data
	void Clear();

	// Singleton
	ResourceManager(const ResourceManager &) = delete;
	void operator=(ResourceManager const&) = delete;

	// Constructor / destructor
	ResourceManager();
	~ResourceManager();
};

