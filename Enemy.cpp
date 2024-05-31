#include "sprite.hpp"
#include "raylib-cpp.hpp"
#include "game-manager.hpp"
#include "pc.hpp"
#include "Enemy.h"
#include <iostream>


namespace aipfg {



	Enemy::Enemy(Sprite& sprite) : Sprite{sprite}
	{
		//position = {0, 0}; // Set initial position to (0, 0)
  //      direction = {1, 0}; // Set initial movement direction to (1, 0) (right)
  //      speed = 2;
	}

	Enemy::~Enemy()
	{
		std::cout << "DEBUG: Enemy dead" << std::endl;
	}

	void Enemy::update(PC& pc)
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
			
			health -= pc.dmg;
			std::cout << "DEBUG: Player attacked me" << std::endl;
			std::cout << "DEBUG: ENEMY HP: " << health << std::endl;
			this->attack(pc);
			
		}
		
		if (this->health <= 0) { 
			health = 25;
			pc.might += 1;
			pc.hp_max = pc.hp_max + ((int)pc.hp_max % 25);
			pc.dmg += 2;
			pc.speed_ += 0.5;
			pc.shield += 0.1;
		}

	}

	void Enemy::draw() {
		Sprite::draw();
	}

	void Enemy::attack(PC& pc)
	{
		std::cout << "Player hit: " << dmg << std::endl;
		pc.hp -= dmg;
	}

	void Enemy::select_type()
	{
	}
	
	//void Enemy::move()
 //       {
 //       
 //       position.x += direction.x * speed;
 //       position.y += direction.y * speed;

 //       
 //       if (position.x < 0 || position.x > GetScreenWidth()) {
 //           direction.x *= -1; 
 //       }
 //       if (position.y < 0 || position.y > GetScreenHeight()) {
 //           direction.y *= -1; 
 //       }
 //   }

}
