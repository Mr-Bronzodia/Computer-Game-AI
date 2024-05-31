#include "Level.h"


namespace aipfg {

	Level::Level(char* map_path, PC* pc, std::vector<NPC*>& npc_list, Bounds& exit, Bounds& enter, std::vector<Collider*>& collision_bounds)
		: player{ pc }, npcs{ npc_list }, exit_bounds{ exit }, enter_bounds{ enter }, colliders{collision_bounds}
	{
		tile_map = LoadTiled(map_path);
		sprites = std::vector<Sprite*>{player};
		for (NPC* npc : npc_list) sprites.push_back(npc);

		enemy_npcs = std::vector<Enemy*>{};

#ifdef DEBUG_ENABLE
		colision_drawer = DebugDrawCollsion();
#endif 
	}

	Level::~Level() {
		UnloadMap(tile_map);
	}

	void Level::update() {

		player->update();

		for (NPC* npc : npcs) npc->update();

		for (Enemy* enemy : enemy_npcs) enemy->update(*player);

		for (Collider* collider : colliders) {
			if (collider->do_collide(*player->player_collider)) {

				if (collider->is_solid) {
					Vector2 direction = Collider::resolve_collision(*player->player_collider, *collider);
					player->posn_.x += direction.x;
					player->posn_.y += direction.y;
				}
				else {
					collider->on_enter_trigger();
				}
			}
		}
	}


	void Level::draw() {
		DrawTiled(tile_map, 0, 0, WHITE);

		//for (int i = 0; i < enemy_npcs.size(); i++) {
		//	enemy_npcs.at(i)->draw();
		//}

		auto comp = [](Sprite* s1, Sprite* s2) { return (*s1).posn_.y < (*s2).posn_.y; };
		std::sort(sprites.begin(), sprites.end(), comp);
		for (const auto& s : sprites) { (*s).draw(); }


#ifdef DEBUG_ENABLE

		exit_bounds.debug_draw(false);
		enter_bounds.debug_draw(false);
		colision_drawer.update();

		for (Collider* collider : colliders) collider->get_bounds()->debug_draw(collider->is_solid);
		player->player_collider->get_bounds()->debug_draw(true);
		DrawRectangleLines(playable_area.x, playable_area.y, playable_area.width, playable_area.height, YELLOW);

#endif 

	}

	void Level::set_previous_room(Level* level)
	{
		previous_level = level;
	}

	void Level::set_next_room(Level* level)
	{
		next_level = level;
	}

	Level* Level::get_previous_room()
	{
		return previous_level;
	}

	Level* Level::get_next_room()
	{
		return next_level;
	}

	Vector2 Level::get_enter_point() 
	{
		return enter_point;
	}

	void Level::add_collider(Collider* collider)
	{
		colliders.push_back(collider);
	}

	void Level::add_sprite(Sprite* sprite) {
		sprites.push_back(sprite);
	}

	PC* Level::get_player()
	{
		return player;
	}

	void Level::add_NPC(NPC* npc) {
		npcs.push_back(npc);
		sprites.push_back(npc);
	}

	void Level::add_enemies(std::vector<Enemy*>& enemies) {

		enemy_npcs = enemies;

		for (Enemy* enemy : enemy_npcs) sprites.push_back(enemy);
	}

	Vector2 Level::get_exit_point()
	{
		return exit_point;
	}

	void Level::set_enter_point(Vector2& point) {
		enter_point = point;
	}

	void Level::set_exit_point(Vector2& point) {
		exit_point = point;
	}

	void Level::remove_collider(Collider* to_remove) {
		for (int i = 0; i < colliders.size(); i++) {
			if (colliders[i] == to_remove) colliders.erase(colliders.begin() + i);
		}
	}

	void Level::remove_sprite(Sprite* to_remove) {
		for (int i = 0; i < sprites.size(); i++) {
			if (sprites[i] == to_remove) sprites.erase(sprites.begin() + i);
		}
	}
	void Level::set_playable_are(Rectangle& area)
	{
		playable_area = area;
	}
}
