#include "AnimateEntity.h"

void AnimateEntity::Start()
{
	running = true;
}

void AnimateEntity::Stop()
{
	running = false;
}

AnimateEntity::~AnimateEntity()
{
}
