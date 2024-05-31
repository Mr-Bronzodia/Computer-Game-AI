#include "speed-pickup.h"

aipfg::SpeedPickUp::SpeedPickUp(Collider* collider, Sprite* sprite, Level* level) : PickUP { collider, sprite, level }
{
}

void aipfg::SpeedPickUp::on_pickup()
{
	std::cout << "DEBUG: speed picked up, +1 speed" << std::endl;
	player->speed_ += 1;
	remove_from_level();
}



aipfg::SpeedPickUp::~SpeedPickUp()
{

}