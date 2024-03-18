#pragma once
#include "BlackHoleFacade.h"

class Vector2D;
class RandomNumberGenerator;

class BlackHoleUtils : public BlackHoleFacade {
public:
	BlackHoleUtils();
	virtual ~BlackHoleUtils();
	void remove_all_blackholes() override;
	void create_blackholes(int n) override;

private:
	void generateBlackHole(const Vector2D& p);
	RandomNumberGenerator& rand_;
	int width_;
	int height_;
	int rotation_;

};

