#pragma once

#include "sprite.hpp"
#include "raylib-cpp.hpp"
#include "game-manager.hpp"
#include "pc.hpp"
#include <iostream>


namespace aipfg {

	class Enemy : public Sprite {
	public:
		Enemy(Sprite&);
		~Enemy();

		void update(PC&);
		void draw();
		void attack(PC&);
		void select_type();

		int health = 25;
		float dmg = 0.25;
	
		//std::future<void> attack_cool = std::async(std::launch::async, [] {WaitTime(10); });
	};
}