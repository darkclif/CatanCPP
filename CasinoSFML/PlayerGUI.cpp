#include "PlayerGUI.h"
#include "Map.h"

PlayerGUI::PlayerGUI(sfg::SFGUI & _sfgui, sfg::Desktop & _desktop, Game * _game, Map * _map)
	: sfg_sfgui{ _sfgui }, sfg_desktop{ _desktop }, game{ _game }, map{ _map },
	mainMenuPanel(this),
	playerInfoPanel(_game->getCurrentPlayer()),
	resourcesPanel(_game->getCurrentPlayer())
{	
	setupGUI();
	UpdateGUI(sf::Time());
}

PlayerGUI::~PlayerGUI()
{
}

//
// Updates
//
void PlayerGUI::UpdateGUI( sf::Time _dt ) {
	if (game->getContentChange(Game::ContentChange::PLAYER_RESOURCE)) {
		resourcesPanel.Refresh();
	}
	if (game->getContentChange(Game::ContentChange::CURRENT_PLAYER)) {
		resourcesPanel.ChangePlayer(game->getCurrentPlayer());
	}

	if (game->getContentChange(Game::ContentChange::ROUND_TYPE)) {
		showRoundInfo();
	}

	mainMenuPanel.applyPendingMenuChanges();
}

void PlayerGUI::acceptSelection(SelectableMapItem * _item)
{
	bool selectionCorrect = true;
	Location* lLocation;

	switch (_item->getMode())
	{
		case SelectableMapItem::Mode::LOCATION:
			lLocation = static_cast<Location*>(_item);

			if ( lLocation->isNeighbourLocation()) {
				selectionCorrect = false;
				mainMenuPanel.ChangeBuildingMessage("You cannot build village one road away from another village!");
				break;
			}

			if (_item->getLocationSelectionMode() == SelectableMapItem::LocationSelectionMode::CITY) {
				if (lLocation->getOwner() != game->getCurrentPlayer()) {
					selectionCorrect = false;
					mainMenuPanel.ChangeBuildingMessage("You cannot upgrade your opponent village!");
					break;
				}
				
				requestCityBuild(static_cast<Location*>(_item));
			}
			
			if (_item->getLocationSelectionMode() == SelectableMapItem::LocationSelectionMode::VILLAGE)
				requestVillageBuild(static_cast<Location*>(_item));
		
			break;
		case SelectableMapItem::Mode::ROAD:
			requestRoadBuild(static_cast<Road*>(_item));
			break;
		case SelectableMapItem::Mode::TILE:
			// game->buildLocation(game->getCurrentPlayer(), static_cast<Location*>(_item));
			break;
		default:
			break;
	}

	// Pop prompt message 

	if (selectionCorrect) {
		mainMenuPanel.requestPopMenu();
		map->cancelSelection();
	}
}

bool PlayerGUI::isMouseOverGUI()
{
	return isMouseOver;
}

void PlayerGUI::resizeContent()
{
}

//
// Requests
//
void PlayerGUI::requestThrowDice()
{
	game->throwDices();
	mainMenuPanel.ShowDiceButton(false);
}

void PlayerGUI::requestNextRound()
{
	game->nextRound();

	playerInfoPanel.ChangePlayer(game->getCurrentPlayer());
	mainMenuPanel.ShowDiceButton(true);
}

void PlayerGUI::requestCityBuild(Location * _location)
{
	game->buildCity(game->getCurrentPlayer(), _location);
}

void PlayerGUI::requestVillageBuild(Location * _location)
{
	game->buildVillage(game->getCurrentPlayer(), _location);
}

void PlayerGUI::requestRoadBuild(Road * _road)
{
	game->buildRoad(game->getCurrentPlayer(), _road);
}

/* Map selections */
void PlayerGUI::requestCitySelection()
{
	if (game->getRoundType() & Game::RoundType::BEGINNING) {
		
	}
	else {/* RoundType::NORMAL */
		if (game->canPlayerAffordItem(Game::Item::CITY, game->getCurrentPlayer())) {
			map->requestSelection(Map::SelectionMode::SELECT_CITY, this);

			mainMenuPanel.ChangeBuildingMessage("Choose village for upgrading to city.");
			mainMenuPanel.requestPushMenu(MainMenuPanel::Menu::MENU_BUILDING_MESSAGE);
		}
		else {
			mainMenuPanel.requestPushInfo("Not enough resources to build city.", "OK");
		}
	}
}

void PlayerGUI::requestVillageSelection()
{	
	if (game->canPlayerAffordItem(Game::Item::VILLAGE, game->getCurrentPlayer())) {
		map->requestSelection(Map::SelectionMode::SELECT_VILLAGE, this);

		mainMenuPanel.ChangeBuildingMessage("Choose place to build village.");
		mainMenuPanel.requestPushMenu(MainMenuPanel::Menu::MENU_BUILDING_MESSAGE);
	}
	else {
		mainMenuPanel.requestPushInfo("Not enough resources to build village.", "OK");
	}
}

void PlayerGUI::requestRoadSelection()
{
	if (game->canPlayerAffordItem(Game::Item::ROAD, game->getCurrentPlayer())) {
		map->requestSelection(Map::SelectionMode::SELECT_ROAD, this);

		mainMenuPanel.ChangeBuildingMessage("Choose place to build road.");
		mainMenuPanel.requestPushMenu( MainMenuPanel::Menu::MENU_BUILDING_MESSAGE );
	}else {
		mainMenuPanel.requestPushInfo("Not enough resources to build road.","OK");
	}
}

void PlayerGUI::requestSelectionCancel()
{
	map->cancelSelection();
}

void PlayerGUI::showRoundInfo()
{
	Game::RoundType lRoundType = game->getRoundType();
	std::string lMessage = "";

	switch (lRoundType) {
		case Game::BEGINNING_FORWARD: 
			lMessage = "You must build one village and road baside this village for free. Then end the round.";
			break;
		case Game::BEGINNING_BACKWARD: 
			lMessage = "You must build one village and road baside this village for free, turns will go opposite. Then end the round.";
			break;
		case Game::NORMAL: 
			lMessage = "Throw dices and do some actions, then end the round.";
			break;
		default: break;
	}

	infoPanel.ChangeInfo(lMessage);
}

//
// Setup
//
void PlayerGUI::setupGUI()
{
	// Create window 
	mainWindow = sfg::Window::Create(sfg::Window::Style::BACKGROUND);
	mainWindow->SetTitle("Main menu");
	
	mainWindow->GetSignal(sfg::Window::OnMouseEnter).Connect(std::bind(&PlayerGUI::changeMouseOver, this, true));
	mainWindow->GetSignal(sfg::Window::OnMouseLeave).Connect(std::bind(&PlayerGUI::changeMouseOver, this, false));

	auto mainBox = sfg::Box::Create( sfg::Box::Orientation::VERTICAL, 10.f);
	
	/* Modules */
	mainBox->Pack(playerInfoPanel.getBox(), false);
	mainBox->Pack(sfg::Separator::Create());

	mainBox->Pack(infoPanel.getBox(), false);
	mainBox->Pack(sfg::Separator::Create());

	mainBox->Pack(resourcesPanel.getBox(), false);
	mainBox->Pack(sfg::Separator::Create());
	
	mainBox->Pack(mainMenuPanel.getBox(), false);
	/* END_Modules */

	mainWindow->Add( mainBox );
	mainWindow->SetAllocation(sf::FloatRect(0, 0, 200.f, 0));

	sfg_desktop.Add(mainWindow);
}

void PlayerGUI::changeMouseOver(bool _state)
{
	isMouseOver = _state;
}

//
// [MainMenuManager]
//
PlayerGUI::MainMenuPanel::MainMenuPanel(PlayerGUI * _playerGUI)
{
	this->playerGUI = _playerGUI;

	buildInterface();
	packMenusToBox();

	menuStack.push(Menu::MENU_MAIN);
	RefreshMenusVisibility();
}

void PlayerGUI::MainMenuPanel::applyPendingMenuChanges()
{
	if (pendingChanges.empty())
		return;
	
	for (auto change : pendingChanges ) {
		switch (change.action) {
			case PendingMenuChange::Action::POP:
				if (!menuStack.empty())
					menuStack.pop();
				break;
			case PendingMenuChange::Action::PUSH: 
				menuStack.push(change.menu);
				break;
			default: break;
		}
	}

	pendingChanges.clear();
	RefreshMenusVisibility();
}

void PlayerGUI::MainMenuPanel::ChangeBuildingMessage(std::string _message)
{
	labBuildingMessage->SetText(_message);
}

void PlayerGUI::MainMenuPanel::ShowDiceButton(bool _show)
{
	btnDiceThrow->Show(_show);
}

void PlayerGUI::MainMenuPanel::requestPushInfo(std::string _text, std::string _btnText)
{
	labMessage->SetText(_text);
	btnReturn = sfg::Button::Create(_btnText);

	requestPushMenu(Menu::MENU_MESSAGE);
}

void PlayerGUI::MainMenuPanel::requestPushMenu(Menu _menu)
{
	pendingChanges.push_back( PendingMenuChange( PendingMenuChange::Action::PUSH, _menu) );
}

void PlayerGUI::MainMenuPanel::requestPopMenu()
{
	pendingChanges.push_back(PendingMenuChange(PendingMenuChange::Action::POP));
}

void PlayerGUI::MainMenuPanel::buildInterface()
{
	menuStorage.insert(std::pair<Menu, sfg::Box::Ptr>(Menu::MENU_MAIN, createMenuMain()) );
	menuStorage.insert(std::pair<Menu, sfg::Box::Ptr>(Menu::MENU_BUILDING, createMenuBuilding()));
	menuStorage.insert(std::pair<Menu, sfg::Box::Ptr>(Menu::MENU_BUILDING_MESSAGE, createMenuBuildingMessage()));
	menuStorage.insert(std::pair<Menu, sfg::Box::Ptr>(Menu::MENU_MESSAGE, createMenuMessage()));
}

void PlayerGUI::MainMenuPanel::packMenusToBox()
{
	boxWrapper = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.f);

	for ( auto menu_it : menuStorage ) {
		boxWrapper->Pack(menu_it.second);
	}
}

void PlayerGUI::MainMenuPanel::RefreshMenusVisibility()
{
	for (auto menu_it : menuStorage ) {
		menu_it.second->Show(false);
	}

	if (!menuStack.empty()) {
		Menu menu = menuStack.top();
		sfg::Box::Ptr topMenu = menuStorage.at(menu);
		topMenu->Show(true);
	}
}

//
// [MainMenuManager] - MenuCreators
//
sfg::Box::Ptr PlayerGUI::MainMenuPanel::createMenuMain()
{
	// Buttons
	btnDiceThrow = sfg::Button::Create("Throw dices");
	btnDiceThrow->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&PlayerGUI::requestThrowDice, playerGUI));
	
	sfg::Button::Ptr btnBuild = sfg::Button::Create("Build");
	btnBuild->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&MainMenuPanel::requestPushMenu, this, Menu::MENU_BUILDING));

	sfg::Button::Ptr btnNextRound = sfg::Button::Create("End round");
	btnNextRound->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&PlayerGUI::requestNextRound, playerGUI));

	// Box
	sfg::Box::Ptr boxMenuMainAction = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
	boxMenuMainAction->Pack(btnDiceThrow, true);
	boxMenuMainAction->Pack(btnBuild, true);
	boxMenuMainAction->Pack(btnNextRound, true);

	boxMenuMainAction->SetId("playerInfo");

	return boxMenuMainAction;
}

sfg::Box::Ptr PlayerGUI::MainMenuPanel::createMenuBuilding()
{
	// Buttons
	sfg::Button::Ptr btnBuildRoad = sfg::Button::Create("Build road");
	btnBuildRoad->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&PlayerGUI::requestRoadSelection, playerGUI));

	sfg::Button::Ptr btnBuildVillage = sfg::Button::Create("Build village");
	btnBuildVillage->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&PlayerGUI::requestVillageSelection, playerGUI));
	
	sfg::Button::Ptr btnBuildCity = sfg::Button::Create("Build city");
	btnBuildCity->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&PlayerGUI::requestCitySelection, playerGUI));
	
	sfg::Button::Ptr btnBuildCancel = sfg::Button::Create("Cancel");	
	btnBuildCancel->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&MainMenuPanel::requestPopMenu, this));

	// Box
	sfg::Box::Ptr boxMenuMainBuild = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
	boxMenuMainBuild->Pack(btnBuildRoad, true);
	boxMenuMainBuild->Pack(btnBuildCity, true);
	boxMenuMainBuild->Pack(btnBuildVillage, true);
	boxMenuMainBuild->Pack(btnBuildCancel, true);

	return boxMenuMainBuild;
}

sfg::Box::Ptr PlayerGUI::MainMenuPanel::createMenuBuildingMessage()
{
	labBuildingMessage = sfg::Label::Create("[Info builing messege]");
	labBuildingMessage->SetLineWrap(true);
	labBuildingMessage->SetRequisition(sf::Vector2f(200.f, 0));
	
	sfg::Button::Ptr btnReturn = sfg::Button::Create("Cancel");
	btnReturn->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&PlayerGUI::requestSelectionCancel, playerGUI));
	btnReturn->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&MainMenuPanel::requestPopMenu, this));

	// Box
	sfg::Box::Ptr lBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
	lBox->Pack(labBuildingMessage,false);
	lBox->Pack(btnReturn, true);
	
	return lBox;
}

sfg::Box::Ptr PlayerGUI::MainMenuPanel::createMenuMessage()
{
	labMessage = sfg::Label::Create("[Info messege]");
	labMessage->SetLineWrap(true);
	labMessage->SetRequisition(sf::Vector2f(200.f,0));

	sfg::Button::Ptr btnReturn = sfg::Button::Create("OK");
	btnReturn->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&MainMenuPanel::requestPopMenu, this));

	// Box
	sfg::Box::Ptr lBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
	lBox->Pack(labMessage, false);
	lBox->Pack(btnReturn, true);

	return lBox;
}

//
// [PlayerInfoPanel]
//
void PlayerGUI::PlayerInfoPanel::ChangePlayer(Player * _player)
{
	player = _player;
	Refresh();
}

void PlayerGUI::PlayerInfoPanel::Refresh()
{
	// Change avatar 
	sf::Texture& tex = ResourceMgr.getTexture(player->getAvatarTexture());
	sf::Image lImage = tex.copyToImage();

	imgAvatar->SetImage(lImage);

	// Change name
	labPlayerName->SetText(player->getName());

	sfg::Context::Get().GetEngine().SetProperty("Label#playerName","Color",player->getColor());
	labPlayerName->SetId("playerName");
}

PlayerGUI::PlayerInfoPanel::PlayerInfoPanel(Player * _player) : player{ _player }
{
	buildInterface();
	Refresh();
}

void PlayerGUI::PlayerInfoPanel::buildInterface()
{
	// Widgets
	/* 1 row */
	sfg::Label::Ptr labTitle = sfg::Label::Create("Current player:");
	
	/* 2 row */
	imgAvatar = sfg::Image::Create();
	labPlayerName = sfg::Label::Create("[player_name]");

	sfg::Box::Ptr boxSecondRow = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 10.f);
	boxSecondRow->Pack(imgAvatar, false);
	boxSecondRow->Pack(labPlayerName, true);

	// Box
	boxWrapper = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.f);
	boxWrapper->Pack(labTitle);
	boxWrapper->Pack(boxSecondRow);
}

void PlayerGUI::InfoPanel::ChangeInfo(std::string _info)
{
	labInfo->SetText(_info);
}

//
// [InfoPanel]
//
PlayerGUI::InfoPanel::InfoPanel()
{
	buildInterface();
}

void PlayerGUI::InfoPanel::buildInterface()
{
	// Widgets
	labInfo = sfg::Label::Create("[Info]");
	labInfo->SetLineWrap(true);
	labInfo->SetRequisition(sf::Vector2f(200.f, 0));

	// Box
	boxWrapper = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.f);
	boxWrapper->Pack(labInfo);
}

sfg::Box::Ptr PlayerGUI::Panel::getBox()
{
	return boxWrapper;
}


//
// [ResourcesMenu]
//
void PlayerGUI::ResourcesPanel::ChangePlayer(Player * _player)
{
	player = _player;
	Refresh();
}

void PlayerGUI::ResourcesPanel::Refresh()
{
	ResourceBag lPlayerResources = player->getResources();

	for (int i = 0; i < Resource::_SIZE; i++) {
		labCountResources[i]->SetText(std::to_string(lPlayerResources[i]));
	}
}

PlayerGUI::ResourcesPanel::ResourcesPanel(Player * _player) : player{_player}
{
	buildInterface();
	Refresh();
}

void PlayerGUI::ResourcesPanel::buildInterface()
{
	std::vector<std::string> resourceNames = {
		"Wood",
		"Sheep",
		"Clay",
		"Iron",
		"Wheat"
	};

	labCountResources.resize(resourceNames.size());

	boxWrapper = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.f);

	for (int i = 0; i < (int)resourceNames.size(); i++) {
		auto boxSingleResource = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);

		auto labResName = sfg::Label::Create(resourceNames[i]);
		boxSingleResource->Pack(labResName);

		labCountResources[i] = sfg::Label::Create("0");
		boxSingleResource->Pack(labCountResources[i]);

		boxWrapper->Pack(boxSingleResource);
	}
}
