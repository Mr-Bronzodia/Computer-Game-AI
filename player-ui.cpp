#include "player-ui.h"

#define portret_width 0.3f // as a percentage of frame
#define font_size 20
#define button_margin 50

aipfg::PlayerUI::PlayerUI(PC& player)
{
	pc = &player;

	frame = Rectangle{ 0, 0, 120, 50 };
	portret_frame = Rectangle{ frame.x, frame.y, frame.width * portret_width , frame.height };
	max_health_frame = Rectangle{ portret_frame.x + portret_frame.width , frame.y, frame.width * (1.0f - portret_width), frame.height };
	current_health_frame = Rectangle{ max_health_frame.x, max_health_frame.y, frame.width * (1.0f - portret_width), frame.height };

	portret_tex = LoadTexture("../resources/portret.png");
	portret_full_tex = LoadTexture("../resources/portret_full.png");
	portret_frame_tex = LoadTexture("../resources/frame.png");
	health_icon = LoadTexture("../resources/health.png");
	speed_icon = LoadTexture("../resources/hermes.png");
	shield_icon = LoadTexture("../resources/shield.png");
	damage_icon = LoadTexture("../resources/sword.png");
	button_background = LoadTexture("../resources/Btn01.png");

	is_character_sheet = false;

	character_sheet_frame = Rectangle{ 0, 0, 350, 450 };
	Vector2 screen_center{ GetScreenWidth() / 2, GetScreenHeight() / 2 };
	Vector2 half_extends{ character_sheet_frame.width / 2, character_sheet_frame.height / 2 };

	character_sheet_frame.x = screen_center.x - half_extends.x;
	character_sheet_frame.y = screen_center.y - half_extends.y;

	shop_frame = Rectangle{ character_sheet_frame.x, character_sheet_frame.y + character_sheet_frame.height / 2, character_sheet_frame.width , character_sheet_frame.height / 2 };

	health_button = Rectangle{ shop_frame.x + button_margin, shop_frame.y + button_margin, 100, 50 };
	speed_button = Rectangle{ health_button.x, health_button.y + health_button.height + button_margin, 100, 50 };
	shield_button = Rectangle{ health_button.x + health_button.width + button_margin, health_button.y, 100, 50 };
	damage_button = Rectangle{ health_button.x + health_button.width + button_margin, health_button.y + health_button.height + button_margin, 100, 50 };
}

aipfg::PlayerUI::~PlayerUI()
{
}

void aipfg::PlayerUI::display()
{
	display_hud();

	if (IsKeyPressed(KEY_C)) is_character_sheet = !is_character_sheet;

	if (is_character_sheet) 
	{
		display_character_sheet();
		display_shop();
		update_shop();
	}
}

void aipfg::PlayerUI::display_hud()
{
	DrawTexturePro(portret_tex, Rectangle{ 0, 0, (float)portret_tex.width, (float)portret_tex.height }, portret_frame, Vector2{ 0, 0 }, 0, WHITE);
	DrawRectangleRec(max_health_frame, BLACK);

	current_health_frame.width = max_health_frame.width * (pc->hp / pc->hp_max);
	DrawRectangleRec(current_health_frame, RED);

	std::string health = std::to_string((int)pc->hp) + "/" + std::to_string((int)pc->hp_max);
	DrawText(health.c_str(), max_health_frame.x + 5, max_health_frame.y + max_health_frame.height * 0.3f, font_size, WHITE);
}

void aipfg::PlayerUI::display_character_sheet()
{
	Rectangle portret_full{ character_sheet_frame.x, character_sheet_frame.y, character_sheet_frame.width / 2, character_sheet_frame.height / 2};

	float text_offset = portret_full.x + portret_full.width + 5;
	float bottom_margin = 30;

	std::string health_string = "Max Health: " + std::to_string((int)pc->hp_max);
	std::string might_string = "Might: " + std::to_string((int)pc->might);
	std::string dmg_string = "Damage: " + std::to_string((int)pc->dmg);
	std::string shield_string = "Shield: " + std::to_string((int)pc->shield);
	std::string speed_string = "Speed: " + std::to_string((int)pc->speed_);

	DrawRectangleRec(character_sheet_frame, Color{0, 0, 0, 128});

	DrawTexturePro(portret_full_tex, Rectangle{ 0, 0, (float)portret_full_tex.width, (float)portret_full_tex.height }, portret_full, Vector2{ 0, 0 }, 0, WHITE);
	DrawTexturePro(portret_frame_tex, Rectangle{ 0, 0, (float)portret_frame_tex.width, (float)portret_frame_tex.height }, portret_full, Vector2{ 0, 0 }, 0, WHITE);

	DrawText(health_string.c_str(), text_offset, character_sheet_frame.y + bottom_margin, font_size, WHITE);
	DrawText(might_string.c_str(), text_offset, character_sheet_frame.y + bottom_margin * 2, font_size, WHITE);
	DrawText(dmg_string.c_str(), text_offset, character_sheet_frame.y + bottom_margin * 3, font_size, WHITE);
	DrawText(shield_string.c_str(), text_offset, character_sheet_frame.y + bottom_margin * 4, font_size, WHITE);
	DrawText(speed_string.c_str(), text_offset, character_sheet_frame.y + bottom_margin * 5, font_size, WHITE);
}

void aipfg::PlayerUI::display_shop()
{
	DrawText("Shop", shop_frame.x, shop_frame.y, 20, WHITE);

	draw_button(health_button, "2", health_icon, "Health");
	draw_button(speed_button, "1", speed_icon, "Speed");
	draw_button(shield_button, "5", shield_icon, "Shield");
	draw_button(damage_button, "1", damage_icon, "Damage");
}

void aipfg::PlayerUI::update_shop()
{
	if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
		if (CheckCollisionPointRec(GetMousePosition(), health_button)) {
			
			if (pc->might < 2.0f) return;

			std::cout << "Bought: +25 hp" << std::endl;
			pc->hp_max += 25.0f;
			pc->might -= 2.0f;

		}
		if (CheckCollisionPointRec(GetMousePosition(), shield_button)) {
			
			if (pc->might < 5.0f) return;
			std::cout << "Bought: +1 shield" << std::endl;
			pc->shield += 1.0f;
			pc->might -= 5.0f;

		}
		if (CheckCollisionPointRec(GetMousePosition(), speed_button)) {
			
			if (pc->might < 1) return;
			std::cout << "Bought: +1 speed" << std::endl;
			pc->speed_ += 1;
			pc->might -= 1;
		}
		if (CheckCollisionPointRec(GetMousePosition(), damage_button)) {

			if (pc->might < 1) return;
			std::cout << "Bought: +1 damage" << std::endl;
			pc->dmg += 1;
			pc->might -= 1;
		}
	}
}

void aipfg::PlayerUI::draw_button(Rectangle& src, std::string price, Texture2D& icon, std::string text)
{
	std::string price_str = "Cost: " + price;
	DrawText(price_str.c_str(), src.x, src.y - 12, 12, WHITE);
	DrawTexturePro(button_background, Rectangle{ 0, 0, (float)button_background.width, (float)button_background.height }, src, Vector2{ 0,0 }, 0, WHITE);

	Rectangle icon_frame = Rectangle{ src.x, src.y, src.width * 0.4f, src.height };
	DrawTexturePro(icon, Rectangle{ 0, 0, (float)icon.width, (float)icon.height }, icon_frame, Vector2{ 0,0 }, 0, WHITE);

	DrawText(text.c_str(), icon_frame.x + icon.width, src.y + src.width * 0.4f, font_size, WHITE);
}



