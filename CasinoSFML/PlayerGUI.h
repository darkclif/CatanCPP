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

	void		UpdateGUI( sf::Time _dt );

	void		acceptSelection(SelectableMapItem* _item);

	bool		isMouseOverGUI();
	void		resizeContent();

private:
	/* Action senders to Game */
	void		requestThrowDice();
	void		requestNextRound();

	void		requestLocationBuild(Location*);
	void		requestRoadBuild(Road*);

	/* Map selection request */
	void		requestVillageSelection();
	void		requestCitySelection();
	void		requestRoadSelection();

	void		requestSelectionCancel();

private:
	class Panel {
	public:
		sfg::Box::Ptr getBox();
	
	protected:
		virtual void buildInterface() = 0;

		sfg::Box::Ptr boxWrapper;
	};

	class MainMenuPanel : public Panel{
		public:
			/* Structs */
			enum Menu { /* Main menu states */
				MENU_MAIN,
				MENU_BUILDING,
				MENU_BUILDING_MESSAGE,
				MENU_MESSAGE,
				_SIZE
			};

			enum class Button : int {
				/* MENU_MAIN */
				THROW_DICES,
				BUILD_MENU,
				END_ROUND,

				/* MENU_BUILDING */
				BUILD_ROAD,
				BUILD_CITY,
				BUILD_VILLAGE,
			};

			struct PendingMenuChange {
				enum Action { POP, PUSH };

				Action		action;
				Menu		menu;

				PendingMenuChange(Action _action, Menu _menu) : action{ _action }, menu{ _menu } {}
				PendingMenuChange(Action _action ) : action{ _action }, menu{ /*not used*/ Menu::_SIZE } {}
			};
			/* END_Structs */

			void			applyPendingMenuChanges();

			/* Actions to change menu elements */
			void ChangeBuildingMessage(std::string _message);

			void ShowButton(Button _button, bool _show = true);
			void ShowAllButtons();

			void requestPushInfo(std::string _text, std::string _btnText);
			void requestPushMenu(Menu _menu);
			void requestPopMenu();

			MainMenuPanel(PlayerGUI* _playerGUI);

		private:
			void buildInterface();
			void packMenusToBox();
			
			void RefreshMenusVisibility();

			/* Menus creators */
			sfg::Box::Ptr createMenuMain();
			sfg::Box::Ptr createMenuBuilding();
			sfg::Box::Ptr createMenuBuildingMessage();
			sfg::Box::Ptr createMenuMessage();

		private:
			std::map<Menu, sfg::Box::Ptr>	menuStorage;

			std::stack<Menu>				menuStack;
			std::vector<PendingMenuChange>	pendingChanges;

			PlayerGUI* playerGUI;

			/* Elements which are changable */
			std::map<Button,sfg::Button::Ptr>	mapButtons;
			
			sfg::Label::Ptr		labBuildingMessage;
			
			sfg::Label::Ptr		labMessage;
			sfg::Button::Ptr	btnReturn;
	};
	
	class PlayerInfoPanel: public Panel {
	public:
		void ChangePlayer( Player* _player);
		void Refresh();

		PlayerInfoPanel( Player* _player);
	
	private:
		void buildInterface();

	private:
		Player* player;

		/* Elements which are changable */
		sfg::Label::Ptr		labPlayerName;
		sfg::Image::Ptr		imgAvatar;
	};

	class InfoPanel: public Panel {
	public:
		void		ChangeInfo(std::string _info);
		inline void ClearInfo() { ChangeInfo(""); };

		InfoPanel();

	private:
		void buildInterface();

	private:
		/* Elements which are changable */
		sfg::Label::Ptr		labInfo;
	};

	class ResourcesPanel : public Panel {
	public:
		void ChangePlayer(Player* _player);
		void Refresh();

		ResourcesPanel(Player* _player);

	private:
		void buildInterface();

		Player* player;

		/* Elements which are changable */
		std::vector<sfg::Label::Ptr>	labCountResources;
	};

	/*** MAIN WINDOW ***/
	sfg::Window::Ptr	mainWindow;

	PlayerInfoPanel		playerInfoPanel;
	InfoPanel			infoPanel;
	ResourcesPanel		resourcesPanel;
	MainMenuPanel		mainMenuPanel;

	void				showRoundInfo();
private:
	void				setupGUI();

	void				refreshMenuButtons();
	void				changeMouseOver(bool _state);

private:
	sfg::SFGUI&			sfg_sfgui;
	sfg::Desktop&		sfg_desktop;

	Game*				game;
	Map*				map;

	bool				isMouseOver;
};

