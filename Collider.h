#pragma once

#include "raylib.h"
#include "Bounds.h"
#include "sprite.hpp"
#include <iostream>
#include <functional>

namespace aipfg
{

	class Collider {

	private:

		Bounds collider_bounds;	
		std::function<void()> trigger_function;

	public:

		bool is_solid;
		

	public:

		Collider(Bounds& bounds, bool solid);

		static Vector2 resolve_collision(Collider& moving_bounds, Collider& stationary_bounds);

		void on_enter_trigger();

		Bounds* get_bounds();

		bool do_collide(Collider& other);

		void set_trggier(std::function<void()> func);

	};

}