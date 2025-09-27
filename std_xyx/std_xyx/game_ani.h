#pragma once

#include "game_img.h"
#include "timer.h"

struct Ani_Res
{
	std::string name;
	int num;

	Ani_Res() = default;
	Ani_Res(const std::string name, const int num) :name(name), num(num) {}
	~Ani_Res() = default;
};

class GameAni : public GameImg
{
public:
	GameAni() = default;
	virtual ~GameAni() = default;

	GameAni(const std::string& id) : GameImg(id) {}
	GameAni(const std::string& id, int num) : GameImg(id, num) {}

	DEFINE_TYPE_NAME(GameAni);

	virtual void on_init() override;
	virtual void on_enter() override;
	virtual void on_update(float delta) override;
	virtual void on_render() override;
	/*���ö���״̬*/
	void reset();
	/*����ѭ��*/
	void set_loop(bool loop);
	/*����֡���*/
	void set_interval(float val);
	/*������Դ��ʼ���*/
	void set_res_int_val(int val);
	/*��ȡ��ǰ֡����*/
	int get_idx_frame();
	/*��ȡ֡����*/
	int get_res_num();
	/*���ö�����Դ*/
	void set_res_name(const Ani_Res& res);
	/*���õ�ǰ֡����*/
	void set_texture();
	/*��ȡ��ǰ֡����*/
	//SDL_Texture* get_texture();
	/*�����Ƿ񲥷����*/
	bool check_finished();
	/*���ûص�����*/
	void set_on_finished(std::function<void()> func);

private:
	/*��ʱ��*/
	Timer timer;
	// ֡����
	int idx_frame = 0;
	// �Ƿ�ѭ��
	bool is_loop = true;
	// ��Դ��ʼ���
	int res_int_val = 0;
	// ����������Ļص�����
	std::function<void()> on_finished = nullptr;
	// ��Դ����
	int res_num = 0;
};