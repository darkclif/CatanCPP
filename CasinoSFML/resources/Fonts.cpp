#include "Fonts.h"

#include <iostream>
#include "../Console.h"

namespace Catan {

	Fonts::Fonts()
	{
	}

	Fonts::~Fonts()
	{
	}


	std::string Fonts::getPath(Name _name) {

		auto it = mPaths.find(_name);
		if (it == mPaths.end()) {
			std::string lError = "Path to font not assigned to given font name";
			Console::debug << lError << std::endl;
			throw std::logic_error(lError);
		}
		else {
			return it->second;
		}
	}


	const std::map< Fonts::Name, std::string> Fonts::mPaths = {
		/* List below must contain all enums in Fonts::Name */
		/* Fonts */
		{ Fonts::DEFAULT,"fonts/roboto.ttf" }
	};
}