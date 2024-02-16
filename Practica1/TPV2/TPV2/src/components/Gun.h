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
	void render() override;

	struct Bullet {
		bool used = false;
		Vector2D pos;
		Vector2D vel;
		int width;
		int height;
		float rot;
	};

	constexpr static auto max_bullets = 20;
	typedef std::array<Bullet, max_bullets> bullets_array;
	typedef bullets_array::iterator iterator;

	void reset();
	inline iterator begin() {
		return bullets_.begin();
	}

	inline iterator end() {
		return bullets_.end();
	}
private:
	const Uint32 shootTimeLimit_ = 250; // 0.25 sec
	Uint32 lastTimeShoot_;
	Transform* tr_;
	bullets_array bullets_;
};

