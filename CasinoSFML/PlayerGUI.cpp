#include "PlayerGUI.h"
#include "Map.h"

PlayerGUI::PlayerGUI(sfg::SFGUI & _sfgui, sfg::Desktop & _desktop, Game * _game, Map * _map)
	: sfg_sfgui{ _sfgui }, sfg_desktop{ _desktop }, game{ _game }, map{ _map },
	mainMenuManager(this),
	playerInfoPanel(_game->getCurrentPlayer())
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
		updatePlayerResource();
	}
	if (game->getContentChange(Game::ContentChange::CURRENT_PLAYER)) {
		updatePlayerResource();
	}

	mainMenuManager.applyPendingMenuChanges();
}

void PlayerGUI::requestLocationBuild(Location * _location)
{
	game->buildLocation(game->getCurrentPlayer(), _location);
}

void PlayerGUI::requestRoadBuild(Road * _road)
{
	game->buildRoad(game->getCurrentPlayer(), _road);
}

void PlayerGUI::updatePlayerResource()
{
	ResourceBag lPlayerResources = game->getCurrentPlayer()->getResources();

	for (int i = 0; i < Resource::_SIZE; i++) {
		labCountResources[i]->SetText( std::to_string(lPlayerResources[i]) );
	}
}

void PlayerGUI::acceptSelection(SelectableMapItem * _item)
{
	switch (_item->getType())
	{
		case SelectableMapItem::Type::LOCATION:
			requestLocationBuild(static_cast<Location*>(_item));
			break;
		case SelectableMapItem::Type::ROAD:
			requestRoadBuild(static_cast<Road*>(_item));
			break;
		case SelectableMapItem::Type::TILE:
			// game->buildLocation(game->getCurrentPlayer(), static_cast<Location*>(_item));
			break;
		default:
			break;
	}
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
	mainMenuManager.ShowDiceButton(false);
}

void PlayerGUI::requestNextRound()
{
	game->nextRound();

	playerInfoPanel.ChangePlayer(game->getCurrentPlayer());
	mainMenuManager.ShowDiceButton(true);
}

void PlayerGUI::requestLocationSelection()
{
	map->getSelection(Map::SelectionMode::SELECT_LOCATION, this); 
}

void PlayerGUI::requestRoadSelection()
{
	map->getSelection(Map::SelectionMode::SELECT_ROAD, this);
}

//
// Setup
//
void PlayerGUI::setupGUI()
{
	// Create window 
	mainWindow = sfg::Window::Create(sfg::Window::Style::BACKGROUND);
	mainWindow->SetTitle("Main menu");
	
	auto mainBox = sfg::Box::Create( sfg::Box::Orientation::VERTICAL, 10.f);
	
	/* Modules */
	mainBox->Pack(setupPlayerInfoPanel(), false);
	mainBox->Pack(sfg::Separator::Create());

	mainBox->Pack(setupResourcesMenu(), false);
	mainBox->Pack(sfg::Separator::Create());
	
	mainBox->Pack(setupMainMenu(), false);
	/* END_Modules */

	mainWindow->Add( mainBox );
	mainWindow->SetAllocation(sf::FloatRect(0, 0, 200, 0));

	sfg_desktop.Add(mainWindow);
}

sfg::Box::Ptr PlayerGUI::setupMainMenu()
{
	return mainMenuManager.getBox();
}

sfg::Box::Ptr PlayerGUI::setupPlayerInfoPanel()
{
	return playerInfoPanel.getBox();
}

//
// [ResourcesMenu]
//
sfg::Box::Ptr PlayerGUI::setupResourcesMenu() {
	std::vector<std::string> resourceNames = {
		"Wood",
		"Sheep",
		"Clay",
		"Iron",
		"Wheat"
	};
	
	labCountResources.resize(resourceNames.size());

	auto boxResources = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.f);

	for (int i = 0; i < (int)resourceNames.size(); i++) {
		auto boxSingleResource = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);

		auto labResName = sfg::Label::Create(resourceNames[i]);
		labCountResources[i] = sfg::Label::Create("0");

		boxSingleResource->Pack(labResName);
		boxSingleResource->Pack(labCountResources[i]);

		boxResources->Pack(boxSingleResource);
	}
	
	return boxResources;
}

//
// [MainMenuManager]
//
PlayerGUI::MainMenuManager::MainMenuManager(PlayerGUI * _playerGUI)
{
	this->playerGUI = _playerGUI;

	createMenus();
	packMenusToBox();

	menuStack.push(Menu::MENU_MAIN);
	RefreshMenusVisibility();
}

sfg::Box::Ptr PlayerGUI::MainMenuManager::getBox()
{
	return boxWrapper;
}

void PlayerGUI::MainMenuManager::applyPendingMenuChanges()
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

void PlayerGUI::MainMenuManager::ChangeMessage(std::string _message)
{
	labMessage->SetText(_message);
}

void PlayerGUI::MainMenuManager::ShowDiceButton(bool _show)
{
	btnDiceThrow->Show(_show);
}

void PlayerGUI::MainMenuManager::requestPushMenu(Menu _menu)
{
	pendingChanges.push_back( PendingMenuChange( PendingMenuChange::Action::PUSH, _menu) );
}

void PlayerGUI::MainMenuManager::requestPopMenu()
{
	pendingChanges.push_back(PendingMenuChange(PendingMenuChange::Action::POP));
}

void PlayerGUI::MainMenuManager::createMenus()
{
	menuStorage.insert(std::pair<Menu, sfg::Box::Ptr>(Menu::MENU_MAIN, createMenuMain()) );
	menuStorage.insert(std::pair<Menu, sfg::Box::Ptr>(Menu::MENU_BUILDING, createMenuBuilding()));
	menuStorage.insert(std::pair<Menu, sfg::Box::Ptr>(Menu::MENU_MESSAGE, createMenuMessage()));
}

void PlayerGUI::MainMenuManager::packMenusToBox()
{
	boxWrapper = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.f);

	for ( auto menu_it : menuStorage ) {
		boxWrapper->Pack(menu_it.second);
	}
}

void PlayerGUI::MainMenuManager::RefreshMenusVisibility()
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
// MenuCreators
//
sfg::Box::Ptr PlayerGUI::MainMenuManager::createMenuMain()
{
	// Buttons
	btnDiceThrow = sfg::Button::Create("Throw dices");
	btnDiceThrow->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&PlayerGUI::requestThrowDice, playerGUI));
	
	sfg::Button::Ptr btnBuild = sfg::Button::Create("Build");
	btnBuild->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&MainMenuManager::requestPushMenu, this, Menu::MENU_BUILDING));

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

sfg::Box::Ptr PlayerGUI::MainMenuManager::createMenuBuilding()
{
	// Buttons
	sfg::Button::Ptr btnBuildRoad = sfg::Button::Create("Build road");
	btnBuildRoad->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&PlayerGUI::requestRoadSelection, playerGUI));

	sfg::Button::Ptr btnBuildLocation = sfg::Button::Create("Build location");
	btnBuildLocation->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&PlayerGUI::requestLocationSelection, playerGUI));

	sfg::Button::Ptr btnBuildCancel = sfg::Button::Create("Cancel");	
	btnBuildCancel->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&MainMenuManager::requestPopMenu, this));

	// Box
	sfg::Box::Ptr boxMenuMainBuild = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
	boxMenuMainBuild->Pack(btnBuildRoad, true);
	boxMenuMainBuild->Pack(btnBuildLocation, true);
	boxMenuMainBuild->Pack(btnBuildCancel, true);

	return boxMenuMainBuild;
}

sfg::Box::Ptr PlayerGUI::MainMenuManager::createMenuMessage()
{
	labMessage = sfg::Label::Create("[Info messege]");

	sfg::Button::Ptr btnReturn = sfg::Button::Create("Cancel");
	//btnReturn->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&MainMenuManager::requestPopMenu, this));

	// Box
	sfg::Box::Ptr lBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
	lBox->Pack(btnReturn, true);
	
	return lBox;
}

//
// [PlayerInfoPanel]
//
sfg::Box::Ptr PlayerGUI::PlayerInfoPanel::getBox()
{
	return boxWrapper;
}

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

PlayerGUI::PlayerInfoPanel::PlayerInfoPanel(Player * _player)
{
	buildInterface();

	player = _player;
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
