#pragma once
#include <string>

#include <SFML/Graphics.hpp>

#include "resources/Textures.h"

class Settings
{
public:
	/* Structs */
	struct PlayerConfig {
		std::string				name;
		sf::Color				color;
		Catan::Textures::Name	avatarTexture;
		
		PlayerConfig(std::string _name, sf::Color _color, Catan::Textures::Name _texName) {
			name = _name;
			color = _color;
			avatarTexture = _texName;
		};
	};

	/* SFGUI Styles set*/
	static const void setSfguiStyles();

	/* Settings storage*/
	static const std::vector<Settings::PlayerConfig> playersConfig;

private:
	Settings() = delete;
	~Settings() = delete;
};

