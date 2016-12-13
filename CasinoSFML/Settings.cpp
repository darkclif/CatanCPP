#include "Settings.h"
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

const std::vector<Settings::PlayerConfig> Settings::playersConfig = {
	PlayerConfig("Papjesz",sf::Color::Blue,Catan::Textures::AVATAR_1),
	PlayerConfig("Oleczka",sf::Color::Yellow,Catan::Textures::AVATAR_5),
	PlayerConfig("Chynia",sf::Color::Red,Catan::Textures::AVATAR_6),
	PlayerConfig("Maciej",sf::Color::Green,Catan::Textures::AVATAR_4)
};

#define SfgProp sfg::Context::Get().GetEngine()

void Settings::setSfguiStyles()
{
	// Template: sfg::Context::Get().GetEngine().SetProperty("Box#playerInfo", "BackgroundColor", sf::Color(0, 50, 120, 255));
	
	/* .title */
	SfgProp.SetProperty("Label.title", "FontSize", 15);
}
