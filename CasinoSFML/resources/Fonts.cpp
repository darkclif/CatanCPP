#include "Fonts.h"

#include <iostream>

namespace Catan {

	Fonts::Fonts()
	{
	}

	std::string Fonts::getPath(Name _name) {

		auto it = mPaths.find(_name);
		if (it == mPaths.end()) {
			std::string lError = "No given path for font";
			std::cout << lError << std::endl;
			throw std::logic_error(lError);
		}
		else {
			return it->second;
		}
	}

	Fonts::~Fonts()
	{
	}

	const std::map< Fonts::Name, std::string> Fonts::mPaths = {
		/* List below must contain all enums in Fonts::Name */
		/* Fonts */
		{ Fonts::DEFAULT,"fonts/roboto.ttf" }
	};
}