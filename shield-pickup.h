#pragma once

#include "sprite.hpp"
#include "Collider.h"
#include "Level.h"
#include "pick-up.h"

namespace aipfg
{

	class ShieldPickUp : PickUP {

	private:


	public:

		ShieldPickUp(Collider* collider, Sprite* sprite, Level* level);
		~ShieldPickUp() override;
		void on_pickup() override;
		PC* player;



	private:



	};

}
