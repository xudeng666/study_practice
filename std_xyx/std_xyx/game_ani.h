#pragma once

#include "game_img.h"
#include "timer.h"

struct Ani_Res
{
	std::string name;
	int num;
};

class GameAni : public GameImg
{
public:
	GameAni() = default;
	~GameAni() = default;
	GameAni(const Vector2 pos, const Ani_Res res);

	virtual void on_enter() override;
	virtual void on_update(float delta) override;
	virtual void on_render() override;
	/*���ö���״̬*/
	void reset();
	/*����ѭ��*/
	void set_loop(bool loop);
	/*����֡���*/
	void set_interval(float val);
	/*��ȡ��ǰ֡����*/
	int get_idx_frame();
	/*���ö�����Դ*/
	void set_res_name(const Ani_Res res);
	/*���õ�ǰ֡����*/
	void set_Texture();
	/*��ȡ��ǰ֡����*/
	SDL_Texture* get_Texture();
	/*�����Ƿ񲥷����*/
	bool check_finished();
	/*���ûص�����*/
	void set_on_finished(std::function<void()> func);

private:
	/*��ʱ��*/
	Timer timer;
	// ֡����
	int idx_frame = 1;
	// �Ƿ�ѭ��
	bool is_loop = true;
	// ����������Ļص�����
	std::function<void()> on_finished = nullptr;
	// ��Դ����
	int res_num;
};

