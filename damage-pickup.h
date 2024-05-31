#pragma once

#include "sprite.hpp"
#include "Collider.h"
#include "Level.h"
#include "pick-up.h"

namespace aipfg
{

	class DamagePickUp : PickUP {

	private:


	public:

		DamagePickUp(Collider* collider, Sprite* sprite, Level* level);
		~DamagePickUp() override;
		void on_pickup() override;
		PC* player;



	private:



	};

}