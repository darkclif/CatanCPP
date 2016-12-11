#include "IntroState.h"
#include "ResourceManager.h"

bool IntroState::HandleEvents(sf::Event _event)
{
	sf::Event lEvent = _event;

	// Key pressed
	if (lEvent.type == sf::Event::KeyPressed) {
		SkipIntro();
	}

	// Cross button
	if (_event.type == sf::Event::Closed) {
		requestStackClear();
	}

	return true;
}

bool IntroState::Update(sf::Time _dt)
{
	alpha += 2.f * _dt.asSeconds();
	txtPrompt.setFillColor( sf::Color(255,255,255,((int)alpha % 2) * 255));

	return true;
}

void IntroState::Draw(sf::RenderWindow & _window)
{
	_window.draw(sprLogo);
	_window.draw(txtPrompt);
	_window.draw(sprBigLogo);
	_window.draw(txtPresents);
}

void IntroState::resizeContent()
{
}

void IntroState::SkipIntro() {
	requestStackPop();
	requestStackPush(States::MAIN_MENU);
}

IntroState::IntroState( StateManager* _engine, State::Context _context) : State(_engine, _context)
{
	alpha = 0.f;

	// Logo
	sprLogo.setPosition(0,-300);
	sprLogo.setTexture( ResourceManager::getInstance().getTexture(Catan::Textures::LOGO) );
	Catan::setOriginAtCenter(sprLogo);

	// Big logo
	sprBigLogo.setPosition(0, 0);
	sprBigLogo.setTexture( ResourceManager::getInstance().getTexture(Catan::Textures::BIG_LOGO));
	Catan::setOriginAtCenter(sprBigLogo);

	// Prompt
	std::string lMsg = "Press any key to continue...";
	txtPrompt.setString(lMsg);
	txtPrompt.setPosition(0, 240);
	txtPrompt.setFont( ResourceManager::getInstance().getFont(Catan::Fonts::DEFAULT));
	Catan::setOriginAtCenter(txtPrompt);

	// Presents
	lMsg = "PRESENTS";
	txtPresents.setCharacterSize(30);
	txtPresents.setString(lMsg);
	txtPresents.setPosition(0, -150);
	txtPresents.setFont(ResourceManager::getInstance().getFont(Catan::Fonts::DEFAULT));
	Catan::setOriginAtCenter(txtPresents);

	// Set center view
	sf::View lView = context.window->getView();
	lView.setCenter( sf::Vector2f(0,0));
	
	context.window->setView(lView);
}

IntroState::~IntroState()
{
}
