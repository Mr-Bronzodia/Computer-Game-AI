#include "shield-pickup.h"

aipfg::ShieldPickUp::ShieldPickUp(Collider* collider, Sprite* sprite, Level* level) : PickUP{ collider, sprite, level }
{

}

aipfg::ShieldPickUp::~ShieldPickUp()
{

}

void aipfg::ShieldPickUp::on_pickup()
{
	std::cout << "DEBUG: shield picked up, +0.1 shield" << std::endl;
	player->shield += 0.1f;
	remove_from_level();
}
