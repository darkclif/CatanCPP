#include "ResourceManager.h"

#include <iostream>

sf::Texture & ResourceManager::getTexture( Catan::Textures::Name _texName )
{
	auto it = mTextureMap.find( _texName );

	if ( it != mTextureMap.end() ) {
		return *(it->second);
	}
	else {
		std::unique_ptr<sf::Texture> lTexture( new sf::Texture());
		std::string lSrc = Catan::Textures::getPath( _texName );

		if (!lTexture->loadFromFile(lSrc)) {
			std::string lError = "No texture file: " + lSrc;
			std::cout << lError << std::endl;
		}

		// Insert texture to map
		mTextureMap.insert( std::make_pair( _texName, std::move(lTexture)) );
		return *(mTextureMap.find(_texName)->second);
	}
}

sf::Font & ResourceManager::getFont(Catan::Fonts::Name _fontName)
{
	auto it = mFontMap.find(_fontName);

	if (it != mFontMap.end()) {
		return *(it->second);
	}
	else {
		std::unique_ptr<sf::Font> lFont( new sf::Font() );
		std::string lSrc = Catan::Fonts::getPath(_fontName);

		if (!lFont->loadFromFile(lSrc)) {
			std::string lError = "No font file: " + lSrc;
			std::cout << lError << std::endl;
		}

		// Insert texture to map
		mFontMap.insert(std::make_pair(_fontName, std::move(lFont) ));
		return *(mFontMap.find(_fontName)->second);
	}
}

void ResourceManager::Clear()
{
	mFontMap.clear();
	mTextureMap.clear();
}

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}
