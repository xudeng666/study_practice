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
	virtual void set_size();
	/*���óߴ�*/
	virtual void set_size(const SDL_Point& size) override;
	/*��������*/
	virtual void set_texture();
	/*��ȡ����*/
	SDL_Texture* get_texture();
	/*��������ӳ�䷽ʽ*/
	void set_texture_map_type(TextureMapType type);
	/*��ȡ����ӳ�䷽ʽ*/
	TextureMapType get_texture_map_type();
	/*������Դ*/
	void set_res_name(const std::string name);

protected:
	SDL_Texture* texture = nullptr;
	// ��Դ��
	std::string res_name;
	// ͼƬӳ�䷽ʽ
	TextureMapType map_type = TextureMapType::AUTO;
};

