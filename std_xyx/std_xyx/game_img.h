#pragma once

#include "game_obj.h"

class GameImg : public GameObj
{
public:
	GameImg() = default;
	virtual ~GameImg();

	GameImg(const std::string& id) : GameObj(id) {}
	GameImg(const std::string& id, int num) : GameObj(id, num) {}

	DEFINE_TYPE_NAME(GameImg);

	virtual void on_enter() override;
	virtual void on_update(float delta) override;
	virtual void on_render() override;
	/*���óߴ�*/
	virtual void init_size();
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