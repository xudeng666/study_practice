#pragma once
//#include "game_obj.h"
#include "game_img.h"

class GameBar :public GameObj
{
public:
	GameBar() = default;
	~GameBar() = default;
	GameBar(const Vector2 pos);

	void on_enter() override;
	void on_update(float delta) override;
	void on_render() override;
	GameImg* get_img_bg();
	GameImg* get_img_pro();
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
	GameImg* img_bg = nullptr;
	// ������
	GameImg* img_pro = nullptr;
	// ��ǰֵ
	float percent_num = 0.0f;
	// ���ֵ
	SDL_Point max_value = { 0,0 };
	// ����������
	bool is_horizontal = true;
};

