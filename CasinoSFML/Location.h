#pragma once
#include "DrawableEntity.h"
#include "PlayerEntity.h"
#include "SelectableMapItem.h"

#include <vector>

class Road;

class Location : public DrawableEntity, public PlayerEntity, public SelectableMapItem
{
public:
	enum Type {
		CITY,
		VILLAGE
	};

	enum Bonus {
		NONE,
		NORMAL_3_1,
		CLAY_2_1,
		WOOD_2_1,
		WHEAT_2_1,
		IRON_2_1,
		SHEEP_2_1
	};

	Location();
	~Location();

	// Control three roads
	bool addRoad(Road* _road);
	const std::vector<Road*>& getRoads();

	sf::Texture&			getTexture();
	void					draw(sf::RenderWindow& _window);

	void					setType(Type _type);
	Type					getType();

private:
	std::vector<Road*>		arrRoads;

	Type					type;
	Bonus					bonus;
};

