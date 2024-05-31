#include "health-pickup.h"

void aipfg::HealthPickUp::on_pickup()
{
	std::cout << "DEBUG: health picked up, +25 hp" << std::endl;
	player->hp += std::min(player->hp_max - player->hp, 25.0f);
	remove_from_level();
}

aipfg::HealthPickUp::HealthPickUp(Collider* collider, Sprite* sprite, Level* level) : PickUP{collider, sprite, level}
{

}

aipfg::HealthPickUp::~HealthPickUp()
{
	
}

