#pragma once

#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

#include "Location.h"
#include "Road.h"
#include "ResourceManager.h"
#include "resources/Textures.h"
#include "DrawableEntity.h"
#include "ResourceBag.h"
#include "SelectableMapItem.h"

namespace Catan {

	//
	//	Dice number
	//
	class DiceNumber : public DrawableEntity {
	public:
		void draw(sf::RenderWindow& _window);

		void setNumber(int _number);

		DiceNumber(sf::Vector2f _position, DrawableEntity* _parent) : DrawableEntity(_position, 0, _parent), number{ 0 } {}
		DiceNumber() : DrawableEntity(), number{ 0 } { }
	protected:
		sf::Texture& getTexture();

		int number;
		static const Textures::Name arrDiceToTexture[11];

	};

	//
	//	Thief
	//
	class Thief : public DrawableEntity {
	public:
		void draw(sf::RenderWindow& _window);

		Thief() : DrawableEntity() {}
		Thief(sf::Vector2f _position, DrawableEntity* _parent) : DrawableEntity(_position, 0, _parent) {}
	protected:
		sf::Texture& getTexture();
	};

	//
	// Tile
	//
	class Tile : public DrawableEntity, public SelectableMapItem
	{
	public:
		// Type of tiles
		enum TileType : int {
			WOOD = 1,
			SHEEP = 1 << 1,
			CLAY = 1 << 2,
			IRON = 1 << 3,
			WHEAT = 1 << 4,
			DESERT = 1 << 5,

			BLANK = 1 << 6,		// Resource to assign 
			NOT_USED = 1 << 7,

			RESOURCE = WOOD | SHEEP | CLAY | IRON | WHEAT,

			__ENUM_SIZE
		};

		Tile(TileType _type, unsigned int _number);
		Tile();

		~Tile();

		bool				isThief();
		void				setThief(bool _thief);

		void				giveResourceToPlayers();

		TileType			getType();
		void				setType(TileType _type);

		int					getDiceNumber();
		void				setDiceNumber(int _number);

		sf::Texture&		getTexture();
		void				draw(sf::RenderWindow & _window);

		// Access soroundings 
		bool				addRoad(Road* _road, int _number);
		Road*				getRoad(int _number);

		bool				addLocation(Location* _location, int _number);
		Location*			getLocation(int _number);

		bool				bindRoadsLocations();

		// For initialize circle-style map
		int					getInitJump();
		void				setInitJump(int _jump);
	private:
		Resource			getResourceType();

	private:
		TileType		type;
		unsigned int	diceNumber;
		bool			thief;

		// For initialize circle-style map
		int				initJump;

		std::vector<Location*>						arrLocations;
		std::vector<Road*>							arrRoads;

		std::unique_ptr<Thief>						thiefEntity;
		std::unique_ptr<DiceNumber>					numberEntity;

		static const std::map<TileType, Textures::Name>	mapTypeToTexture;
		static const std::map<TileType, Resource>	mapTypeToResource;
	};

}