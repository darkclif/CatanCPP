#include "ResourceManager.h"

#include <iostream>
#include "Console.h"

sf::Texture & ResourceManager::getTexture( Catan::Textures::Name _texName )
{
	auto it = mTextureMap.find( _texName );

	if ( it != mTextureMap.end() ) {
		return *(it->second);
	}
	else {
		// Load new texture
		std::unique_ptr<sf::Texture> lTexture( new sf::Texture());
		std::string lSrc = Catan::Textures::getPath( _texName );

		if (!lTexture->loadFromFile(lSrc)) {
			Console::debug << "No texture file found in path: " + lSrc;

			lSrc = Catan::Textures::getPath(Catan::Textures::Name::TEXTURE_ERROR);

			if (!lTexture->loadFromFile(lSrc))
				throw std::logic_error("Cannot load Textures::Name::TEXTURE_ERROR");
		}

		// Insert to map
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
		// Add new font
		std::unique_ptr<sf::Font> lFont( new sf::Font() );
		std::string lSrc = Catan::Fonts::getPath(_fontName);

		if (!lFont->loadFromFile(lSrc)) {
			Console::debug << "No font file found in path: " + lSrc;

			lSrc = Catan::Fonts::getPath(Catan::Fonts::Name::DEFAULT);

			if (!lFont->loadFromFile(lSrc))
				throw std::logic_error("Cannot load Fonts::Name::DEFAULT");
		}

		// Insert to map
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
