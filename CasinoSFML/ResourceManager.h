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

	sf::Texture* getTexture( std::string _texName );

private:

	std::map< std::string, sf::Texture* > mTextureMap;

	// Singleton
	ResourceManager(const ResourceManager &) = delete;
	void operator=(ResourceManager const&) = delete;

	// Constructor / destructor
	ResourceManager();

	~ResourceManager();
};

