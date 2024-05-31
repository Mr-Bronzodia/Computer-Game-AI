#include "Collider.h"

aipfg::Collider::Collider(Bounds& bounds, bool solid) 
	: collider_bounds {bounds}, is_solid{solid}
{

}

Vector2 aipfg::Collider::resolve_collision(Collider& moving_collider, Collider& stationary_collider)
{
	Bounds* moving_bounds = moving_collider.get_bounds();
	Bounds* stationary_bounds = stationary_collider.get_bounds();

	Vector2 collision_direction = { moving_bounds->get_bounding_centre().x - stationary_bounds->get_bounding_centre().x,  moving_bounds->get_bounding_centre().y - stationary_bounds->get_bounding_centre().y };

	collision_direction.x *= 0.09f;
	collision_direction.y *= 0.09f;

	return collision_direction;
}

void aipfg::Collider::on_enter_trigger()
{
	trigger_function();
}

aipfg::Bounds* aipfg::Collider::get_bounds()
{
	return &collider_bounds;
}

bool aipfg::Collider::do_collide(Collider& other)
{
	return collider_bounds.do_overlap(other.get_bounds());
}

void aipfg::Collider::set_trggier(std::function<void()> func)
{
	trigger_function = func;
}

