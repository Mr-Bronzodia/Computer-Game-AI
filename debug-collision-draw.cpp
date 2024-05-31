#include "debug-collision-draw.h"

aipfg::DebugDrawCollsion::DebugDrawCollsion()
{
	draw_bounds = std::vector<Bounds>{};
	top_right = Vector2{ 0,0 };
	bottom_left = Vector2{ 0,0 };
}

void aipfg::DebugDrawCollsion::update()
{
	for (Bounds bound : draw_bounds) bound.debug_draw(true);

	if (top_right.x != 0 && top_right.y != 0) DrawCircle(top_right.x, top_right.y, 7, PINK);

	if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return;


	if (top_right.x == 0 && top_right.y == 0) {
		top_right = GetMousePosition();
		return;
	}

	if (bottom_left.x == 0 && bottom_left.y == 0) {

		bottom_left = GetMousePosition();
		Bounds newBounds = create_bounds(top_right, bottom_left);
		draw_bounds.push_back(newBounds);
		std::cout << "Bounds{Vector2{" << newBounds.get_bounding_centre().x << ", " << newBounds.get_bounding_centre().y << "}, Vector2{" << newBounds.extend.x << ", " << newBounds.extend.y << "}}" << std::endl;
		top_right = Vector2{ 0,0 };
		bottom_left = Vector2{ 0,0 };

	}
}

aipfg::Bounds aipfg::DebugDrawCollsion::create_bounds(Vector2& top_right, Vector2& bottom_left)
{
	Vector2 lenght{ bottom_left.x - top_right.x, bottom_left.y - top_right.y };

	Vector2 extends{ lenght.x / 2, lenght.y / 2 };

	Vector2 centre{ top_right.x + extends.x, top_right.y + extends.y };

	//Vector2 centre{ top_right.x + extends.x, top_right.y - extends.y };

	return Bounds(centre, extends);
}
