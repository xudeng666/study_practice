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
	/*设置尺寸*/
	virtual void set_size();
	/*设置尺寸*/
	virtual void set_size(const SDL_Point& size) override;
	/*设置纹理*/
	virtual void set_texture();
	/*获取纹理*/
	SDL_Texture* get_texture();
	/*设置纹理映射方式*/
	void set_texture_map_type(TextureMapType type);
	/*获取纹理映射方式*/
	TextureMapType get_texture_map_type();
	/*设置资源*/
	void set_res_name(const std::string name);

protected:
	SDL_Texture* texture = nullptr;
	// 资源名
	std::string res_name;
	// 图片映射方式
	TextureMapType map_type = TextureMapType::AUTO;
};

