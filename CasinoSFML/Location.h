#pragma once
#include "DrawableEntity.h"
#include "PlayerEntity.h"
#include "SelectableMapItem.h"

#include <vector>

namespace Catan {

	class Road;

	class Location : public DrawableEntity, public PlayerEntity, public SelectableMapItem
	{
	public:
		enum class Type {
			CITY,
			VILLAGE,
			NONE
		};

		enum class Bonus {
			NORMAL_3_1,
			CLAY_2_1,
			WOOD_2_1,
			WHEAT_2_1,
			IRON_2_1,
			SHEEP_2_1,
			NONE
		};

		bool						addRoad(Road* _road);
		const std::vector<Road*>&	getRoads();

		bool					isNeighbourLocation();
		bool					isNearPlayerRoad(Player* _player);

		sf::Texture&			getTexture();
		void					draw(sf::RenderWindow& _window);

		void					setType(Type _type);
		Type					getType();

		void					setBonus(Bonus _type);
		Bonus					getBonus();

		void					Build(Type _type, Player* _player, RoundType _round = RoundType::NORMAL);

		Location();
		~Location();
	private:
		std::vector<Road*>		arrRoads;

		Type					type;
		Bonus					bonus;
	};

}