#include "AnimateEntity.h"

namespace Catan {

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

}