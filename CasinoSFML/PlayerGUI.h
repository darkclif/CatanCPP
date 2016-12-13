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
	void		requestThiefSet(Tile*);

	/* Map selection request */
	void		requestVillageSelection();
	void		requestCitySelection();
	void		requestRoadSelection();
	void		requestTileSelection();

	void		requestSelectionCancel();

private:
	class Panel {
	public:
		sfg::Box::Ptr	getBox();
		virtual void	Refresh(Game*) = 0;

		// Show Widget with enum
		template<typename W>
		void ShowWidget(W _widget, bool show = true) {
			if (mapWidgets.find((int)_widget) == mapWidgets.end()) {
				Console::debug << "Given Widget does not exist in panel." << std::endl;
				return;
			}
			
			mapWidgets.at((int)_widget)->Show(show);
		}

		// Return Widget with enum and cast to Type
		template<typename W, typename Type>
		std::shared_ptr<Type> getWidget(W _widget) {
			if (mapWidgets.find((int)_widget) == mapWidgets.end()) {
				Console::debug << "Given Widget does not exist in panel." << std::endl;
				return nullptr;
			}

			return std::static_pointer_cast<Type>( mapWidgets.at((int)_widget) );
		}

		void ShowAllWidgets();

		Panel();

	protected:
		virtual void buildInterface() = 0;

		sfg::Box::Ptr boxWrapper;

		/* Elements which are changable */
		std::map<int, sfg::Widget::Ptr>	mapWidgets;
	};

	class MainMenuPanel : public Panel{
		public:
			enum class Widget : int {
				/* MENU_MAIN */
				THROW_DICES,
				BUILD_MENU,
				SET_THIEF,
				END_ROUND,

				/* MENU_BUILDING */
				BUILD_ROAD,
				BUILD_CITY,
				BUILD_VILLAGE,

				/* MENU_BUILDING_MESSAGE */
				BUILD_MESSAGE,

				/* MENU_MESSAGE */
				INFO_MESSAGE
			};

			/* Menu navigation stack */
			enum class Menu { /* Main menu states */
				MENU_MAIN,
				MENU_BUILDING,
				MENU_BUILDING_MESSAGE,
				MENU_INFO,
				_SIZE
			};

			struct PendingMenuChange {
				enum Action { POP, PUSH };

				Action		action;
				Menu		menu;

				PendingMenuChange(Action _action, Menu _menu) : action{ _action }, menu{ _menu } {}
				PendingMenuChange(Action _action ) : action{ _action }, menu{ /*not used*/ Menu::_SIZE } {}
			};
			/* END_Menu navigation stack */

			/* Actions to change menu elements */
			void ChangeBuildingMessage(std::string _message);

			void requestPushInfo(std::string _text);
			void requestPushMenu(Menu _menu);
			void requestPopMenu();

			void Refresh(Game* _game);
			void Update();

			MainMenuPanel(PlayerGUI* _playerGUI);

		private:
			void buildInterface();
			
			void applyPendingMenuChanges();
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
	};
	
	class PlayerInfoPanel: public Panel {
	public:
		enum class Widget : int{
			IMG_AVATAR,
			LAB_NAME
		};

		void Refresh(Game* _game);

		PlayerInfoPanel();
	
	private:
		void buildInterface();
	};

	class InfoPanel: public Panel {
	public:
		enum class Widget {
			LABEL_TILE,
			LABEL_TURN_NUMBER,
			LABEL_DICE,
			LABEL_INFO
		};

		void	Refresh(Game* _game);

		InfoPanel();

	private:
		void buildInterface();
	};

	class ResourcesPanel : public Panel {
	public:
		void Refresh(Game* _game);

		template<typename W>
		void ShowWidget(W _widget, bool _show = true) = delete;
		void ShowAllWidgets() = delete;

		ResourcesPanel();

	private:
		void buildInterface();

		sfg::Box::Ptr buildPageResources();
		sfg::Box::Ptr buildPageCosts();

		/* Elements which are changable */
		std::vector<sfg::Label::Ptr>	labCountResources;
	};

	/*** MAIN WINDOW ***/
	sfg::Window::Ptr	mainWindow;

	PlayerInfoPanel		playerInfoPanel;
	InfoPanel			infoPanel;
	ResourcesPanel		resourcesPanel;
	MainMenuPanel		mainMenuPanel;

private:
	void				setupGUI();

	void				changeMouseOver(bool _state);

private:
	sfg::SFGUI&			sfg_sfgui;
	sfg::Desktop&		sfg_desktop;

	Game*				game;
	Map*				map;

	bool				isMouseOver;
};

