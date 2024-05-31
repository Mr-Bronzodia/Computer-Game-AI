#include "damage-pickup.h"

void aipfg::DamagePickUp::on_pickup()
{
	std::cout << "DEBUG: damage picked up, +1 dmg" << std::endl;
	player->dmg += 1;
	remove_from_level();
}

aipfg::DamagePickUp::DamagePickUp(Collider* collider, Sprite* sprite, Level* level) : PickUP{ collider, sprite, level }
{

}


aipfg::DamagePickUp::~DamagePickUp()
{

}
