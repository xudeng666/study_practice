#pragma once

#include <SDL_ttf.h>

#include "game_obj.h"

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
	void set_pos_lable(const Vector2 pos);
	/*������Ӱλ��*/
	void set_pos_shade(const Vector2 pos);
	/*��������*/
	void set_font(std::string name);
	/*��ȡ����*/
	TTF_Font* get_font();
	/*����ê��*/
	void set_anchor_mode(AnchorMode mode);
	/*��ȡê��*/
	AnchorMode get_anchor_mode();

protected:
	// �ı�����
	std::string lable_text = "";
	// ������ɫ
	int color_lable = 0xFFFFFFFF;		//ARGB
	// �Ƿ���ʾ��Ӱ
	bool is_shade = false;	// �Ƿ�����Ӱ
	// ��Ӱ��ɫ
	int color_shade = 0x55555555;		//ARGB
	// ���ĵ�λ��
	Vector2 pos_lable = { 0,0 };
	// ��Ӱ��������ĵ�λ��
	Vector2 pos_shade = { -2,2 };
	// ����ָ��
	TTF_Font* font = nullptr;
	// �ı�ê��
	AnchorMode anchor_mode = AnchorMode::TOPLEFT;
};