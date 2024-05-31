#pragma once

#include "raylib.h"
#include "sprite.hpp"
#include "Collider.h"
#include "Level.h"
#include <functional>

namespace aipfg
{

	class PickUP {

	protected:

		Collider* pickup_collider;
		Sprite* pickup_sprite;
		Level* parent_level;

	public:

		PickUP(Collider* collider, Sprite* sprite, Level* level);
		void remove_from_level();
		virtual ~PickUP();
		virtual void on_pickup() = 0;

	private:

		

	};

}