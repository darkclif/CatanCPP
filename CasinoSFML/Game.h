#pragma once
#include <vector>

#include "Player.h"
#include "Map.h"

class PlayerGUI;

class Game
{
public:
	enum ContentChange {
		PLAYER_RESOURCE = 1,
		CURRENT_PLAYER = 1 << 1,
		THIEF_ACTIVATED = 1 << 2
	};

	enum RoundType {
		BEGINNING_FORWARD,
		BEGINNING_BACKWARD,
		NORMAL
	};

	struct RoundInfo {
		bool		isThrowed;
		int			dices[2];
		RoundType	roundType;
		int			roundNumber;

		RoundInfo() {
			isThrowed = false;
			dices[0] = 0; dices[1] = 0;
			roundType = BEGINNING_FORWARD;
			roundNumber = 0;
		}
	};

	Game(int _players, Map* _map);
	~Game();

	friend class PlayerGUI;
public:
	bool				getContentChange(unsigned int _change);

private:
	void				nextRound();
	Player*				getCurrentPlayer();

	bool				throwDices();
	int					getDiceSum();

	bool				buildLocation(Player* _player, Location* _location);
	bool				buildRoad(Player * _player, Road * _road);

	RoundType			getRoundType();
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

