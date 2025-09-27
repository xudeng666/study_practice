#pragma once

#include "game_img.h"

class GameBar :public GameObj
{
public:
	GameBar() = default;
	virtual ~GameBar() = default;

	GameBar(const std::string& id) : GameObj(id) {}
	GameBar(const std::string& id, int num) : GameObj(id, num) {}

	virtual void on_init() override;
	virtual void on_enter() override;
	virtual void on_update(float delta) override;
	virtual void on_render() override;
	virtual void set_size(const SDL_Point& size) override;

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
	void set_max_value(const SDL_Point& value);
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