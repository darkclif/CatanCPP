#pragma once
#include <map>
#include <SFML/Graphics.hpp>

class ResourceManager
{
public:
	static ResourceManager& getInstance() {
		static ResourceManager instance;
		return instance;
	};

	// Get texture 
	sf::Texture* getTexture( std::string _texName );

	// Get font 
	sf::Font* getFont( std::string _fontName );

private:

	std::map< std::string, sf::Texture* > mTextureMap;

	std::map< std::string, sf::Font* > mFontMap;

	// Singleton
	ResourceManager(const ResourceManager &) = delete;
	void operator=(ResourceManager const&) = delete;

	// Constructor / destructor
	ResourceManager();

	~ResourceManager();
};

