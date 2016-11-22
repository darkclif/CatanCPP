#pragma once

#include <map>
#include <string>

namespace Catan {

	class Textures
	{
	public:
		enum Name {
			/* All texture names */
			/* Misc.*/
			BIG_LOGO,
			LOGO,
			MENU_BG_2,

			/* Avatars */
			AVATAR_1,AVATAR_2,AVATAR_3,
			AVATAR_4,AVATAR_5,AVATAR_6,

			/* Map */
			TEXTURE_ERROR,
			TEXTURE_EMPTY,

			TILE_WOOD,
			TILE_WHEAT,
			TILE_SHEEP,
			TILE_CLAY,
			TILE_IRON,
			TILE_DESERT,
			TILE_BLANK,
			TILE_NOT_USED,

			TILE_DICE_NUM_2,
			TILE_DICE_NUM_3,
			TILE_DICE_NUM_4,
			TILE_DICE_NUM_5,
			TILE_DICE_NUM_6,
			TILE_DICE_NUM_8,
			TILE_DICE_NUM_9,
			TILE_DICE_NUM_10,
			TILE_DICE_NUM_11,
			TILE_DICE_NUM_12,

			ROAD,
			CITY,
			VILLAGE,

			THIEF
		};

		static std::string getPath( Name _name );

		Textures();
		~Textures();
	private:
		// Paths to resources
		static const std::map< Name, std::string> mPaths;
	};

}

