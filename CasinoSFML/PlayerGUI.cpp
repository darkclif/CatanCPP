#include "PlayerGUI.h"
#include "Map.h"
#include "Settings.h"
#include "Functions.h"

PlayerGUI::PlayerGUI(sfg::SFGUI & _sfgui, sfg::Desktop & _desktop, Game * _game, Map * _map)
	: sfg_sfgui{ _sfgui }, sfg_desktop{ _desktop }, game{ _game }, map{ _map },
	mainMenuPanel(this), playerInfoPanel(), resourcesPanel()
{	
	diceHolder = std::make_unique<DiceHolder>(sf::Vector2f(-800.f, 300.f),sf::Vector2f(-450.f, 100.f));

	setupGUI();
	UpdateGUI(sf::Time());

	mainMenuPanel.Refresh(game);
	playerInfoPanel.Refresh(game);
	resourcesPanel.Refresh(game);

	Settings::setSfguiStyles();
}

PlayerGUI::~PlayerGUI()
{
}

//
// Updates
//
void PlayerGUI::UpdateGUI( sf::Time _dt ) {
	if (game->getContentChange(Game::ContentChange::PLAYER_RESOURCE)) {
		resourcesPanel.Refresh(game);
		playerInfoPanel.Refresh(game);
	}

	if (game->getContentChange(Game::ContentChange::CURRENT_PLAYER)) {
		playerInfoPanel.Refresh(game);
		resourcesPanel.Refresh(game);
		infoPanel.Refresh(game);
	}

	if (game->getContentChange(Game::ContentChange::DICE_THROW)) {
		infoPanel.Refresh(game);

		diceHolder->setDices(game->getRoundInfo().dices[0], game->getRoundInfo().dices[1]);
		diceHolder->ResetAnimation();
	}

	if (game->getContentChange(Game::ContentChange::MENU_BUTTONS)) {
		mainMenuPanel.Refresh(game);
	}

	mainMenuPanel.Update();
	diceHolder->update(_dt);
}

void PlayerGUI::draw(sf::RenderWindow & _window)
{
	diceHolder->draw(_window);
}

void PlayerGUI::acceptSelection(SelectableMapItem * _item)
{
	bool selectionCorrect = true;
	
	switch (_item->getMode())
	{
		case SelectableMapItem::Mode::LOCATION:
			requestLocationBuild(static_cast<Location*>(_item));
			break;
		case SelectableMapItem::Mode::ROAD:
			requestRoadBuild(static_cast<Road*>(_item));
			break;
		case SelectableMapItem::Mode::TILE:
			requestThiefSet(static_cast<Tile*>(_item));
			break;
		default: break;
	}
}

bool PlayerGUI::isMouseOverGUI()
{
	return isMouseOver;
}

void PlayerGUI::resizeContent()
{
}

/* Requests to Game object */
void PlayerGUI::requestThrowDice()
{
	game->throwDices();
}

void PlayerGUI::requestNextRound()
{
	game->nextRound();
}

void PlayerGUI::requestLocationBuild(Location * _location)
{
	Player* lPlayer = game->getCurrentPlayer();
	Game::RoundType lRoundType = game->getRoundType();

	if (_location->isNeighbourLocation()) {
		mainMenuPanel.ChangeBuildingMessage("You cannot build village one road away from another village!");
		return;
	}

	if (_location->getLocationSelectionMode() == SelectableMapItem::LocationSelectionMode::CITY) {
		if (_location->getOwner() != game->getCurrentPlayer()) {
			mainMenuPanel.ChangeBuildingMessage("You cannot upgrade your opponent village!");
			return;
		}

		game->buildCity(game->getCurrentPlayer(), _location);
	}
	else {  /* LocationSelectionMode::VILLAGE */

		if (!(_location->isNearPlayerRoad(lPlayer)) && (lRoundType & Game::RoundType::NORMAL)) {
			mainMenuPanel.ChangeBuildingMessage("You can only build village beside one of your road!");
			return;
		}

		game->buildVillage(game->getCurrentPlayer(), _location);
	}

	mainMenuPanel.requestPopMenu();
	map->cancelSelection();
}

void PlayerGUI::requestRoadBuild(Road * _road)
{
	Player* lPlayer = game->getCurrentPlayer();

	if (!(_road->isBesidePlayerItem(lPlayer))) {
		mainMenuPanel.ChangeBuildingMessage("Road can only be placed next to player city, village or road!");
		return;
	}

	if (game->getRoundType() & Game::RoundType::BEGINNING_BACKWARD) {
		
		if (!(_road->isNeighbourWithLocation(lPlayer,Road::RoundType::BEGINNING_BACKWARD))) {
			mainMenuPanel.ChangeBuildingMessage("Road must be places beside village placed in this turn!");
			return;
		}
	}

	game->buildRoad(game->getCurrentPlayer(), _road);

	mainMenuPanel.requestPopMenu();
	map->cancelSelection();
}

void PlayerGUI::requestThiefSet(Tile * _tile)
{
	game->setThiefTile(game->getCurrentPlayer(), _tile);

	mainMenuPanel.requestPopMenu();
	map->cancelSelection();
}

/* Map selections */
void PlayerGUI::requestCitySelection()
{
	if (game->getRoundType() & Game::RoundType::BEGINNING)
		mainMenuPanel.requestPushInfo("In this phase you cannot build a city.");
	
	if (!(game->canPlayerAffordItem(Game::Item::CITY, game->getCurrentPlayer())))
		mainMenuPanel.requestPushInfo("Not enough resources to build city.");

	/* Succes */
	map->requestSelection(Map::SelectionMode::SELECT_CITY, this);

	mainMenuPanel.ChangeBuildingMessage("Choose village for upgrading to city.");
	mainMenuPanel.requestPushMenu(MainMenuPanel::Menu::MENU_BUILDING_MESSAGE);
}

void PlayerGUI::requestVillageSelection()
{	
	if (!(game->canPlayerAffordItem(Game::Item::VILLAGE, game->getCurrentPlayer()))) {
	
		mainMenuPanel.requestPushInfo("Not enough resources to build village.");
		return;
	}

	if (game->getCurrentPlayer()->getPhaseState(Player::Phase::BEGINNING_FORWARD).village
		&& (game->getRoundType() & Game::RoundType::BEGINNING_FORWARD)) {
		
		mainMenuPanel.requestPushInfo("You have already build one village in this phase.");
		return;
	}

	if (game->getCurrentPlayer()->getPhaseState(Player::Phase::BEGINNING_BACKWARD).village
		&& (game->getRoundType() & Game::RoundType::BEGINNING_BACKWARD)) {

		mainMenuPanel.requestPushInfo("You have already build one village in this phase.");
		return;
	}

	/* Succes */
	map->requestSelection(Map::SelectionMode::SELECT_VILLAGE, this);

	mainMenuPanel.ChangeBuildingMessage("Choose place to build village.");
	mainMenuPanel.requestPushMenu(MainMenuPanel::Menu::MENU_BUILDING_MESSAGE);
}

void PlayerGUI::requestRoadSelection()
{
	if (!(game->canPlayerAffordItem(Game::Item::ROAD, game->getCurrentPlayer()))) {

		mainMenuPanel.requestPushInfo("Not enough resources to build road.");
		return;
	}

	if (game->getCurrentPlayer()->getPhaseState(Player::Phase::BEGINNING_FORWARD).road
		&& (game->getRoundType() & Game::RoundType::BEGINNING_FORWARD)) {

		mainMenuPanel.requestPushInfo("You have already build one road in this phase.");
		return;
	}

	if (game->getCurrentPlayer()->getPhaseState(Player::Phase::BEGINNING_BACKWARD).road
		&& (game->getRoundType() & Game::RoundType::BEGINNING_BACKWARD)) {

		mainMenuPanel.requestPushInfo("You have already build one road in this phase.");
		return;
	}

	/* Succes */
	map->requestSelection(Map::SelectionMode::SELECT_ROAD, this);

	mainMenuPanel.ChangeBuildingMessage("Choose place to build road.");
	mainMenuPanel.requestPushMenu(MainMenuPanel::Menu::MENU_BUILDING_MESSAGE);
}

void PlayerGUI::requestTileSelection()
{
	if (!(game->getRoundInfo().isThiefAwaken)) {
		mainMenuPanel.requestPushInfo("You cannot place thief now.");
		return;
	}

	/* Succes */
	map->requestSelection(Map::SelectionMode::SELECT_TILE, this);

	mainMenuPanel.ChangeBuildingMessage("Choose tile to place a thief.");
	mainMenuPanel.requestPushMenu(MainMenuPanel::Menu::MENU_BUILDING_MESSAGE);
}

void PlayerGUI::requestSelectionCancel()
{
	map->cancelSelection();
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

///
/// PANELS AND MENUS
///

//
// [Panel]
//
sfg::Box::Ptr PlayerGUI::Panel::getBox()
{
	return boxWrapper;
}

void PlayerGUI::Panel::ShowAllWidgets()
{
	for (auto& lWidget : mapWidgets) {
		lWidget.second->Show(true);
	}
}

PlayerGUI::Panel::Panel()
{
}

//
// [MainMenuManager]
//
PlayerGUI::MainMenuPanel::MainMenuPanel(PlayerGUI * _playerGUI) : playerGUI{_playerGUI}
{
	buildInterface();

	menuStack.push(Menu::MENU_MAIN);
	RefreshMenusVisibility();
}

void PlayerGUI::MainMenuPanel::Refresh(Game * _game)
{
	ShowAllWidgets();

	Game::RoundInfo lRoundInfo = _game->getRoundInfo();
	Player* lPlayer = _game->getCurrentPlayer();

	if (!(lRoundInfo.isThiefAwaken))
		ShowWidget(Widget::SET_THIEF, false);

	if (lRoundInfo.roundType & Game::BEGINNING) {
		ShowWidget(Widget::THROW_DICES, false);
		ShowWidget(Widget::BUILD_CITY, false);


		if (lRoundInfo.roundType & Game::BEGINNING_FORWARD) {
			if (!(lPlayer->getPhaseState(Player::Phase::BEGINNING_FORWARD).Completed()))
				ShowWidget(Widget::END_ROUND, false);

		}
		else { /* Game::BEGINNING_BACKWARD */
			if (!(lPlayer->getPhaseState(Player::Phase::BEGINNING_BACKWARD).Completed()))
				ShowWidget(Widget::END_ROUND, false);

		}
	}
	else {/* Game::NORMAL */
		if (lRoundInfo.isThrowed)
			ShowWidget(Widget::THROW_DICES, false);
		else
			ShowWidget(Widget::END_ROUND, false);
	}
}

void PlayerGUI::MainMenuPanel::Update()
{
	applyPendingMenuChanges();
}

void PlayerGUI::MainMenuPanel::buildInterface()
{
	menuStorage.insert(std::pair<Menu, sfg::Box::Ptr>(Menu::MENU_MAIN, createMenuMain()));
	menuStorage.insert(std::pair<Menu, sfg::Box::Ptr>(Menu::MENU_BUILDING, createMenuBuilding()));
	menuStorage.insert(std::pair<Menu, sfg::Box::Ptr>(Menu::MENU_BUILDING_MESSAGE, createMenuBuildingMessage()));
	menuStorage.insert(std::pair<Menu, sfg::Box::Ptr>(Menu::MENU_INFO, createMenuMessage()));

	boxWrapper = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.f);

	for (auto menu_it : menuStorage) {
		boxWrapper->Pack(menu_it.second);
	}
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
	getWidget<Widget, sfg::Label>(Widget::BUILD_MESSAGE)->SetText(_message);
}

void PlayerGUI::MainMenuPanel::requestPushInfo(std::string _text)
{
	getWidget<Widget, sfg::Label>(Widget::INFO_MESSAGE)->SetText(_text);

	requestPushMenu(Menu::MENU_INFO);
}

void PlayerGUI::MainMenuPanel::requestPushMenu(Menu _menu)
{
	pendingChanges.push_back( PendingMenuChange( PendingMenuChange::Action::PUSH, _menu) );
}

void PlayerGUI::MainMenuPanel::requestPopMenu()
{
	pendingChanges.push_back(PendingMenuChange(PendingMenuChange::Action::POP));
}

void PlayerGUI::MainMenuPanel::RefreshMenusVisibility()
{
	for (auto lMenu : menuStorage ) {
		lMenu.second->Show(false);
	}

	if (!menuStack.empty()) {
		Menu menu = menuStack.top();
		sfg::Box::Ptr topMenu = menuStorage.at(menu);
		topMenu->Show(true);
	}
}

// [MainMenuManager] - MenuCreators
sfg::Box::Ptr PlayerGUI::MainMenuPanel::createMenuMain()
{
	// Buttons
	auto btnDiceThrow = sfg::Button::Create("Throw dices");
	btnDiceThrow->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&PlayerGUI::requestThrowDice, playerGUI));
	
	auto btnBuild = sfg::Button::Create("Build");
	btnBuild->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&MainMenuPanel::requestPushMenu, this, Menu::MENU_BUILDING));

	auto btnSetThief = sfg::Button::Create("Set thief");
	btnSetThief->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&PlayerGUI::requestTileSelection, playerGUI));

	auto btnNextRound = sfg::Button::Create("End round");
	btnNextRound->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&PlayerGUI::requestNextRound, playerGUI));

	mapWidgets.insert({ (int)Widget::THROW_DICES, btnDiceThrow });
	mapWidgets.insert({ (int)Widget::BUILD_MENU, btnBuild });
	mapWidgets.insert({ (int)Widget::SET_THIEF, btnSetThief});
	mapWidgets.insert({ (int)Widget::END_ROUND, btnNextRound });

	// Box
	sfg::Box::Ptr lBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
	lBox->Pack(btnDiceThrow, true);
	lBox->Pack(btnBuild, true);
	lBox->Pack(btnSetThief, true);
	lBox->Pack(btnNextRound, true);

	lBox->SetId("playerInfo");

	return lBox;
}

sfg::Box::Ptr PlayerGUI::MainMenuPanel::createMenuBuilding()
{
	// Widgets
	auto btnBuildRoad = sfg::Button::Create("Build road");
	btnBuildRoad->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&PlayerGUI::requestRoadSelection, playerGUI));

	auto btnBuildVillage = sfg::Button::Create("Build village");
	btnBuildVillage->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&PlayerGUI::requestVillageSelection, playerGUI));
	
	auto btnBuildCity = sfg::Button::Create("Build city");
	btnBuildCity->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&PlayerGUI::requestCitySelection, playerGUI));
	
	auto btnBuildCancel = sfg::Button::Create("Cancel");
	btnBuildCancel->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&MainMenuPanel::requestPopMenu, this));

	mapWidgets.insert({ (int)Widget::BUILD_ROAD, btnBuildRoad });
	mapWidgets.insert({ (int)Widget::BUILD_CITY, btnBuildCity});
	mapWidgets.insert({ (int)Widget::BUILD_VILLAGE, btnBuildVillage });

	// Box
	auto lBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
	lBox->Pack(btnBuildRoad, true);
	lBox->Pack(btnBuildCity, true);
	lBox->Pack(btnBuildVillage, true);
	lBox->Pack(btnBuildCancel, true);

	return lBox;
}

sfg::Box::Ptr PlayerGUI::MainMenuPanel::createMenuBuildingMessage()
{
	// Widgets
	auto labBuildingMessage = sfg::Label::Create("[Info builing messege]");
	labBuildingMessage->SetLineWrap(true);
	labBuildingMessage->SetRequisition(sf::Vector2f(200.f, 0));
	
	auto btnReturn = sfg::Button::Create("Cancel");
	btnReturn->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&PlayerGUI::requestSelectionCancel, playerGUI));
	btnReturn->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&MainMenuPanel::requestPopMenu, this));

	mapWidgets.insert({(int)Widget::BUILD_MESSAGE, labBuildingMessage});

	// Box
	sfg::Box::Ptr lBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
	lBox->Pack(labBuildingMessage,false);
	lBox->Pack(btnReturn, true);
	
	return lBox;
}

sfg::Box::Ptr PlayerGUI::MainMenuPanel::createMenuMessage()
{
	// Widgets
	auto labInfo = sfg::Label::Create("[Info messege]");
	labInfo->SetLineWrap(true);
	labInfo->SetRequisition(sf::Vector2f(200.f,0));

	auto btnReturn = sfg::Button::Create("OK");
	btnReturn->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&MainMenuPanel::requestPopMenu, this));

	mapWidgets.insert({(int)Widget::INFO_MESSAGE, labInfo});

	// Box
	auto lBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
	lBox->Pack(labInfo, false);
	lBox->Pack(btnReturn, true);

	return lBox;
}

//
// [PlayerInfoPanel]
//
PlayerGUI::PlayerInfoPanel::PlayerInfoPanel() : Panel()
{
	buildInterface();
}

void PlayerGUI::PlayerInfoPanel::Refresh(Game* _game)
{
	Player* lPlayer = _game->getCurrentPlayer();

	// Change avatar 
	sf::Texture& tex = ResourceMgr.getTexture(lPlayer->getAvatarTexture());
	sf::Image lImage = tex.copyToImage();

	getWidget<Widget, sfg::Image>(Widget::IMG_AVATAR)->SetImage(lImage);

	// Change name
	getWidget<Widget, sfg::Label>(Widget::LAB_NAME)->SetText(lPlayer->getName());

	sfg::Context::Get().GetEngine().SetProperty("Label#playerName","Color",lPlayer->getColor());
	getWidget<Widget, sfg::Label>(Widget::LAB_NAME)->SetId("playerName");

	// Change win points
	std::string stringWinPoints = "WP: " + std::to_string(lPlayer->getWinPoints());
	getWidget<Widget, sfg::Label>(Widget::LAB_WINPOINTS)->SetText(stringWinPoints);
}

void PlayerGUI::PlayerInfoPanel::buildInterface()
{
	// Widgets
	/* 1 row */
	sfg::Label::Ptr labTitle = sfg::Label::Create("Current player:");
	labTitle->SetClass("title");

	/* 2 row */
	auto imgAvatar = sfg::Image::Create();
	auto labPlayerName = sfg::Label::Create("[player_name]");

	auto boxSecondRow = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 10.f);
	boxSecondRow->Pack(imgAvatar, false);
	boxSecondRow->Pack(labPlayerName, true);

	/* 3 row */
	auto labWinPoints = sfg::Label::Create();

	mapWidgets.insert({ (int)Widget::IMG_AVATAR, imgAvatar });
	mapWidgets.insert({ (int)Widget::LAB_NAME, labPlayerName });
	mapWidgets.insert({ (int)Widget::LAB_WINPOINTS, labWinPoints });

	// Box
	boxWrapper = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.f);
	boxWrapper->Pack(labTitle);
	boxWrapper->Pack(boxSecondRow);
	boxWrapper->Pack(labWinPoints);
}

//
// [InfoPanel]
//
PlayerGUI::InfoPanel::InfoPanel() : Panel()
{
	buildInterface();	
}

void PlayerGUI::InfoPanel::Refresh(Game * _game)
{
	Game::RoundInfo lRoundInfo = _game->getRoundInfo();

	int lDice[2];
	lDice[0] = lRoundInfo.dices[0];
	lDice[1] = lRoundInfo.dices[1];

	Game::RoundType lRoundType = lRoundInfo.roundType;
	int lTurnNumber = lRoundInfo.roundNumber;

	// Turn number
	std::string lTurnNumberString = "Turn number: " + std::to_string(lTurnNumber);
	getWidget<InfoPanel::Widget, sfg::Label>(Widget::LABEL_TURN_NUMBER)->SetText(lTurnNumberString);

	// Dice 
	if (lRoundType & Game::RoundType::NORMAL) {
		std::string lPrefix = "Dice: ";
		std::string lDiceString = ""; 
		int lDiceSum = lDice[0] + lDice[1];

		if (lDiceSum > 1 && lDiceSum < 13)
			lDiceString = "[" + std::to_string(lDice[0]) + "]" +
					  "[" + std::to_string(lDice[1]) + "]" +
					  "=(" + std::to_string(lDiceSum) + ")";
		else 
			lDiceString = "-";

		getWidget<InfoPanel::Widget, sfg::Label>(Widget::LABEL_DICE)->SetText(lPrefix + lDiceString);
		ShowWidget<InfoPanel::Widget>(Widget::LABEL_DICE);
	}
	else {
		ShowWidget<InfoPanel::Widget>(Widget::LABEL_DICE, false);
	}

	std::string lInfo = "";

	// Info
	switch (lRoundType) {
	case Game::BEGINNING_FORWARD:
		lInfo = "You must build one village and road baside this village for free. Then end the round.";
		break;
	case Game::BEGINNING_BACKWARD:
		lInfo = "You must build one village and road baside this village for free, turns will go opposite. Then end the round.";
		break;
	case Game::NORMAL:
		lInfo = "Throw dices and do some actions, then end the round.";
		break;
	default: break;
	}

	getWidget<InfoPanel::Widget, sfg::Label>(Widget::LABEL_INFO)->SetText(lInfo);
}

void PlayerGUI::InfoPanel::buildInterface()
{
	// Widgets
	auto labTitle = sfg::Label::Create("Current turn:");
	labTitle->SetClass("title");
	
	auto labTurnNumber = sfg::Label::Create();
	auto labDiceSum = sfg::Label::Create();

	auto labInfo = sfg::Label::Create("[Info]");
	labInfo->SetLineWrap(true);
	labInfo->SetRequisition(sf::Vector2f(200.f, 0));

	mapWidgets.insert({ (int)Widget::LABEL_TILE, labTitle });
	mapWidgets.insert({ (int)Widget::LABEL_TURN_NUMBER, labTurnNumber });
	mapWidgets.insert({ (int)Widget::LABEL_DICE, labDiceSum });
	mapWidgets.insert({ (int)Widget::LABEL_INFO, labInfo });

	// Box
	boxWrapper = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.f);
	boxWrapper->Pack(labTitle);
	boxWrapper->Pack(labTurnNumber);
	boxWrapper->Pack(labDiceSum);
	
	boxWrapper->Pack(sfg::Separator::Create());
	boxWrapper->Pack(labInfo);
}

//
// [ResourcesMenu]
//
PlayerGUI::ResourcesPanel::ResourcesPanel() : Panel()
{
	buildInterface();
}

void PlayerGUI::ResourcesPanel::Refresh(Game* _game)
{
	Player* lPlayer = _game->getCurrentPlayer();
	ResourceBag lPlayerResources = lPlayer->getResources();

	/* Resources */
	for (int i = 0; i < Resource::_SIZE; i++) {
		labCountResources[i]->SetText(std::to_string(lPlayerResources[i]));
	}

	/* Units */
	std::string numVillage = std::to_string(lPlayer->getItem(Player::Item::VILLAGE));
	std::string numCity = std::to_string(lPlayer->getItem(Player::Item::CITY));
	std::string numRoad = std::to_string(lPlayer->getItem(Player::Item::ROAD));

	getWidget<Widget, sfg::Label>(Widget::LAB_VILLAGE)->SetText("Villages: " + numVillage + "/5");
	getWidget<Widget, sfg::Label>(Widget::LAB_CITY)->SetText("Cities: " + numCity + "/4");
	getWidget<Widget, sfg::Label>(Widget::LAB_ROAD)->SetText("Roads: " + numRoad + "/15");
}

void PlayerGUI::ResourcesPanel::buildInterface()
{
	boxWrapper = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.f);
	
	// Notebook 
	auto nbkNotebook = sfg::Notebook::Create();

	nbkNotebook->AppendPage(buildPageResources(), sfg::Label::Create("Resources"));
	nbkNotebook->AppendPage(buildPageCosts(), sfg::Label::Create("Costs"));
	nbkNotebook->AppendPage(buildPageUnits(), sfg::Label::Create("Units"));

	boxWrapper->Pack(nbkNotebook);
}

sfg::Box::Ptr PlayerGUI::ResourcesPanel::buildPageResources()
{
	auto lBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 2.f);
	
	std::vector<std::string> names = { "Wood","Sheep","Clay","Iron","Wheat" };

	std::vector<Catan::Textures::Name> textureNames = {
		Catan::Textures::ICON_WOOD,
		Catan::Textures::ICON_SHEEP,
		Catan::Textures::ICON_CLAY,
		Catan::Textures::ICON_IRON,
		Catan::Textures::ICON_WHEAT
	};

	labCountResources.resize(names.size());

	for (int i = 0; i < (int)names.size(); i++) {
		auto boxSingleResource = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);

		// Icon
		sf::Image tmpIconImage(ResourceMgr.getTexture(textureNames[i]).copyToImage());
		auto imgIcon = sfg::Image::Create(tmpIconImage);

		// Name
		auto labResName = sfg::Label::Create(names[i]);

		// Number
		labCountResources[i] = sfg::Label::Create("0");

		/* Pack */
		boxSingleResource->Pack(imgIcon);
		boxSingleResource->Pack(labResName);
		boxSingleResource->Pack(labCountResources[i]);

		lBox->Pack(boxSingleResource);
	}

	return lBox;
}

sfg::Box::Ptr PlayerGUI::ResourcesPanel::buildPageCosts()
{
	auto lBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 2.f);

	std::vector<std::string> costNames = {"Road","Village","City","Dev card"};

	std::vector<std::vector<Catan::Textures::Name>> costResourceList = {
		{Catan::Textures::ICON_WOOD, Catan::Textures::ICON_CLAY },
		{Catan::Textures::ICON_WOOD, Catan::Textures::ICON_CLAY,  Catan::Textures::ICON_WHEAT, Catan::Textures::ICON_SHEEP },
		{Catan::Textures::ICON_WHEAT, Catan::Textures::ICON_WHEAT, Catan::Textures::ICON_IRON, Catan::Textures::ICON_IRON, Catan::Textures::ICON_IRON },
		{Catan::Textures::ICON_WHEAT, Catan::Textures::ICON_SHEEP, Catan::Textures::ICON_IRON }
	};

	for (sf::Uint32 i = 0; i < costNames.size(); i++ ) {
		auto lResBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 2.f);
		
		auto labName = sfg::Label::Create(costNames[i]);
		labName->SetAlignment(sf::Vector2f(0,0));
		lResBox->Pack(labName, true);

		for ( auto& lRes : costResourceList[i]) {
			auto imgResource = sfg::Image::Create(ResourceMgr.getTexture(lRes).copyToImage());
			lResBox->Pack(imgResource, false);
		}

		lBox->Pack(lResBox);
	}

	return lBox;
}

sfg::Box::Ptr PlayerGUI::ResourcesPanel::buildPageUnits()
{
	auto lBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 2.f);

	std::vector<std::pair<Catan::Textures::Name, Widget>> textureNames = {
		{ Catan::Textures::ICON_VILLAGE, Widget::LAB_VILLAGE },
		{ Catan::Textures::ICON_CITY, Widget::LAB_CITY },
		{ Catan::Textures::ICON_ROAD, Widget::LAB_ROAD }
	};

	for (auto& lUnit : textureNames) {
		auto lBoxRow = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 2.f);

		auto imgUnit = sfg::Image::Create(ResourceMgr.getTexture(lUnit.first).copyToImage());
		lBoxRow->Pack(imgUnit, false);

		auto labText = sfg::Label::Create("[Status text]");
		mapWidgets.insert({ (int)lUnit.second, labText });
		lBoxRow->Pack(labText, false);

		lBox->Pack(lBoxRow);
	}

	return lBox;
}

sfg::Box::Ptr PlayerGUI::ResourcesPanel::buildPageCards()
{
	auto lBox = sfg::Box::Create();
	

	
	return lBox;
}

/* Dices */
void PlayerGUI::DiceHolder::draw(sf::RenderWindow & _window)
{
	for (auto& lDice : arrDices) {
		lDice->draw(_window);
	}
}

void PlayerGUI::DiceHolder::update(sf::Time _dt)
{
	time += _dt;

	if ( time < ANIMATION_TIME) {
		/* Update postion */

		float step = time / ANIMATION_TIME;
		sf::Vector2f result = startPos + step * (endPos - startPos);

		setPosition(result);
		
		for(auto& lDice : arrDices )
			lDice->setRotation(lDice->getRotation() + 400.f * step);
	}
}

void PlayerGUI::DiceHolder::setDices(int _d1, int _d2)
{
	arrDices[0]->setNumber(_d1);
	arrDices[1]->setNumber(_d2);
}

void PlayerGUI::DiceHolder::ResetAnimation()
{
	time = sf::seconds(0.f);
}

PlayerGUI::DiceHolder::DiceHolder(sf::Vector2f _start_pos, sf::Vector2f _end_pos): DrawableEntity(_start_pos, 0.f, nullptr)
{
	startPos = _start_pos;
	endPos = _end_pos;

	arrDices.push_back(std::make_unique<Dice>(sf::Vector2f(-100,-100), 1, this));
	arrDices.push_back(std::make_unique<Dice>(sf::Vector2f(100,100), 1, this));
}

sf::Texture & PlayerGUI::DiceHolder::getTexture()
{
	return ResourceMgr.getTexture(Catan::Textures::TEXTURE_EMPTY);
}

void PlayerGUI::DiceHolder::Dice::draw(sf::RenderWindow & _window)
{
	if (number < 1 || number > 6)
		return;

	sf::Sprite tmpSprite(getSprite());
	tmpSprite.setTexture(getTexture());
	tmpSprite.setPosition(getAbsolutePosition());

	tmpSprite.setTextureRect(sf::IntRect(TEXTURE_SIZE*(number - 1),0, TEXTURE_SIZE, TEXTURE_SIZE));

	_window.draw(tmpSprite);
}

/* Single dice */
int PlayerGUI::DiceHolder::Dice::getNumber()
{
	return number;
}

void PlayerGUI::DiceHolder::Dice::setNumber(int _number)
{
	number = _number;
}

PlayerGUI::DiceHolder::Dice::Dice(sf::Vector2f _pos, int _number, DrawableEntity* _parent) : 
	DrawableEntity(_pos,0.f,_parent), number{_number}
{
	setTexture(getTexture());
	setTextureRect(sf::IntRect(0,0, TEXTURE_SIZE, TEXTURE_SIZE));
	setOriginAtCenter();
}

sf::Texture & PlayerGUI::DiceHolder::Dice::getTexture()
{
	return ResourceMgr.getTexture(Catan::Textures::DICES);
}
