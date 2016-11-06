#pragma once
#include "Place.h"
class Location : public Place
{
public:
	enum Type {
		CITY,
		VILLAGE,
		EMPTY
	};

	Location();
	~Location();
};

