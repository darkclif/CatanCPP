#include "Settings.h"
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

const std::vector<Settings::PlayerConfig> Settings::playersConfig = {
	PlayerConfig("Papjesz",sf::Color::Blue,Catan::Textures::AVATAR_1),
	PlayerConfig("Oleczka",sf::Color::Yellow,Catan::Textures::AVATAR_5),
	PlayerConfig("Chynia",sf::Color::Red,Catan::Textures::AVATAR_6),
	PlayerConfig("Maciej",sf::Color::Green,Catan::Textures::AVATAR_4)
};

const void Settings::setSfguiStyles()
{
	// sfg::Context::Get().GetEngine().SetProperty("Box#playerInfo", "BackgroundColor", sf::Color(0, 50, 120, 255));

}
