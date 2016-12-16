#include "Settings.h"
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

namespace Catan {

	const std::vector<Settings::PlayerConfig> Settings::playersConfig = {
		PlayerConfig("Papjesz",sf::Color::Blue,Textures::AVATAR_1),
		PlayerConfig("Oleczka",sf::Color::Yellow,Textures::AVATAR_5),
		PlayerConfig("Chynia",sf::Color::Red,Textures::AVATAR_6),
		PlayerConfig("Maciej",sf::Color::Green,Textures::AVATAR_4)
	};

#define SfgProp sfg::Context::Get().GetEngine()

	void Settings::setSfguiStyles()
	{
		// Template: sfg::Context::Get().GetEngine().SetProperty("Box#playerInfo", "BackgroundColor", sf::Color(0, 50, 120, 255));

		/* .title */
		SfgProp.SetProperty("Label.title", "FontSize", 15);
	}

}