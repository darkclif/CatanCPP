#include "ResourceManager.h"



sf::Texture* ResourceManager::getTexture( std::string _texName )
{
	typedef std::map < std::string, sf::Texture* >::iterator lIterator;
	lIterator it = mTextureMap.find( _texName );

	if ( it != mTextureMap.end() ) {
		return it->second;
	}
	else {
		sf::Texture* lTexture = new sf::Texture();
		std::string lSrc = "textures/" + _texName + ".png";

		if (!lTexture->loadFromFile(lSrc)) {
			delete lTexture;
			throw std::runtime_error("No texture file: " + lSrc);
		}

		// Insert texture to map
		mTextureMap.insert( std::make_pair( _texName, lTexture) );
		return lTexture;
	}
}

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
	// Delete all stored textures
	typedef std::map < std::string, sf::Texture* >::iterator lIterator;
	for (lIterator it = mTextureMap.begin(); it != mTextureMap.end(); it++ ) {
		delete it->second;
	}
}
