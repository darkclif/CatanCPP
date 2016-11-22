#pragma once
#include <string>

#include <SFML/Graphics.hpp>

#include "resources/Textures.h"

class Settings
{
public:
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

	//
	// Settings
	//

	static const std::vector<Settings::PlayerConfig> playersConfig;
private:
	Settings() = delete;
	~Settings() = delete;
};

