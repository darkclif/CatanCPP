#include "GameState.h"
#include "Functions.h"

bool GameState::HandleEvents(sf::Event _event)
{
	sfg_desktop.HandleEvent(_event);

	if(!playerGUI->isMouseOverGUI())
		map->HandleEvent(_event);

	/* Keyboard */
	if (_event.type == sf::Event::KeyPressed) {
		switch (_event.key.code){
			/* Exit */
			case sf::Keyboard::Escape: exitGame(); break;
			/* Navigate map*/
			case sf::Keyboard::Left: changeActionKeyState(ActionKey::LEFT, true); break;
			case sf::Keyboard::Right: changeActionKeyState(ActionKey::RIGHT, true); break;
			case sf::Keyboard::Up: changeActionKeyState(ActionKey::UP, true);  break;
			case sf::Keyboard::Down: changeActionKeyState(ActionKey::DOWN, true);  break;
			case sf::Keyboard::Q: changeActionKeyState(ActionKey::ZOOM_OUT, true);  break;
			case sf::Keyboard::A: changeActionKeyState(ActionKey::ZOOM_IN, true);  break;
			default:break;
		}
	}

	if (_event.type == sf::Event::KeyReleased) {
		switch (_event.key.code) {
			/* Navigate map*/
			case sf::Keyboard::Left: changeActionKeyState(ActionKey::LEFT, false); break;
			case sf::Keyboard::Right: changeActionKeyState(ActionKey::RIGHT, false); break;
			case sf::Keyboard::Up: changeActionKeyState(ActionKey::UP, false);  break;
			case sf::Keyboard::Down: changeActionKeyState(ActionKey::DOWN, false);  break;
			case sf::Keyboard::Q: changeActionKeyState(ActionKey::ZOOM_OUT, false);  break;
			case sf::Keyboard::A: changeActionKeyState(ActionKey::ZOOM_IN, false);  break;
			default:break;
		}
	}

	return true;
}

bool GameState::Update(sf::Time _dt)
{
	sfg_desktop.Update(_dt.asSeconds());
	playerGUI->UpdateGUI(_dt);

	// Check if view is not out of table
	struct { float top, down, left, right; } boundView, boundTable;

	/* View */
	const float OFFSET = 10.f;

	sf::Vector2i lPoint1(0,0);
	sf::Vector2i lPoint2(context.window->getSize());

	sf::Vector2f lFloatPoint1 = context.window->mapPixelToCoords(lPoint1);
	sf::Vector2f lFloatPoint2 = context.window->mapPixelToCoords(lPoint2);

	boundView.left = lFloatPoint1.x + OFFSET;
	boundView.right = lFloatPoint2.x - OFFSET;
	boundView.top = lFloatPoint1.y + OFFSET;
	boundView.down = lFloatPoint2.y - OFFSET;

	/* Table */
	sf::FloatRect lTableRect = tableEntity.getSpriteGlobalBounds();

	boundTable.left = lTableRect.left;
	boundTable.right = lTableRect.left + lTableRect.width;
	boundTable.top = lTableRect.top;
	boundTable.down = lTableRect.top + lTableRect.height;

	// Move screen
	if(isActionKeyPressed(ActionKey::LEFT) && (boundView.left > boundTable.left)) 
		Catan::moveView(context.window, sf::Vector2f(-MOVE_SPEED * _dt.asSeconds(), 0.f));
	if(isActionKeyPressed(ActionKey::RIGHT) && (boundView.right < boundTable.right))
		Catan::moveView(context.window, sf::Vector2f(MOVE_SPEED * _dt.asSeconds(), 0.f));
	if(isActionKeyPressed(ActionKey::UP) && (boundView.top > boundTable.top))
		Catan::moveView(context.window, sf::Vector2f(0.f, -MOVE_SPEED * _dt.asSeconds()));
	if(isActionKeyPressed(ActionKey::DOWN) && (boundView.down < boundTable.down))
		Catan::moveView(context.window, sf::Vector2f(0.f, MOVE_SPEED * _dt.asSeconds()));

	if (isActionKeyPressed(ActionKey::ZOOM_IN)) Catan::zoomView(context.window, 1.2f);
	if (isActionKeyPressed(ActionKey::ZOOM_OUT)) Catan::zoomView(context.window, 0.8f);

	return true;
}

void GameState::Draw(sf::RenderWindow & _window)
{
	tableEntity.draw(_window);
	map->Draw(_window);
	playerGUI->draw(_window);
	sfg_sfgui.Display(_window);
}

void GameState::spawnGUI() {
}

void GameState::resizeContent()
{
	playerGUI->resizeContent();
}

bool GameState::isActionKeyPressed(ActionKey _key)
{
	return actionKeysStates[_key];
}

void GameState::changeActionKeyState(ActionKey _key, bool _state)
{
	actionKeysStates[_key] = _state;
}

GameState::GameState(StateManager * _engine, Context _context): State(_engine, _context)
{
	actionKeysStates.resize(ActionKey::_SIZE, false);

	map = std::make_unique<Map>(_context.window);
	game = std::make_unique<Game>(3, map.get());
	playerGUI = std::make_unique<PlayerGUI>(sfg_sfgui, sfg_desktop, game.get(), map.get());

	Catan::zoomView(context.window, 3.f);

	spawnGUI();
}

GameState::~GameState()
{
}

//
// Actions
//
void GameState::exitGame() {
	requestStackPop();
	requestStackPush(States::MAIN_MENU);
}

//
// [Table]
//
void GameState::TableEntity::draw(sf::RenderWindow & _window)
{
	sf::Sprite tmpSprite(getSprite());
	tmpSprite.setTexture(getTexture());

	Catan::setOriginAtCenter(tmpSprite);

	_window.draw(tmpSprite);
}

GameState::TableEntity::TableEntity()
{
	setTexture(ResourceMgr.getTexture(Catan::Textures::Name::TABLE));

	setScale(6.f,6.f);
	setPosition(sf::Vector2f(610.f,-800.f));
}

sf::Texture & GameState::TableEntity::getTexture()
{
	return ResourceMgr.getTexture(Catan::Textures::Name::TABLE);
}
