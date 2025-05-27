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
extern IMAGE img_1P_winnner;							// 1P 获胜文本图片
extern IMAGE img_2P_winnner;							// 2P 获胜文本图片
extern IMAGE img_winnner_bar;							// 获胜玩家文本背景图片

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
		is_game_over = false;
		is_win_out = false;

		pos_img_win_bg.x = -img_winnner_bar.getwidth();
		pos_img_win_bg.y = (getheight() - img_winnner_bar.getheight()) / 2;
		pos_x_win_bg_dst = (getwidth() - img_winnner_bar.getwidth()) / 2;

		pos_img_win_text.x = pos_img_win_bg.x;
		pos_img_win_text.y = (getheight() - img_1P_winnner.getheight()) / 2;
		pos_x_win_text_dst = (getwidth() - img_1P_winnner.getwidth()) / 2;

		timer_win_in.restart();
		timer_win_in.set_wait_time(2500);
		timer_win_in.set_one_shot(true);
		timer_win_in.set_callback([&](){is_win_out = true;});

		timer_win_out.restart();
		timer_win_out.set_wait_time(1000);
		timer_win_out.set_one_shot(true);
		timer_win_out.set_callback([&]() {scene_manager.exchange_scene(SceneManager::SceneType::Menu);});

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

		mciSendString(_T("play bgm_game repeat from 0"), nullptr, 0, nullptr);
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

		const Vector2& pos_1 = player_1->getPosition();
		const Vector2& pos_2 = player_2->getPosition();
		if (pos_1.y >= getheight())
		{
			player_1->set_hp(0);
		}
		if (pos_2.y >= getheight())
		{
			player_2->set_hp(0);
		}

		int hp_1 = player_1->get_hp();
		int hp_2 = player_2->get_hp();
		player_bar1.set_hp(player_1->get_hp());
		player_bar1.set_mp(player_1->get_mp());
		player_bar2.set_hp(player_2->get_hp());
		player_bar2.set_mp(player_2->get_mp());

		if (player_1->get_hp() <= 0 || player_2->get_hp() <= 0)
		{
			if (!is_game_over)
			{
				mciSendString(_T("stop bgm_game"), nullptr, 0, nullptr);
				mciSendString(_T("play ui_win from 0"), nullptr, 0, nullptr);
			}
			is_game_over = true;
		}

		if (is_game_over)
		{
			pos_img_win_bg.x += speed_win_bg * delta;
			pos_img_win_text.x += speed_win_text * delta;

			if (is_win_out)
			{
				timer_win_out.on_update(delta);
			}
			else
			{
				timer_win_in.on_update(delta);
				if (pos_img_win_bg.x > pos_x_win_bg_dst)
				{
					pos_img_win_bg.x = pos_x_win_bg_dst;
				}
				if (pos_img_win_text.x > pos_x_win_text_dst)
				{
					pos_img_win_text.x = pos_x_win_text_dst;
				}
			}
		}
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

		if (is_game_over)
		{
			putimage_alpha(pos_img_win_bg.x, pos_img_win_bg.y, &img_winnner_bar);
			putimage_alpha(pos_img_win_text.x, pos_img_win_text.y, player_1->get_hp() > 0 ? &img_1P_winnner : &img_2P_winnner);
		}
		else
		{
			player_bar1.on_draw();
			player_bar2.on_draw();
		}
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
		player_1 = nullptr;
		player_2 = nullptr;
		is_debug = false;
		bullet_list.clear();
		main_camera.reset_position();
		mciSendString(_T("stop bgm_game"), nullptr, 0, nullptr);
	}
private:
	const float speed_win_bg = 3.0f;
	const float speed_win_text = 1.5f;
private:
	POINT pos_img_sky = { 0 };
	POINT pos_img_hills = { 0 };

	StatusBar player_bar1;
	StatusBar player_bar2;

	bool is_game_over = false;

	POINT pos_img_win_bg = { 0 };
	POINT pos_img_win_text = { 0 };
	int pos_x_win_bg_dst = 0;
	int pos_x_win_text_dst = 0;
	Timer timer_win_in;
	Timer timer_win_out;
	bool is_win_out = false;
	IMAGE* img_win = nullptr;
};

