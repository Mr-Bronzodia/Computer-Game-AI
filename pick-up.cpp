#include "pick-up.h"

aipfg::PickUP::PickUP(Collider* collider, Sprite* sprite, Level* level) : pickup_collider{collider}, pickup_sprite{sprite}, parent_level{level}
{
	level->add_collider(pickup_collider);
	level->add_sprite(pickup_sprite);
	pickup_collider->set_trggier(std::bind(&PickUP::on_pickup, this));
	
}

void aipfg::PickUP::remove_from_level()
{
	parent_level->remove_collider(pickup_collider);
	parent_level->remove_sprite(pickup_sprite);
}

aipfg::PickUP::~PickUP()
{

}
