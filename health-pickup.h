#pragma once

#include "sprite.hpp"
#include "Collider.h"
#include "Level.h"
#include "pick-up.h"
#include <cmath>

namespace aipfg
{

	class HealthPickUp : PickUP {

	private:


	public:

		HealthPickUp(Collider* collider, Sprite* sprite, Level* level);
		~HealthPickUp() override;
		void on_pickup() override;
		PC* player;



	private:

		

	};

}