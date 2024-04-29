// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <cstdint>
#include "../ecs/ecs.h"

using msgId_type = uint8_t;
enum msgId : msgId_type {
	_m_NEW_GAME, 
	_m_ROUND_START,
	_m_ROUND_OVER, 
	_m_GAME_OVER,
	_m_PACMAN_FOOD_COLLISION,
	_m_PACMAN_GHOST_COLLISION,
	_m_IMMUNITY_START, 
	_m_IMMUNITY_END,
	_m_ADD_SCORE

};


struct Message {
	msgId_type id;

	// if we use union we save memory, but then use only primitive
	// types, otherwise you will need to define constructors almost
	// every where.

	union {
		// _m_ADD_SCORE
		struct {
			int score;
		}add_score;

		// _m_NEW_GAME
		struct {

		}new_game;


		// _m_ROUND_START
		struct {

		}round_start;

		// _m_ROUND_OVER
		struct {
			int lifes;
		}round_over;

		// _m_PACMAN_GHOST_COLLISION
		struct 
		{
			ecs::entity_t ghost;
		}pacman_ghost;

		// _m_PACMAN_FOOD_COLLISION
		struct
		{
			ecs::entity_t fruit;
			bool milagrosa;
		}pacman_food;

		// _m_ROUND_OVER
		/*struct
		{
			
		}round_over;*/

		// _m_INMUNITY_START
		struct
		{
			bool canDie;
		}inmunity_start;

		// _m_INMUNITY_END
		struct
		{
			bool canDie;
		}inmunity_end;
	};
};
