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
		THIEF_ACTIVATED = 1 << 2,
		ROUND_TYPE = 1 << 3,
		ALL = PLAYER_RESOURCE | CURRENT_PLAYER | THIEF_ACTIVATED | ROUND_TYPE
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
		RoundType	roundType;
		int			roundNumber;

		RoundInfo() {
			isThrowed = false;
			dices[0] = 0;
			dices[1] = 0;
			roundType = BEGINNING_FORWARD;
			roundNumber = 0;
		}
	};
	/* END_Types */

	static const std::map<Item, ResourceBag> buildingsCosts;

	static bool canPlayerAffordItem(Item _item, Player* _player);

	Game(int _players, Map* _map);
	~Game();

	friend class PlayerGUI;
public:
	bool				getContentChange(unsigned int _change);

	RoundType			getRoundType() const;

private:
	void				nextRound();
	Player*				getCurrentPlayer();

	bool				throwDices();
	int					getDiceSum();

	bool				buildVillage(Player* _player, Location* _location);
	bool				buildCity(Player* _player, Location* _location);
	bool				buildRoad(Player * _player, Road * _road);

	void				setRoundType(RoundType _type);

	void				addContentChange(unsigned int _change);

private:
	Map*				gameMap;

private:
	unsigned int		contentChanges;

	RoundInfo			roundInfo;

	int					numCurrentPlayer;

	int					numPlayers;
	std::vector<Player> arrPlayers;
};

