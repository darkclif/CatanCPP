#pragma once

#include "Player.h"

class Place
{
public:
	Player& getOwner() {
		return *owner;
	}

protected:
	Player* owner;

	Place(): owner{ nullptr } {
	}

	Place(Player* _owner) : owner{ _owner } {
	};

	virtual ~Place() = 0;
};

