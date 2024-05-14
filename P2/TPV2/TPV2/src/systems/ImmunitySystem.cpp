#include "ImmunitySystem.h"

#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"

ImmunitySystem::~ImmunitySystem() {
}

void ImmunitySystem::initSystem() {

}

void ImmunitySystem::recieve(const Message& m) {
	switch (m.id) {
	case _m_PACMAN_CHECK_INMUNITY:
		// comprueba si tiene inmunidad, si no, mira el mensaje. Si la tiene, no hace nada y no se acumula la inmunidad
		if (!pacmanImmunity && m.pacman_food.milagrosa != NULL) {
			pacmanImmunity = m.pacman_food.milagrosa;

			// comprueba que el mensaje del choque con la fruta le aporte inmunidad y la activa
			if (pacmanImmunity) {
				activateImmunity();
			}
		}
		break;
	default:
		break;
	}
}

void ImmunitySystem::update() {
	if (pacmanImmunity) {
		if (sdlutils().virtualTimer().currTime() > immunityTime + 10000) {
			pacmanImmunity = false;
			Message m;
			m.id = _m_IMMUNITY_END;
			m.inmunity_end.canDie = false;
			mngr_->send(m);
		}
	}
}

void ImmunitySystem::activateImmunity() {
	immunityTime = sdlutils().virtualTimer().currTime();
	Message m;
	m.id = _m_IMMUNITY_START;
	m.inmunity_start.canDie = true;
	mngr_->send(m);
}
