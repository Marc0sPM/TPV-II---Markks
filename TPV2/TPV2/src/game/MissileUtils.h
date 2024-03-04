#pragma once

#include "MissileFacade.h"
class Vector2D;
class RandomNumberGenerator;

class MissileUtils : public MissileFacade
{
public:
	MissileUtils();
	virtual ~MissileUtils() {}
	void create_missile() override;
	void remove_all_missiles() override;
private:
	void generateMissile(const Vector2D& p, const Vector2D& v);

	RandomNumberGenerator& rnd_;
	int width_;
	int height_;
};

