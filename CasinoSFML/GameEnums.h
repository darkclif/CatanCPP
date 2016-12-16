#pragma once


namespace Catan {

	enum class RoundType : char {
		BEGINNING_FORWARD = 1,
		BEGINNING_BACKWARD = 1 << 1,
		NORMAL = 1 << 2,

		BEGINNING = BEGINNING_BACKWARD | BEGINNING_FORWARD,
		ANY = NORMAL | BEGINNING_BACKWARD | BEGINNING_FORWARD
	};

	inline bool operator&(const RoundType& _type1, const RoundType& _type2) {
		return ((char)_type1 & (char)_type2) != 0;
	}

	enum class Card : int {
		KNIGHT = 1,

		MONOPOL = 1 << 1,
		BUILD_ROADS = 1 << 2,
		INVENTION = 1 << 3,

		LIBRARY = 1 << 4,
		MAIN_SQUARE = 1 << 5,
		CITY_HALL = 1 << 6,
		CATHEDRAL = 1 << 7,
		UNIVERSITY = 1 << 8,
		WP_CARD = LIBRARY | MAIN_SQUARE | CITY_HALL | CATHEDRAL | UNIVERSITY
	};

	enum class Item : int{
		ROAD = 0,
		VILLAGE,
		CITY,
		_SIZE
	};

	enum class SpecialCards : int {
		LONGEST_ROAD = 0,
		KNIGHT_RULER,
		_SIZE
	};

	enum class Resource : int {
		WOOD = 0,
		SHEEP,
		CLAY,
		IRON,
		WHEAT,
		_SIZE
	};

}