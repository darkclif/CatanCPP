#include "PlayerEntity.h"

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
	return !(owner == nullptr);
}

PlayerEntity::~PlayerEntity()
{
}
