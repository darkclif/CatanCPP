#pragma once

#include <map>
#include <string>

namespace Catan {

	class Textures
	{
	public:
		enum Name {
			/* All texture names */
			TILE_WOOD,
			TILE_WHEAT,
			TILE_SHEEP,
			TILE_CLAY,
			TILE_IRON,
			TILE_DESERT,
			TILE_BLANK,
			TILE_NOT_USED
		};

		static std::string getPath( Name _name );

		Textures();
		~Textures();
	private:

		static const std::map< Name, std::string> mPaths;
	};

}

