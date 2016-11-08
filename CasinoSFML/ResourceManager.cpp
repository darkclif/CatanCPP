#include "ResourceManager.h"

#include <iostream>

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

			std::string lError = "No texture file: " + lSrc;
			std::cout << lError << std::endl;
			//throw std::runtime_error(lError);
		}

		// Insert texture to map
		mTextureMap.insert( std::make_pair( _texName, lTexture) );
		return lTexture;
	}
}

sf::Font * ResourceManager::getFont(std::string _fontName)
{
	typedef std::map < std::string, sf::Font* >::iterator lIterator;
	lIterator it = mFontMap.find(_fontName);

	if (it != mFontMap.end()) {
		return it->second;
	}
	else {
		sf::Font* lFont = new sf::Font();
		std::string lSrc = "fonts/" + _fontName + ".ttf";

		if (!lFont->loadFromFile(lSrc)) {
			delete lFont;

			std::string lError = "No font file: " + lSrc;
			std::cout << lError << std::endl;
			//throw std::runtime_error(lError);
		}

		// Insert texture to map
		mFontMap.insert(std::make_pair(_fontName, lFont));
		return lFont;
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
