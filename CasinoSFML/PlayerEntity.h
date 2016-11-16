#pragma once
#include "Player.h"

class PlayerEntity
{
public:
	Player* getOwner();
	void setOwner( Player* _player);

	PlayerEntity() : owner{ nullptr } {};
	~PlayerEntity();
protected:
	Player* owner;
};

