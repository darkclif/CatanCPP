#pragma once

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <SFML/Graphics.hpp>

class PlayerGUI
{
public:
	
	
	PlayerGUI( sfg::SFGUI& _sfgui, sfg::Desktop& _desktop);
	~PlayerGUI();
	


private:
	sfg::SFGUI& sfg_sfgui;
	sfg::Desktop& sfg_desktop;
};

