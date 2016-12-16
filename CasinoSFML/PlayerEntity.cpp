#include "PlayerEntity.h"

namespace Catan {

	void PlayerEntity::setBuildRound(RoundType _round)
	{
		buildRound = _round;
	}

	PlayerEntity::RoundType PlayerEntity::getBuildRound()
	{
		return buildRound;
	}

	Player * PlayerEntity::getOwner()
	{
		return owner;
	}

	void PlayerEntity::setOwner(Player * _player)
	{
		owner = _player;
	}

	bool PlayerEntity::hasOwner()
	{
		return (owner != nullptr);
	}

	PlayerEntity::~PlayerEntity()
	{
	}

}