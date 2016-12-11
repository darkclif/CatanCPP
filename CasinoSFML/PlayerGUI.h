#pragma once

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Console.h"
#include <stack>

class Map;

class PlayerGUI
{
public:
	PlayerGUI( sfg::SFGUI& _sfgui, sfg::Desktop& _desktop, Game* _game, Map* _map);
	~PlayerGUI();

	void				UpdateGUI( sf::Time _dt );

	void				acceptSelection(SelectableMapItem* _item);
	void				resizeContent();

private:
	/* Action senders to Game */
	void				requestThrowDice();
	void				requestNextRound();

	void				requestLocationBuild(Location*);
	void				requestRoadBuild(Road*);

	void				updatePlayerResource();

	/* Map selection request */
	void				requestLocationSelection();
	void				requestRoadSelection();

private:
	class MainMenuManager {
		public:
			enum Menu { /* Main menu states */
				MENU_MAIN,
				MENU_BUILDING,
				MENU_MESSAGE
			};

			struct PendingMenuChange {
				enum Action { POP, PUSH };

				Action		action;
				Menu		menu;

				PendingMenuChange(Action _action, Menu _menu) : action{ _action }, menu{ _menu } {}
				PendingMenuChange(Action _action ) : action{ _action }, menu{ /*not used*/ Menu::MENU_MESSAGE } {}
			};

			sfg::Box::Ptr	getBox();
			void			applyPendingMenuChanges();

			/* Actions to change menu elements */
			void ChangeMessage(std::string _message);
			void ShowDiceButton(bool _show);

			MainMenuManager(PlayerGUI* _playerGUI);

		private:
			void requestPushMenu( Menu _menu );
			void requestPopMenu();
			
			void createMenus();
			void packMenusToBox();
			
			void RefreshMenusVisibility();

			/* Menus creators */
			sfg::Box::Ptr createMenuMain();
			sfg::Box::Ptr createMenuBuilding();
			sfg::Box::Ptr createMenuMessage();

		private:
			sfg::Box::Ptr					boxWrapper;
			std::map<Menu, sfg::Box::Ptr>	menuStorage;

			std::stack<Menu>				menuStack;
			std::vector<PendingMenuChange>	pendingChanges;

			PlayerGUI* playerGUI;

			/* Elements which are changable */
			sfg::Label::Ptr		labMessage;
			sfg::Button::Ptr	btnDiceThrow;
	};
	
	class PlayerInfoPanel {
	public:
		sfg::Box::Ptr getBox();

		void ChangePlayer( Player* _player);
		void Refresh();

		PlayerInfoPanel( Player* _player);
	
	private:
		void buildInterface();

	private:
		Player* player;

		sfg::Box::Ptr boxWrapper;

		/* Elements which are changable */
		sfg::Label::Ptr		labPlayerName;
		sfg::Image::Ptr		imgAvatar;
	};

	/*** MAIN WINDOW ***/
	sfg::Window::Ptr	mainWindow;

	/* Curret player info panel */
	PlayerInfoPanel		playerInfoPanel;

	/* Menu resource */
	std::vector<sfg::Label::Ptr>	labCountResources;

	/* Menu main */
	MainMenuManager		mainMenuManager;

private:
	void				setupGUI();
	
	sfg::Box::Ptr		setupPlayerInfoPanel();
	sfg::Box::Ptr		setupResourcesMenu();
	sfg::Box::Ptr		setupMainMenu();
	
private:
	sfg::SFGUI&			sfg_sfgui;
	sfg::Desktop&		sfg_desktop;

	Game*				game;
	Map*				map;
};

