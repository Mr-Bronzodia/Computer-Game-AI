#pragma once

#include "raylib-tileson.h"
#include "sprite.hpp"
#include "pc.hpp"
#include "npc.hpp"
#include "Bounds.h"
#include <vector>
#include <optional>
#include <algorithm>
#include "debug-collision-draw.h"
#include "Collider.h"
#include "Enemy.h"

//#define DEBUG_ENABLE

namespace aipfg
{

	class Level {

	private:

		Map tile_map;
		PC* player;
		std::vector<NPC*> npcs;
		std::vector<Sprite*> sprites;
		Level* previous_level;
		Level* next_level;
		std::vector<Collider*> colliders;
		std::vector<Enemy*> enemy_npcs;
		Vector2 enter_point;
		Vector2 exit_point;

#ifdef DEBUG_ENABLE
		DebugDrawCollsion colision_drawer;
#endif 


	public:

		Bounds exit_bounds;
		Bounds enter_bounds;
		Rectangle playable_area;

	public:

		Level(char*, PC*, std::vector<NPC*>&, Bounds&, Bounds&, std::vector<Collider*>&);

		~Level();

		void update();

		void draw();

		void set_previous_room(Level*);
		void set_next_room(Level*);

		Level* get_previous_room();
		Level* get_next_room();

		Vector2 get_enter_point();
		Vector2 get_exit_point();

		void set_enter_point(Vector2& point);
		void set_exit_point(Vector2& point);

		void add_collider(Collider* collider);
		void add_sprite(Sprite* collider);
		void add_NPC(NPC* collider);
		PC* get_player();

		void remove_collider(Collider* to_remove);
		void remove_sprite(Sprite* to_remove);

		void set_playable_are(Rectangle& area);

		void add_enemies(std::vector<Enemy*>& enemies);

	};
	
}