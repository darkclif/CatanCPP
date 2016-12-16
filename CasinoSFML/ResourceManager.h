#pragma once
#include <SFML/Graphics.hpp>

#include <map>
#include <memory>

#include "resources/Textures.h"
#include "resources/Fonts.h"

namespace Catan {

#define ResourceMgr ResourceManager::getInstance()

	class ResourceManager
	{
	public:
		static ResourceManager& getInstance() {
			static ResourceManager instance;
			return instance;
		};

		// Resource acccesors 
		sf::Texture&	getTexture(Textures::Name _texName);
		sf::Font&		getFont(Fonts::Name _fontName);

	private:

		// Resource conteners 
		std::map< Textures::Name, std::unique_ptr<sf::Texture> > mTextureMap;
		std::map< Fonts::Name, std::unique_ptr<sf::Font> > mFontMap;

		// Clear data
		void Clear();

		// Singleton
		ResourceManager(const ResourceManager &) = delete;
		void operator=(ResourceManager const&) = delete;

		// Constructor / destructor
		ResourceManager();
		~ResourceManager();
	};

}