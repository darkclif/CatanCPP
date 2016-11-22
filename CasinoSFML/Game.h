#pragma once
#include <vector>

#include "Player.h"
#include "Map.h"

class Game
{
public:
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
public:


private:
	void				nextRound();
	Player*				getCurrentPlayer();

	bool				throwDices();

	RoundType			getRoundType();
	void				setRoundType(RoundType _type);
private:
	Map* gameMap;

private:
	RoundInfo			roundInfo;

	int					numCurrentPlayer;

	int					numPlayers;
	std::vector<Player> arrPlayers;
};

