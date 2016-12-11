#pragma once
#include "State.h"
#include "StateManager.h"
#include "Functions.h"

class IntroState : public State
{
public:
	bool HandleEvents(sf::Event _event);
	bool Update(sf::Time _dt);
	void Draw(sf::RenderWindow& _window);

	void resizeContent();

	IntroState( StateManager* _engine, Context _context);
	~IntroState();

private:
	
	sf::Sprite	sprLogo;
	sf::Sprite	sprBigLogo;
	sf::Text	txtPrompt;
	sf::Text	txtPresents;
	
	float		alpha;
private:
	void nextStep();
	void SkipIntro();
};

