#pragma once

#include "raylib.h"

namespace aipfg
{

	class Bounds {

	private:

		Vector2 centre;

	public: 
		
		Vector2 extend;

		Vector2 top_point;
		Vector2 botom_point;
		
	public:

		Bounds(Vector2&, Vector2&);

		bool is_inside(Vector2&);

		bool do_overlap(Bounds*);

		void debug_draw(bool);

		void set_bounding_centre(Vector2&);

		Vector2 get_bounding_centre();

		float get_area();

	};

}