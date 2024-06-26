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
	void removeGhost(ecs::entity_t g);
	void removeAllGhosts();
private:
	/// <summary>
	/// Calcula el vector velocidad del ghost respecto a la posicion
	/// del pacman y la establece en el transform del  ghost
	/// </summary>
	/// <param name="g">Ghost entity</param>
	void calcVelFromPacman(ecs::entity_t g);
	void vulnerable();
	Transform* ghTR_;
	int lastTimeGeneratedGhost_;
	RandomNumberGenerator& rnd_;
	bool canDie;
};