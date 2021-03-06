#pragma once
#include <string>

#include <SFML/Graphics.hpp>

#include "resources/Textures.h"

namespace Catan {

	class Settings
	{
	public:
		/* Structs */
		struct PlayerConfig {
			std::string				name;
			sf::Color				color;
			Textures::Name	avatarTexture;

			PlayerConfig(std::string _name, sf::Color _color, Textures::Name _texName) {
				name = _name;
				color = _color;
				avatarTexture = _texName;
			};
		};

		/* SFGUI Styles set*/
		static void setSfguiStyles();

		/* Settings storage*/
		static const std::vector<Settings::PlayerConfig> playersConfig;

	private:
		Settings() = delete;
		~Settings() = delete;
	};

}