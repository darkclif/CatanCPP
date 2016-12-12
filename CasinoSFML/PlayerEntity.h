#pragma once
#include "Player.h"

class PlayerEntity
{
public:
	enum class RoundType : char{
		BEGINNING_FORWARD = 1,
		BEGINNING_BACKWARD = 1 << 1,
		NORMAL = 1 << 2,
		ANY = NORMAL | BEGINNING_FORWARD | BEGINNING_BACKWARD
	};

	void		setBuildRound(RoundType _round);
	RoundType	getBuildRound();

	Player*		getOwner();
	void		setOwner( Player* _player);

	bool		hasOwner();

	PlayerEntity() : owner{ nullptr }, buildRound{RoundType::ANY} {};
	~PlayerEntity();

protected:
	RoundType	buildRound;

	Player*		owner;
};

