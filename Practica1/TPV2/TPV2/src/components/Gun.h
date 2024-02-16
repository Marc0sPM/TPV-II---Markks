#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"

class Transform;

class Gun : public ecs::Component
{

public:

	__CMPID_DECL__(ecs::cmp::GUN);

	Gun();
	virtual ~Gun();

	void initComponent() override;
	void update() override;
	
private:
	const Uint32 shootTimeLimit_ = 250; // 0.25 sec
	Uint32 lastTimeShoot_;
	Transform* tr_;
};

