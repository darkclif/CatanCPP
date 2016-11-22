#pragma once
#include <SFML/Graphics.hpp>
class AnimateEntity
{
public:
	void Start();
	void Stop();

	bool isRunning();

	virtual void update(sf::Time _time) = 0;

	AnimateEntity() : running{ true } {};
	AnimateEntity(bool _run) : running{ _run } {};
	~AnimateEntity();

private:
	bool running;
};

