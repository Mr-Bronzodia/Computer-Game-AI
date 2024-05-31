#pragma once

#include "sprite.hpp"
#include "Collider.h"
#include "Level.h"
#include "pick-up.h"

namespace aipfg
{

	class SpeedPickUp : PickUP {

	private:


	public:

		SpeedPickUp(Collider* collider, Sprite* sprite, Level* level);
		~SpeedPickUp() override;
		void on_pickup() override;
		PC* player;



	private:



	};

}
