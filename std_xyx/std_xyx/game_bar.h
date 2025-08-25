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
	/*���ñ�������*/
	void set_img_bg_texture(const std::string name);
	/*������Դ*/
	void set_img_pro_texture(const std::string name);
	/*���õ�ǰֵ*/
	void set_point_num(int num);
	/*���ó�ʼֵֵ*/
	void set_init_point(int num);
	/// <summary>
	/// ���ý������ٷֱ�
	/// </summary>
	/// <param name="num">0.0~1.0</param>
	void set_percent_num(float num);
	void set_is_point(bool point);

protected:
	// ����
	GameImg* img_bg = nullptr;
	// ������
	GameImg* img_pro = nullptr;
	// ��ǰֵ
	float percent_num = 0.0f;
	// �Ƿ��״������
	int is_point = false;
	// ����
	int point_num = 0;
	// ��ʼ����
	int init_point = 0;
};

