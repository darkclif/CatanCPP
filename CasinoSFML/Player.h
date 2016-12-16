#pragma once

#include <string>

#include "SFML/Graphics.hpp"

#include "resources/Textures.h"
#include "ResourceBag.h"
#include "GameEnums.h"

namespace Catan {

	class Player
	{
	public:
		struct ItemCount {
			int	count;
			const int MAX;

			ItemCount(int _max) : MAX{ _max }, count{ _max } {};
			ItemCount(int _max, int _count) : MAX{ _max }, count{ _count } {};
		};

		struct PhaseBuildings {
			bool road = false;
			bool village = false;

			inline bool Completed() { return (road && village); }
		};

		Player(std::string _name, sf::Color _color, Textures::Name _avatar);
		~Player();

		PhaseBuildings	getPhaseState(RoundType);
		void			setPhaseState(RoundType, Item);

		void			giveResources(ResourceBag _bag);
		ResourceBag		getResources() const;

		void			takeResources(ResourceBag _bag);

		int				getItem(Item _item) const;
		void			takeItem(Item _item, int _count);
		void			giveItem(Item _item, int _count);

		void			recalculateWinPoints();
		int				getWinPoints() const;

		std::string		getName() const;
		sf::Color		getColor() const;
		Textures::Name getAvatarTexture() const;

	private:
		// Player info
		Textures::Name	avatarTexture;
		std::string				name;
		sf::Color				color;

		// Player items
		std::map<Item, ItemCount> items;
		ResourceBag				playerResources;

		int						winPoints;

		// Buildings in beginning rounds 
		// (to prevent building more than road and village per round)
		std::map<RoundType, PhaseBuildings>	buildingsInRound;
	};

}