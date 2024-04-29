#pragma once

#include "../ecs/System.h"

class ImmunitySystem : public ecs::System {
public:

	__SYSID_DECL__(ecs::sys::IMMUNITY)

		ImmunitySystem() : pacmanImmunity(false), immunityTime(0) {};
	virtual ~ImmunitySystem();
	void initSystem() override;
	void recieve(const Message& m) override;
	void update() override;

private:
	bool pacmanImmunity;
	int immunityTime;
	void activateImmunity();
};