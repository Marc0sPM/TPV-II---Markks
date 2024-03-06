#pragma once

#include "../ecs/Component.h"

class Transform;

class CheckLimits : public ecs::Component
{
public:
	__CMPID_DECL__(ecs::cmp::CHECKLIMITS);

	CheckLimits();
	virtual ~CheckLimits() {}
	void initComponent() override;
	void update() override;


private:
	Transform* tr_;
};

