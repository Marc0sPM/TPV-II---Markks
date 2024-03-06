#pragma once
#include "../ecs/ecs.h"

using ecs::entity_t;

class MissileFacade 
{
	public:
		MissileFacade() {
		}
		virtual ~MissileFacade() {
		}
		virtual void create_missile() = 0;
		virtual void remove_all_missiles() = 0;
		virtual void remove_missile(ecs::entity_t a) = 0;
};

