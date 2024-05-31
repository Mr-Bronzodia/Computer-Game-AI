#pragma once

#include "pc.hpp"
#include "raylib.h"

namespace aipfg
{

	class PlayerUI 
	{
	private:

		PC* pc;

		Rectangle frame;
		Rectangle shop_frame;
		Rectangle portret_frame;
		Rectangle max_health_frame;
		Rectangle current_health_frame;
		Rectangle character_sheet_frame;

		Texture2D portret_tex;
		Texture2D portret_full_tex;
		Texture2D portret_frame_tex;
		Texture2D health_icon;
		Texture2D speed_icon;
		Texture2D shield_icon;
		Texture2D damage_icon;
		Texture2D button_background;

		Rectangle health_button;
		Rectangle speed_button;
		Rectangle shield_button;
		Rectangle damage_button;

		bool is_character_sheet;

	public:
			PlayerUI(PC& player);
			~PlayerUI();

			void display();
	private:

			void display_hud();
			void display_character_sheet();
			void display_shop();
			void update_shop();
			void draw_button(Rectangle& src, std::string price, Texture2D& icon, std::string text);

	};

} // namespace aipfg
