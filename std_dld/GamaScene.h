#pragma once
#include "util.h"
#include "StatusBar.h"
#include "Player.h"
#include "Platform.h"
#include "Scene.h"
#include "SceneManager.h"
#include <iostream>

extern IMAGE img_sky;									// 天空图片
extern IMAGE img_hills;									// 山脉图片
extern IMAGE img_platform_large;						// 大型平台图片
extern IMAGE img_platform_small;						// 小型平台图片

extern Camera main_camera;
extern std::vector<Platform> platform_list;

extern SceneManager scene_manager;

extern Player* player_1;
extern Player* player_2;
extern IMAGE* img_head_player_1;
extern IMAGE* img_head_player_2;


/*游戏场景*/
class GamaScene :
    public Scene
{
public:
	GamaScene() = default;
	~GamaScene() = default;

	/*进入场景初始化*/
	void on_enter()
	{
		player_1->setFaceRight(true);
		player_2->setFaceRight(false);
		player_1->setPosition(200, 50);
		player_2->setPosition(975, 50);

		pos_img_sky.x = (getwidth() - img_sky.getwidth()) / 2;
		pos_img_sky.y = (getheight() - img_sky.getheight()) / 2;
		pos_img_hills.x = (getwidth() - img_hills.getwidth()) / 2;
		pos_img_hills.y = (getheight() - img_hills.getheight()) / 2;

		platform_list.resize(4);

		Platform& large_platform = platform_list[0];
		large_platform.img = &img_platform_large;
		large_platform.render_pos.x = 122;
		large_platform.render_pos.y = 455;
		large_platform.shape.left = (float)large_platform.render_pos.x + 30;
		large_platform.shape.right = (float)large_platform.render_pos.x + img_platform_large.getwidth() - 30;
		large_platform.shape.y = (float)large_platform.render_pos.y + 60;

		Platform& small_platform_1 = platform_list[1];
		small_platform_1.img = &img_platform_small;
		small_platform_1.render_pos.x = 175;
		small_platform_1.render_pos.y = 360;
		small_platform_1.shape.left = (float)small_platform_1.render_pos.x + 40;
		small_platform_1.shape.right = (float)small_platform_1.render_pos.x + img_platform_small.getwidth() - 40;
		small_platform_1.shape.y = (float)small_platform_1.render_pos.y + img_platform_small.getheight() / 2;

		Platform& small_platform_2 = platform_list[2];
		small_platform_2.img = &img_platform_small;
		small_platform_2.render_pos.x = 855;
		small_platform_2.render_pos.y = 360;
		small_platform_2.shape.left = (float)small_platform_2.render_pos.x + 40;
		small_platform_2.shape.right = (float)small_platform_2.render_pos.x + img_platform_small.getwidth() - 40;
		small_platform_2.shape.y = (float)small_platform_2.render_pos.y + img_platform_small.getheight() / 2;

		Platform& small_platform_3 = platform_list[3];
		small_platform_3.img = &img_platform_small;
		small_platform_3.render_pos.x = 515;
		small_platform_3.render_pos.y = 225;
		small_platform_3.shape.left = (float)small_platform_3.render_pos.x + 40;
		small_platform_3.shape.right = (float)small_platform_3.render_pos.x + img_platform_small.getwidth() - 40;
		small_platform_3.shape.y = (float)small_platform_3.render_pos.y + img_platform_small.getheight() / 2;

		player_bar1.set_head(img_head_player_1);
		player_bar2.set_head(img_head_player_2);

		player_bar1.set_position(200, 620);
		player_bar2.set_position(694, 620);
	}
	/*处理数据*/
	void on_update(int delta)
	{
		player_1->on_update(delta);
		player_2->on_update(delta);

		main_camera.on_update(delta);

		bullet_list.erase(std::remove_if(
			bullet_list.begin(), bullet_list.end(),
			[](const Bullet* bullet)
			{
				bool del = bullet->check_can_remove();
				if (del) delete bullet;
				return del;
			}), bullet_list.end());

		for (Bullet* bullet : bullet_list)
		{
			bullet->on_update(delta);
		}

		player_bar1.set_hp(player_1->get_hp());
		player_bar1.set_mp(player_1->get_mp());
		player_bar2.set_hp(player_2->get_hp());
		player_bar2.set_mp(player_2->get_mp());
	}
	/*用于渲染绘图*/
	void on_draw(const Camera& camera)
	{
		putimage_alpha(camera, pos_img_sky.x, pos_img_sky.y, &img_sky);
		putimage_alpha(camera, pos_img_hills.x, pos_img_hills.y, &img_hills);

		for (const Platform& platform : platform_list)
		{
			platform.on_draw(camera);
		}
		
		if (is_debug)
		{
			settextcolor(RGB(255, 0, 0));
			outtextxy(0,0, _T("已开启调试模式，按‘Q’键关闭"));
		}

		player_1->on_draw(camera);
		player_2->on_draw(camera);

		for (const Bullet* bullet : bullet_list)
		{
			bullet->on_draw(camera);
		}

		player_bar1.on_draw();
		player_bar2.on_draw();
	}
	/*处理玩家输入*/
	void on_input(const ExMessage& msg)
	{
		player_1->on_input(msg);
		player_2->on_input(msg);

		if (msg.message == WM_KEYUP)
		{
			switch (msg.vkcode)
			{
			case 'Q':
				is_debug = !is_debug;
				break;
			default:
				break;
			}
		}
	}
	/*退出游戏场景*/
	void on_exit()
	{
	}
private:
	POINT pos_img_sky = { 0 };
	POINT pos_img_hills = { 0 };

	StatusBar player_bar1;
	StatusBar player_bar2;
};

