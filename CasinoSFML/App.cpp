#include "App.h"

#include "State.h"
#include "StateManager.h"
#include "States.h"
#include "Settings.h"

#include "IntroState.h"
#include "MainMenuState.h"
#include "GameState.h"

void App::handleGlobalEvent(sf::Event _event, State::Context _context, StateManager& _engine) {
	// Window resize
	if (_event.type == sf::Event::Resized) {
		sf::RenderWindow* lWindow = _context.window;
		sf::Vector2u lSize = lWindow->getSize();
		sf::View lView = lWindow->getView();

		lView.setSize(sf::Vector2f((float)lSize.x,(float)lSize.y));
		lWindow->setView(lView);
	}

	// Cross button
	if (_event.type == sf::Event::Closed) {
		_engine.requestStackClear();
	}
}

void App::registerStates( StateManager& _engine) {
	_engine.registerState<IntroState>(States::INTRO);
	_engine.registerState<MainMenuState>(States::MAIN_MENU);
	_engine.registerState<GameState>(States::GAME);
}

void App::Run()
{
	std::srand(unsigned(std::time(0)));
	
	// SFML
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow sf_window(sf::VideoMode(1300, 1000), "SFML works!", sf::Style::Default, settings);
	sf_window.setFramerateLimit(30);

	sf_window.resetGLStates();

	// SFGUI Global Styles
	Settings::setSfguiStyles();

	// Engine
	State::Context lContext;
	lContext.window = &sf_window;
	
	StateManager stateEngine(lContext);
	registerStates(stateEngine);

	stateEngine.pushState(States::INTRO);

	sf::Clock time;
	while ( !stateEngine.isEmpty() ) {
		sf::Event event;

		while (sf_window.pollEvent(event)) {
			handleGlobalEvent(event, lContext, stateEngine);
			stateEngine.handleEvent(event);
		}

		stateEngine.Update( time.getElapsedTime() );
		time.restart();

		stateEngine.Draw( sf_window );
	}

}

App::App()
{
};

App::~App()
{
}
