#include "Textures.h"

#include <iostream>

namespace Catan {

	Textures::Textures()
	{
	}

	std::string Textures::getPath(Name _name) {
		
		auto it =  mPaths.find(_name);
		if ( it == mPaths.end() ) {
			std::string lError = "No given path for texture";
			std::cout << "No given path for texture" << std::endl;
			throw std::logic_error("");
		}
		else {
			return it->second;
		}
	}

	Textures::~Textures()
	{
	}

	const std::map< Textures::Name, std::string> Textures::mPaths = {
		/* List below must contain all enums in Texture::Name */
		/* Textures of hex */
		{ Textures::TILE_WOOD,"textures/tile_texture_wood.png" },
		{ Textures::TILE_WHEAT,"textures/tile_texture_wheat.png" },
		{ Textures::TILE_SHEEP,"textures/tile_texture_sheep.png" },
		{ Textures::TILE_CLAY,"textures/tile_texture_clay.png" },
		{ Textures::TILE_IRON,"textures/tile_texture_iron.png" },
		{ Textures::TILE_DESERT,"textures/tile_texture_desert.png" },
		{ Textures::TILE_BLANK,"textures/tile_texture_blank.png" },
		{ Textures::TILE_NOT_USED,"textures/tile_texture_not_used.png" }
	};
}