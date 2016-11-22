#include "AnimateEntity.h"

void AnimateEntity::Start()
{
	running = true;
}

void AnimateEntity::Stop()
{
	running = false;
}

bool AnimateEntity::isRunning()
{
	return running;
}

AnimateEntity::~AnimateEntity()
{
}
