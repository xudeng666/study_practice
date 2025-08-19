#pragma once

#include "res_mgr.h"
#include "game_img.h"

class GameAni : public GameImg
{
public:
	GameAni() = default;
	~GameAni() = default;
	GameAni(const Vector2 pos, const std::string name, const int num);

	void on_update(float delta) override;
	void on_render() override;
	/*���ö���״̬*/
	void reset();
	/*����ѭ��*/
	void set_loop(bool loop);
	/*����֡���*/
	void set_interval(float val);
	/*��ȡ��ǰ֡����*/
	int get_idx_frame();
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
	std::function<void()> on_finished;
	// ��Դ��
	const std::string name;
	// ��Դ����
	const int num;
};

