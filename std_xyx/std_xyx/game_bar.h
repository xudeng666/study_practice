#pragma once

#include "game_img.h"

class GameBar :public GameObj
{
public:
	GameBar() = default;
	virtual ~GameBar() = default;

	virtual void on_init() override;
	virtual void on_enter() override;
	virtual void on_update(float delta) override;
	virtual void on_render() override;

	DEFINE_TYPE_NAME(GameBar);

	TreeNode_SP get_img_bg();
	TreeNode_SP get_img_pro();
	/// <summary>
	/// ���ý������ٷֱ�
	/// </summary>
	/// <param name="num">0.0~1.0</param>
	void set_percent_num(float num);
	/// <summary>
	/// ���ý��������ֵ
	/// </summary>
	/// <param name="value">SDL_Point</param>
	void set_max_value(SDL_Point value);
	/// <summary>
	/// ���ý���������
	/// </summary>
	/// <param name="is_h">true ���� false ����</param>
	void set_is_horizontal(bool is_h);

protected:
	// ����
	TreeNode_WP img_bg;
	// ������
	TreeNode_WP img_pro;
	// ��ǰֵ
	float percent_num = 0.0f;
	// ���ֵ
	SDL_Point max_value = { 0,0 };
	// ����������
	bool is_horizontal = true;
};

INIT_TYPE_NAME(GameBar);