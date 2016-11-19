#pragma once
class AnimateEntity
{
public:
	void Start();
	void Stop();

	virtual void Update( float _time ) = 0;

	AnimateEntity() : running{ false } {};
	AnimateEntity(bool _run) : running{ _run } {};
	~AnimateEntity();

private:
	bool running;
};

