#pragma once
#include "../ecs/Component.h"

class Transform;
class RandomNumberGenerator;

class RotationComponent : public ecs::Component {
public:
	__CMPID_DECL__(ecs::cmp::ROTATION)

	RotationComponent();
	virtual ~RotationComponent();
	void initComponent() override;
	void update() override;

protected:
	Transform* tr_;
	RandomNumberGenerator& rand_;
	int rotation_;
};