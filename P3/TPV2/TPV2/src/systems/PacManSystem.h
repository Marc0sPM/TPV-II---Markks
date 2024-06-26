// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/System.h"

struct Transform;

class PacManSystem: public ecs::System {
public:

	__SYSID_DECL__(ecs::sys::PACMAN)

	PacManSystem();
	virtual ~PacManSystem();
	void initSystem() override;
	void recieve(const Message& m) override;
	void update() override;
	
private:
	Transform *pmTR_;
	bool immunity;
	void checkDead();
	void resetPos();
};

