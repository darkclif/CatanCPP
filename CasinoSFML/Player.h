#pragma once

#include <string>

#include "SFML/Graphics.hpp"

#include "resources/Textures.h"
#include "ResourceBag.h"

class Player
{
public:
	enum class Item : int{
		ROAD = 0,
		CITY,
		VILLAGE,
		_SIZE
	};

	enum class Phase : int {
		BEGINNING_FORWARD,
		BEGINNING_BACKWARD,
		_SIZE
	};

	struct PhaseBuildings {
		bool road = false;
		bool village = false;

		inline bool Completed() { return (road && village); }
	};

	Player( std::string _name, sf::Color _color, Catan::Textures::Name _avatar);
	~Player();

	PhaseBuildings	getPhaseState(Phase);
	void			setPhaseState(Phase, Item);

	void			giveResources(ResourceBag _bag);
	ResourceBag		getResources() const;

	void			takeResources(ResourceBag _bag);

	int				getItem(Item _item) const;
	void			takeItem(Item _item, int _count);
	void			giveItem(Item _item, int _count);

	std::string		getName() const;
	sf::Color		getColor() const;
	Catan::Textures::Name getAvatarTexture() const;

private:
	// Player info
	Catan::Textures::Name	avatarTexture;
	std::string				name;
	sf::Color				color;

	// Player items
	std::vector<int>		items;
	ResourceBag				playerResources;

	// Beginning phases states
	PhaseBuildings			phaseBuilings[(int)(Phase::_SIZE)];
};

