#pragma once

#include "game_img.h"

/*��ť��*/
class GameBtn :public GameImg
{
public:
	GameBtn() = default;
	~GameBtn() = default;
	GameBtn(const Vector2 pos, const std::string name);

	void on_update(float delta) override;
	// void on_render(const Camera* camera) override;
	void on_cursor_down() override;
	void on_cursor_up() override;
	void on_cursor_hover(bool is_hover) override;
	/*ִ�е��*/
	virtual void on_click() {}

private:
	std::string res_name;
	ButtonState status = ButtonState::NORMAL;
};

