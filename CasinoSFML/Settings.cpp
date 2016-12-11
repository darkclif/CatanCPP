#include "Settings.h"
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

const std::vector<Settings::PlayerConfig> Settings::playersConfig = {
	PlayerConfig("Ignacy",sf::Color::Blue,Catan::Textures::AVATAR_1),
	PlayerConfig("Jan",sf::Color::Yellow,Catan::Textures::AVATAR_2),
	PlayerConfig("Karol",sf::Color::Red,Catan::Textures::AVATAR_3),
	PlayerConfig("Maciej",sf::Color::Green,Catan::Textures::AVATAR_4)
};

const void Settings::setSfguiStyles()
{
	// sfg::Context::Get().GetEngine().SetProperty("Box#playerInfo", "BackgroundColor", sf::Color(0, 50, 120, 255));

}
