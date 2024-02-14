#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"

class Image;

class Transform;

class Health : public ecs::Component
{
public:

	__CMPID_DECL__(ecs::cmp::HEALTH);

	Health();
	virtual ~Health();
	void initComponent() override;
	void update()override;
	void render() override;

	inline void resetLifes() {
		currentLifes_ = maxLifes_;
	}
	inline void loseLife() {
		if(currentLifes_ > 0)  currentLifes_--;
	}
	inline int getLifes() const {
		return currentLifes_;
	}

private:
	const int maxLifes_ = 3;
	int currentLifes_;
};



