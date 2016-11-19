#include "Textures.h"

#include <iostream>
#include "../Console.h"

namespace Catan {

	Textures::Textures()
	{
	}

	Textures::~Textures()
	{
	}

	std::string Textures::getPath(Name _name) {
		
		auto it =  mPaths.find(_name);
		if ( it == mPaths.end() ) {
			std::string lError = "Path to texture not assigned to given texture name";
			Console::debug << lError << std::endl;
			throw std::logic_error(lError);
		}
		else {
			return it->second;
		}
	}

	const std::map< Textures::Name, std::string> Textures::mPaths = {
		/* List below must contain all enums in Texture::Name */
		{ Catan::Textures::Name::TEXTURE_ERROR, "textures/texture_error.png" },
		{ Catan::Textures::Name::TEXTURE_EMPTY, "textures/texture_empty.png" },
		/** MISC **/
		{ Textures::LOGO,"textures/logo.png" },
		{ Textures::BIG_LOGO,"textures/big_logo.png" },
		/** MAP **/
		/* Hex */
		{ Textures::TILE_WOOD,"textures/tile_texture_wood.png" },
		{ Textures::TILE_WHEAT,"textures/tile_texture_wheat.png" },
		{ Textures::TILE_SHEEP,"textures/tile_texture_sheep.png" },
		{ Textures::TILE_CLAY,"textures/tile_texture_clay.png" },
		{ Textures::TILE_IRON,"textures/tile_texture_iron.png" },
		{ Textures::TILE_DESERT,"textures/tile_texture_desert.png" },
		{ Textures::TILE_BLANK,"textures/tile_texture_blank.png" },
		{ Textures::TILE_NOT_USED,"textures/tile_texture_not_used.png" },
		/* Hex dice numbers*/
		{ Textures::Name::TILE_DICE_NUM_2, "textures/tile_dice_num_2.png"},
		{ Textures::Name::TILE_DICE_NUM_3, "textures/tile_dice_num_3.png"},
		{ Textures::Name::TILE_DICE_NUM_4, "textures/tile_dice_num_4.png"},
		{ Textures::Name::TILE_DICE_NUM_5, "textures/tile_dice_num_5.png"},
		{ Textures::Name::TILE_DICE_NUM_6, "textures/tile_dice_num_6.png"},
		{ Textures::Name::TILE_DICE_NUM_8, "textures/tile_dice_num_8.png"},
		{ Textures::Name::TILE_DICE_NUM_9, "textures/tile_dice_num_9.png"},
		{ Textures::Name::TILE_DICE_NUM_10, "textures/tile_dice_num_10.png"},
		{ Textures::Name::TILE_DICE_NUM_11, "textures/tile_dice_num_11.png"},
		{ Textures::Name::TILE_DICE_NUM_12, "textures/tile_dice_num_12.png"},
		/* Locations */
		{ Textures::Name::ROAD, "textures/road.png" },
		{ Textures::Name::CITY, "textures/city.png" },
		{ Textures::Name::VILLAGE, "textures/village.png" },
		/* Thief icon*/
		{ Textures::Name::THIEF, "textures/thief.png" }
	};
}