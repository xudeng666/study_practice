#pragma once
#include "game_obj.h"

#include <SDL_ttf.h>

class GameLable :public GameObj
{
public:
	GameLable() = default;
	~GameLable();
	GameLable(const Vector2 pos);

	void on_enter() override;
	void on_update(float delta) override;
	void on_render() override;
	/*���óߴ�*/
	virtual void set_size();
	/*�����ı�����*/
	void set_lable_text(const std::string str);
	/*����������ɫ*/
	void set_lable_color(const int value);
	/*������Ӱ����*/
	void set_is_shade(bool is);
	/*������Ӱ��ɫ*/
	void set_shade_color(const int value);
	/*������Ӱλ��*/
	void set_pos_shade(const SDL_Point pos);
	/*��������*/
	void set_font(std::string font);
	/*��ȡ����*/
	TTF_Font* get_font();

protected:
	// �ı�����
	std::string lable_text = "";
	// ������ɫ
	int color_lable = 0xFFFFFFFF;		//ARGB
	// �Ƿ���ʾ��Ӱ
	bool is_shade = false;	// �Ƿ�����Ӱ
	// ��Ӱ��ɫ
	int color_shade = 0xFFFFFFFF;		//ARGB
	// ��Ӱ��������ĵ�λ��
	SDL_Point pos_shade = { -1,1 };
	// ����ָ��
	TTF_Font* font = nullptr;
};

/*
* TTF_RenderUTF8_Blended(font, str_score.c_str(), { 55, 55, 55, 255 });
TTF_RenderUTF8_Blended(font, str_score.c_str(), { 255, 255, 255, 255 });
SDL_CreateTextureFromSurface(renderer, suf_score_bg);
SDL_CreateTextureFromSurface(renderer, suf_score_fg);
*/