#pragma once
#include "game_obj.h"

class GameImg : public GameObj
{
public:
	GameImg() = default;
	~GameImg() = default;
	GameImg(const Vector2 pos);
	GameImg(const Vector2 pos, const std::string name);

	void on_enter() override;
	void on_update(float delta) override;
	void on_render() override;
	/*���óߴ�*/
	void set_size();
	/*��������*/
	void set_texture();
	/*��ȡ����*/
	SDL_Texture* get_texture();
	/*������Դ*/
	void set_res_name(const std::string name);

protected:
	SDL_Texture* texture = nullptr;
	// ��Դ��
	std::string res_name;
};

