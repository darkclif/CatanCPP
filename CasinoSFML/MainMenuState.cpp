#include "MainMenuState.h"

namespace Catan {

	//
	// LOOP FUNCTIONS 
	//
	bool MainMenuState::HandleEvents(sf::Event _event)
	{
		sfg_dektop.HandleEvent(_event);
		return false;
	}

	bool MainMenuState::Update(sf::Time _dt)
	{
		sprite->update(_dt);
		sfg_dektop.Update(_dt.asSeconds());
		return false;
	}

	void MainMenuState::Draw(sf::RenderWindow & _window)
	{
		sprite->draw(_window);
		sfg_sfgui.Display(_window);
	}

	void MainMenuState::resizeContent()
	{
	}

	//
	// BUTTONS
	//
	void MainMenuState::NewGame()
	{
		requestStackPop();
		requestStackPush(States::GAME);
	}

	void MainMenuState::Exit()
	{
		requestStackClear();
	}

	void MainMenuState::spawnGUI() {
		// Widgets
		auto btnNewGame = sfg::Button::Create("New game");
		btnNewGame->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&MainMenuState::NewGame, this));

		auto btnExit = sfg::Button::Create("Exit");
		btnExit->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&MainMenuState::Exit, this));

		// Box
		auto boxMainBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
		boxMainBox->Pack(btnNewGame, true);
		boxMainBox->Pack(btnExit, true);

		// Window
		auto winWindow = sfg::Window::Create();
		winWindow->SetTitle("Menu");
		winWindow->Add(boxMainBox);

		winWindow->SetAllocation(sf::FloatRect(0, 0, 400, 200));
		winWindow->SetStyle(sfg::Window::Style::BACKGROUND);
		setWindowAtCenter(winWindow, context.window);

		sfg_dektop.Add(winWindow);
	}

	void MainMenuState::spawnBackground() {
		std::unique_ptr<AnimateSprite> tmpSprite(new AnimateSprite(Textures::Name::MENU_BG_2));
		tmpSprite->addFrame(sf::IntRect(0, 0, 232, 666));
		tmpSprite->addFrame(sf::IntRect(232, 0, 232, 666));

		tmpSprite->addDelay(sf::seconds(4.f));
		tmpSprite->addDelay(sf::seconds(0.2f));
		tmpSprite->addDelay(sf::seconds(0.2f));
		tmpSprite->addDelay(sf::seconds(0.2f));

		tmpSprite->setPosition(sf::Vector2f(300, 300));

		sprite = std::move(tmpSprite);
	}

	MainMenuState::MainMenuState(StateManager * _engine, Context _context) : State(_engine, _context)
	{
		setViewOrigin(context.window, sf::Vector2f(0.f, 0.f));

		spawnGUI();
		spawnBackground();
	}

	MainMenuState::~MainMenuState() {
	}

}