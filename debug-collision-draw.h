#pragma once
#include "raylib.h"
#include <vector>
#include "Bounds.h"
#include <iostream>

namespace aipfg
{

	class DebugDrawCollsion {

	private:

		std::vector<Bounds> draw_bounds;
		Vector2 top_right;
		Vector2 bottom_left;

	public:

		DebugDrawCollsion();

		void update();

		Bounds create_bounds(Vector2&, Vector2&);
	};

}