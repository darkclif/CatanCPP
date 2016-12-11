#include "Game.h"
#include "Settings.h"
#include "Console.h"

Game::Game(int _players, Map* _map) : gameMap{ _map }, numPlayers{ _players }, contentChanges{0}
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

bool Game::buildLocation(Player * _player, Location * _location)
{
	_location->setOwner(_player);
	return true;
}

bool Game::buildRoad(Player * _player, Road * _road)
{
	_road->setOwner(_player);
	return true;
}

void Game::nextRound()
{
	switch (getRoundType()) {
		case RoundType::NORMAL: 
			numCurrentPlayer++;
			numCurrentPlayer %= numPlayers;
			break;
		case RoundType::BEGINNING_FORWARD:
			numCurrentPlayer++;
			if (numCurrentPlayer == numPlayers) {
				setRoundType( RoundType::BEGINNING_BACKWARD);
				numCurrentPlayer = numPlayers - 1;
			}
			break;
		case RoundType::BEGINNING_BACKWARD:
			numCurrentPlayer--;
			if (numCurrentPlayer == -1) {
				setRoundType(RoundType::NORMAL);
				numCurrentPlayer = 0;
			}
			break;
		default: 
			std::string lError = "Wrong type of round in Game class";
			Console::debug << lError << std::endl;
			throw std::logic_error(lError);  
			break;
	}

	roundInfo.isThrowed = false;
	roundInfo.dices[0] = 0;
	roundInfo.dices[1] = 0;
	roundInfo.roundNumber++;

	addContentChange(ContentChange::CURRENT_PLAYER);

	Console::info << "Current player: " << getCurrentPlayer()->getName() << std::endl;
}

bool Game::throwDices()
{
	if (roundInfo.isThrowed)
		return false;

	roundInfo.isThrowed = true;
	roundInfo.dices[0] = (rand() % 6) + 1;
	roundInfo.dices[1] = (rand() % 6) + 1;

	if (getDiceSum() != 7) {
		addContentChange(ContentChange::PLAYER_RESOURCE);
		gameMap->acceptDiceThrow(getDiceSum());
	}
	else {
		// Change thief state
	}

	Console::info << "Dices throwed! (" << roundInfo.dices[0] << "," << roundInfo.dices[1] << ")" << std::endl;
	return true;
}

Game::RoundType Game::getRoundType()
{
	return roundInfo.roundType;
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
	unsigned int tmpFlag = ~( contentChanges | ~(_change) );

	if (tmpFlag != 0) {
		return false;
	} else {
		contentChanges &= ~(_change);
		return true;
	}
}
