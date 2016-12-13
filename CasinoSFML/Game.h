#pragma once
#include <vector>

#include "Player.h"
#include "Map.h"
#include "Resourcebag.h"

class PlayerGUI;

class Game
{
public:
	/* Types */
	enum Item {
		ROAD,
		VILLAGE,
		CITY
	};

	enum ContentChange : unsigned int{
		PLAYER_RESOURCE = 1,
		CURRENT_PLAYER = 1 << 1,
		MENU_BUTTONS = 1 << 2,
		DICE_THROW = 1 << 3,
		ALL = PLAYER_RESOURCE | CURRENT_PLAYER | MENU_BUTTONS | DICE_THROW
	};

	enum RoundType : char{
		BEGINNING_FORWARD = 1,
		BEGINNING_BACKWARD = 1 << 1,
		NORMAL = 1 << 2,
		BEGINNING = BEGINNING_BACKWARD | BEGINNING_FORWARD,
		ANY = NORMAL | BEGINNING_BACKWARD | BEGINNING_FORWARD
	};

	struct RoundInfo {
		bool		isThrowed;
		int			dices[2];
		bool		isThiefAwaken;

		RoundType	roundType;
		int			roundNumber;
		
		RoundInfo() {
			roundType = BEGINNING_FORWARD;
			roundNumber = 0;

			isThiefAwaken = false;
			isThrowed = false;
			dices[0] = 0;
			dices[1] = 0;
		}
	};
	/* END_Types */

	static const std::map<Item, ResourceBag>	buildingsCosts;
	static bool									canPlayerAffordItem(Item _item, Player* _player);

	Game(int _players, Map* _map);
	~Game();

	friend class PlayerGUI;

public:
	bool				getContentChange(unsigned int _change);

	RoundType			getRoundType() const;
	RoundInfo			getRoundInfo() const;

private:
	/* Game flow */
	bool				nextRound();
	bool				throwDices();

	bool				buildVillage(Player* _player, Location* _location);
	bool				buildCity(Player* _player, Location* _location);
	bool				buildRoad(Player * _player, Road * _road);

	bool				setThiefTile(Player* _player, Tile* _tile);
	/* END_Game flow */

	void				setRoundType(RoundType _type);
	void				addContentChange(unsigned int _change);

	int					getDiceSum();
	Player*				getCurrentPlayer();

private:
	Map*				gameMap;

private:
	unsigned int		contentChanges;

	RoundInfo			roundInfo;

	int					numCurrentPlayer;

	int					numPlayers;
	std::vector<Player> arrPlayers;
};

