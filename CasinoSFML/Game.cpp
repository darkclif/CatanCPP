#include "Game.h"
#include "Settings.h"
#include "Console.h"

namespace Catan {

	const std::map<Item, ResourceBag> Game::buildingsCosts = {
		std::make_pair<Item, ResourceBag>(Item::ROAD, ResourceBag(1,0,1,0,0)),
		std::make_pair<Item, ResourceBag>(Item::VILLAGE, ResourceBag(1,1,1,0,1)),
		std::make_pair<Item, ResourceBag>(Item::CITY, ResourceBag(0,0,0,3,2))
	};

	bool Game::canPlayerAffordItem(Item _item, Player * _player)
	{
		ResourceBag lItemCost = buildingsCosts.at(_item);

		if (lItemCost <= _player->getResources())
			return true;
		else
			return false;
	}

	Game::Game(int _players, Map* _map) : gameMap{ _map }, numPlayers{ _players }, contentChanges{ ContentChange::ALL }
	{
		if (_players < 2 || _players > 4) {
			std::string lError = "Wrong number of players";
			Console::debug << lError << std::endl;
			throw std::logic_error(lError);
		}

		for (int i = 0; i < _players; i++) {
			arrPlayers.push_back(
				Player(
					Settings::playersConfig[i].name,
					Settings::playersConfig[i].color,
					Settings::playersConfig[i].avatarTexture
					)
				);
		}

		roundInfo = RoundInfo();
		numCurrentPlayer = 0;

		/*TEST*/
		int a = 100;
		for (auto& lPlayer : arrPlayers) {
			lPlayer.giveResources(ResourceBag(a, a, a, a, a));
		}

		//setRoundType(Game::RoundType::NORMAL);
		/*END_TEST*/
	}


	Game::~Game()
	{
	}

	//
	// Game managment
	//
	Player * Game::getCurrentPlayer()
	{
		return &(arrPlayers[numCurrentPlayer]);
	}

	int Game::getDiceSum() {
		return roundInfo.dices[0] + roundInfo.dices[1];
	}

	bool Game::buildVillage(Player * _player, Location * _location)
	{
		if (_location->hasOwner())
			return false;

		if (getRoundType() == RoundType::BEGINNING_FORWARD) {
			if (_location->isNeighbourLocation())
				return false;

			if (_player->getPhaseState(RoundType::BEGINNING_FORWARD).village)
				return false;

			_location->Build(Location::Type::VILLAGE, _player, Location::RoundType::BEGINNING_FORWARD);
			_player->setPhaseState(RoundType::BEGINNING_FORWARD, Item::VILLAGE);
		}
		else if (getRoundType() == RoundType::BEGINNING_BACKWARD) {
			if (_location->isNeighbourLocation())
				return false;

			if (_player->getPhaseState(RoundType::BEGINNING_BACKWARD).village)
				return false;

			_location->Build(Location::Type::VILLAGE, _player, Location::RoundType::BEGINNING_BACKWARD);
			_player->setPhaseState(RoundType::BEGINNING_BACKWARD, Item::VILLAGE);
		}
		else { /* NORMAL ROUND */
			if (!canPlayerAffordItem(Item::VILLAGE, _player))
				return false;

			if (_location->isNeighbourLocation())
				return false;

			if (!(_location->isNearPlayerRoad(_player)))
				return false;

			if (_player->getItem(Item::VILLAGE) <= 0)
				return false;

			_player->takeResources(buildingsCosts.at(Item::VILLAGE));
			_location->Build(Location::Type::VILLAGE, _player);
		}

		_player->takeItem(Item::VILLAGE, 1);
		addContentChange(ContentChange::PLAYER_RESOURCE | ContentChange::MENU_BUTTONS);
		return true;
	}

	bool Game::buildCity(Player * _player, Location * _location)
	{
		if (getRoundType() == RoundType::NORMAL) {
			if (!(_location->getType() == Location::Type::VILLAGE))
				return false;

			if (!(canPlayerAffordItem(Item::CITY, _player)))
				return false;

			if (_player->getItem(Item::CITY) <= 0)
				return false;

			_player->takeResources(buildingsCosts.at(Item::CITY));
			_location->Build(Location::Type::CITY, _player);
		}
		else {
			return false;
		}

		_player->takeItem(Item::CITY, 1);
		_player->giveItem(Item::VILLAGE, 1);
		addContentChange(ContentChange::PLAYER_RESOURCE | ContentChange::MENU_BUTTONS);
		return true;
	}

	bool Game::buildRoad(Player * _player, Road * _road)
	{
		if (_road->hasOwner())
			return false;

		if (getRoundType() == RoundType::BEGINNING_FORWARD) {
			if (!(_road->isNeighbourWithLocation(_player, Road::RoundType::BEGINNING_FORWARD)))
				return false;

			if (_player->getPhaseState(RoundType::BEGINNING_FORWARD).road)
				return false;

			_road->setOwner(_player);
			_player->setPhaseState(RoundType::BEGINNING_FORWARD, Item::ROAD);
		}
		else if (getRoundType() == RoundType::BEGINNING_BACKWARD) {
			if (!(_road->isNeighbourWithLocation(_player, Road::RoundType::BEGINNING_BACKWARD)))
				return false;

			if (_player->getPhaseState(RoundType::BEGINNING_BACKWARD).road)
				return false;

			_road->setOwner(_player);
			_player->setPhaseState(RoundType::BEGINNING_BACKWARD, Item::ROAD);
		}
		else { /* NORMAL ROUND */
			if (!(canPlayerAffordItem(Item::ROAD, _player)))
				return false;

			if (!(_road->isBesidePlayerItem(_player)))
				return false;

			if (_player->getItem(Item::ROAD) <= 0)
				return false;

			_player->takeResources(buildingsCosts.at(Item::ROAD));
			_road->setOwner(_player);
		}

		_player->takeItem(Item::ROAD, 1);
		addContentChange(ContentChange::PLAYER_RESOURCE | ContentChange::MENU_BUTTONS);
		return true;
	}

	bool Game::setThiefTile(Player * _player, Tile * _tile)
	{
		if (!(getRoundInfo().isThiefAwaken))
			return false;

		if (_tile->isThief())
			return false;

		/* Succes */
		gameMap->clearAllThiefs();
		_tile->setThief(true);
		roundInfo.isThiefAwaken = false;

		addContentChange(ContentChange::MENU_BUTTONS);

		return true;
	}

	bool Game::nextRound()
	{
		switch (getRoundType()) {
		case RoundType::NORMAL:
			numCurrentPlayer++;
			numCurrentPlayer %= numPlayers;
			break;
		case RoundType::BEGINNING_FORWARD:
			if (!(getCurrentPlayer()->getPhaseState(RoundType::BEGINNING_FORWARD).Completed()))
				return false;

			numCurrentPlayer++;
			if (numCurrentPlayer == numPlayers) {
				setRoundType(RoundType::BEGINNING_BACKWARD);
				numCurrentPlayer = numPlayers - 1;
			}
			break;
		case RoundType::BEGINNING_BACKWARD:
			if (!(getCurrentPlayer()->getPhaseState(RoundType::BEGINNING_BACKWARD).Completed()))
				return false;

			numCurrentPlayer--;
			if (numCurrentPlayer == -1) {
				setRoundType(RoundType::NORMAL);
				numCurrentPlayer = 0;

				gameMap->giveInitialResources();
			}
			break;
		default:
			std::string lError = "Wrong type of round in Game class";
			Console::debug << lError << std::endl;
			throw std::logic_error(lError);
			break;
		}

		roundInfo.isThrowed = false;
		roundInfo.isThiefAwaken = false;
		roundInfo.dices[0] = 0;
		roundInfo.dices[1] = 0;
		roundInfo.roundNumber++;

		addContentChange(ContentChange::CURRENT_PLAYER | ContentChange::MENU_BUTTONS);

		Console::info << "Current player: " << getCurrentPlayer()->getName() << std::endl;
		return true;
	}

	bool Game::throwDices()
	{
		if (roundInfo.isThrowed)
			return false;

		if (!(getRoundType() == RoundType::NORMAL))
			return false;

		roundInfo.isThrowed = true;
		roundInfo.dices[0] = (rand() % 6) + 1;
		roundInfo.dices[1] = (rand() % 6) + 1;

		gameMap->acceptDiceThrow(getDiceSum());

		if (getDiceSum() != 7) {
			addContentChange(ContentChange::PLAYER_RESOURCE);
		}
		else {
			roundInfo.isThiefAwaken = true;
		}

		addContentChange(ContentChange::MENU_BUTTONS | ContentChange::DICE_THROW);
		Console::info << "Dices throwed (" << getDiceSum() << ") = [" << roundInfo.dices[0] << "][" << roundInfo.dices[1] << "]" << std::endl;
		return true;
	}

	RoundType Game::getRoundType() const
	{
		return roundInfo.roundType;
	}

	Game::RoundInfo Game::getRoundInfo() const
	{
		return roundInfo;
	}

	void Game::setRoundType(RoundType _type)
	{
		roundInfo.roundType = _type;
	}

	void Game::addContentChange(unsigned int _change)
	{
		Console::debug << "Game content change: " << _change << std::endl;
		contentChanges |= _change;
	}

	bool Game::getContentChange(unsigned int _change)
	{
		unsigned int tmpFlag = ~(contentChanges | ~(_change));

		if (tmpFlag != 0) {
			return false;
		}
		else {
			contentChanges &= ~(_change);
			return true;
		}
	}

}