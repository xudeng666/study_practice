#pragma once
#include "game_obj.h"
class GameList :
    public GameObj
{
public:
    GameList() = default;
    GameList(const std::string id);
    GameList(const std::string id, const int num);
    virtual ~GameList();

    DEFINE_TYPE_NAME(GameList);

    virtual void on_init() override;
    virtual void on_enter() override;
    virtual void on_exit() override;
    virtual void on_input(const SDL_Event& event) override;
    virtual void on_update(float delta) override;
    virtual void on_render() override;
    virtual const SDL_Point& get_size() const;
    virtual void children_change();

protected:
    int ranks = 100;                                // 列数（小于1则表示不限）
	TextureMapType map_type = TextureMapType::AUTO; // 图片映射方式
    SDL_Point sub_interval = { 0,0 };               // 子项间隔（宽，高）
};

