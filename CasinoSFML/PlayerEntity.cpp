#include "PlayerEntity.h"

Player * PlayerEntity::getOwner()
{
	return owner;
}

void PlayerEntity::setOwner(Player * _player)
{
	owner = _player;
}

PlayerEntity::~PlayerEntity()
{
}
