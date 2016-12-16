#pragma once
#include "DrawableEntity.h"
#include "SelectableMapItem.h"

#include <vector>
#include <iostream>
#include "PlayerEntity.h"

namespace Catan {

	class Location;

	class Road : public DrawableEntity, public SelectableMapItem, public PlayerEntity
	{
	public:
		Road();
		~Road();

		bool							addLocation(Location* _location);
		const std::vector<Location*>&	getLocations();

		sf::Texture&		getTexture();
		void				draw(sf::RenderWindow& _window);

		bool				isNeighbourWithLocation(Player* _player, RoundType _round = RoundType::ANY);
		bool				isBesidePlayerItem(Player* _player);

	private:

		std::vector<Location*> arrLocations;
	};

}