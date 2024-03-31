#pragma once
#include "../ecs/System.h"

struct Transform;
class RandomNumberGenerator;

class GhostSystem : public ecs::System {
public:

	__SYSID_DECL__(ecs::sys::GHOST)

	GhostSystem();
	virtual ~GhostSystem();
	void initSystem() override;
	void recieve(const Message& m) override;
	void update() override;
	void addGhost();
private:
	void calculateAnimDirection(ecs::entity_t g);
	Transform* ghTR_;
	int lastTimeGeneratedGhost_;
	RandomNumberGenerator& rnd_;
};