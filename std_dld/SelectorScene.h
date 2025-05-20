#pragma once
#include "Scene.h"
#include "Animation.h"
#include "SceneManager.h"
#include <iostream>

extern IMAGE img_VS;
extern IMAGE img_1P;
extern IMAGE img_2P;
extern IMAGE img_1P_desc;
extern IMAGE img_2P_desc;
extern IMAGE img_gravestone_left;
extern IMAGE img_gravestone_right;
extern IMAGE img_selector_tip;
extern IMAGE img_selector_background;
extern IMAGE img_1P_selector_btn_idle_left;
extern IMAGE img_1P_selector_btn_idle_right;
extern IMAGE img_1P_selector_btn_down_left;
extern IMAGE img_1P_selector_btn_down_right;
extern IMAGE img_2P_selector_btn_idle_left;
extern IMAGE img_2P_selector_btn_idle_right;
extern IMAGE img_2P_selector_btn_down_left;
extern IMAGE img_2P_selector_btn_down_right;
extern IMAGE img_peashooter_selector_background_left;
extern IMAGE img_peashooter_selector_background_right;
extern IMAGE img_sunflower_selector_background_left;
extern IMAGE img_sunflower_selector_background_right;

extern Atlas atlas_peashooter_idle_right;
extern Atlas atlas_sunflower_idle_right;

extern IMAGE img_avatar_peashooter;
extern IMAGE img_avatar_sunflower;

extern SceneManager scene_manager;

/*选取角色场景*/
class SelectorScene :
    public Scene
{
public:
	SelectorScene() = default;
	~SelectorScene() = default;

	/*进入场景初始化*/
	void on_enter()
	{
		ani_peashooter.set_atlas(&atlas_peashooter_idle_right);
		ani_sunflower.set_atlas(&atlas_sunflower_idle_right);
		ani_peashooter.set_interval(100);
		ani_sunflower.set_interval(100);

		static const int OFFSET_X = 50;

		pos_img_VS.x = (getwidth() - img_VS.getwidth()) / 2;
		pos_img_VS.y = (getheight() - img_VS.getheight()) / 2;
		pos_img_tip.x = (getwidth() - img_selector_tip.getwidth()) / 2;
		pos_img_tip.y = getheight() - 125;
		pos_img_1P.x = (getwidth() / 2 - img_1P.getwidth()) / 2 - OFFSET_X;
		pos_img_1P.y = 35;
		pos_img_2P.x = getwidth() / 2 + (getwidth() / 2 - img_2P.getwidth()) / 2 + OFFSET_X;
		pos_img_2P.y = pos_img_1P.y;
		pos_img_1P_desc.x = (getwidth() / 2 - img_1P_desc.getwidth()) / 2 - OFFSET_X;
		pos_img_1P_desc.y = getheight() - 150;
		pos_img_2P_desc.x = getwidth() / 2 + (getwidth() / 2 - img_2P_desc.getwidth()) / 2 + OFFSET_X;
		pos_img_2P_desc.y = pos_img_1P_desc.y;
		pos_img_1P_gravestone.x = (getwidth() / 2 - img_gravestone_right.getwidth()) / 2 - OFFSET_X;
		pos_img_1P_gravestone.y = pos_img_1P.y + img_1P.getheight() + 35;
		pos_img_2P_gravestone.x = getwidth() / 2 + (getwidth() / 2 - img_gravestone_left.getwidth()) / 2 + OFFSET_X;
		pos_img_2P_gravestone.y = pos_img_1P_gravestone.y;
		pos_ani_1P.x = (getwidth() / 2 - atlas_peashooter_idle_right.getImageByIndex(0)->getwidth()) / 2 - OFFSET_X;
		pos_ani_1P.y = pos_img_1P_gravestone.y + 80;
		pos_ani_2P.x = getwidth() / 2 + (getwidth() / 2 - atlas_peashooter_idle_right.getImageByIndex(0)->getwidth()) / 2 + OFFSET_X;
		pos_ani_2P.y = pos_ani_1P.y;
		pos_img_1P_name.y = pos_ani_1P.y + 100;
		pos_img_2P_name.y = pos_img_1P_name.y;
		pos_1P_selector_btn_left.x = pos_img_1P_gravestone.x - img_1P_selector_btn_idle_left.getwidth();
		pos_1P_selector_btn_left.y = pos_img_1P_gravestone.y + (img_gravestone_right.getheight() - img_1P_selector_btn_idle_left.getheight()) / 2;
		pos_1P_selector_btn_right.x = pos_img_1P_gravestone.x + img_gravestone_right.getwidth();
		pos_1P_selector_btn_right.y = pos_1P_selector_btn_left.y;
		pos_2P_selector_btn_left.x = pos_img_2P_gravestone.x - img_2P_selector_btn_idle_left.getwidth();
		pos_2P_selector_btn_left.y = pos_1P_selector_btn_left.y;
		pos_2P_selector_btn_right.x = pos_img_2P_gravestone.x + img_gravestone_left.getwidth();
		pos_2P_selector_btn_right.y = pos_1P_selector_btn_left.y;

		//pos_text_1p_name.x = pos_ani_1P.x 
	}
	/*处理数据*/
	void on_update(int delta)
	{
		ani_peashooter.on_updata(delta);
		ani_sunflower.on_updata(delta);

		selector_back_scorll_x += 4;
		if (selector_back_scorll_x > img_peashooter_selector_background_left.getwidth())
			selector_back_scorll_x = 0;

		
	}
	/*用于渲染绘图*/
	void on_draw(const Camera& camera)
	{
		IMAGE* img_p1_back = nullptr;
		IMAGE* img_p2_back = nullptr;

		switch (player_type_2)
		{
		case PlayerType::Peashooter:
			img_p2_back = &img_sunflower_selector_background_left;
			break;
		case PlayerType::Sunflower:
			img_p2_back = &img_peashooter_selector_background_left;
			break;
		default:
			break;
		}
		switch (player_type_1)
		{
		case PlayerType::Peashooter:
			img_p1_back = &img_sunflower_selector_background_right;
			break;
		case PlayerType::Sunflower:
			img_p1_back = &img_peashooter_selector_background_right;
			break;
		default:
			break;
		}

		putimage(0, 0, &img_selector_background);

		putimage_alpha(selector_back_scorll_x - img_p1_back->getwidth(), 0, img_p1_back);
		putimage_alpha(selector_back_scorll_x, 0, img_p1_back->getwidth() - selector_back_scorll_x, 0, img_p1_back, 0, 0);
		putimage_alpha(getwidth() - img_p2_back->getwidth(), 0, img_p2_back->getwidth() - selector_back_scorll_x, 0, img_p2_back, selector_back_scorll_x, 0);
		putimage_alpha(getwidth() - selector_back_scorll_x, 0, img_p2_back);

		putimage_alpha(pos_img_VS.x, pos_img_VS.y, &img_VS);

		putimage_alpha(pos_img_1P.x, pos_img_1P.y, &img_1P);
		putimage_alpha(pos_img_2P.x, pos_img_2P.y, &img_2P);
		putimage_alpha(pos_img_1P_gravestone.x, pos_img_1P_gravestone.y, &img_gravestone_right);
		putimage_alpha(pos_img_2P_gravestone.x, pos_img_2P_gravestone.y, &img_gravestone_left);

		switch (player_type_1)
		{
		case PlayerType::Peashooter:
			ani_peashooter.on_draw(camera, pos_ani_1P.x, pos_ani_1P.y);
			pos_img_1P_name.x = pos_img_1P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_peashooter_name)) / 2;
			outtextxy_shaded(pos_img_1P_name.x, pos_img_1P_name.y + 50, str_peashooter_name);
			break;
		case PlayerType::Sunflower:
			ani_sunflower.on_draw(camera, pos_ani_1P.x, pos_ani_1P.y);
			pos_img_1P_name.x = pos_img_1P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_sunflower_name)) / 2;
			outtextxy_shaded(pos_img_1P_name.x, pos_img_1P_name.y + 50, str_sunflower_name);
			break;
		}

		switch (player_type_2)
		{
		case PlayerType::Peashooter:
			ani_peashooter.on_draw(camera, pos_ani_2P.x, pos_ani_2P.y);
			pos_img_2P_name.x = pos_img_2P_gravestone.x + (img_gravestone_left.getwidth() - textwidth(str_peashooter_name)) / 2;
			outtextxy_shaded(pos_img_2P_name.x, pos_img_2P_name.y + 50, str_peashooter_name);
			break;
		case PlayerType::Sunflower:
			ani_sunflower.on_draw(camera, pos_ani_2P.x, pos_ani_2P.y);
			pos_img_2P_name.x = pos_img_2P_gravestone.x + (img_gravestone_left.getwidth() - textwidth(str_sunflower_name)) / 2;
			outtextxy_shaded(pos_img_2P_name.x, pos_img_2P_name.y + 50, str_sunflower_name);
			break;
		}

		putimage_alpha(pos_1P_selector_btn_left.x, pos_1P_selector_btn_left.y,
			is_btn_1p_ldown ? &img_1P_selector_btn_down_left : &img_1P_selector_btn_idle_left);
		putimage_alpha(pos_1P_selector_btn_right.x, pos_1P_selector_btn_right.y,
			is_btn_1p_rdown ? &img_1P_selector_btn_down_right : &img_1P_selector_btn_idle_right);
		putimage_alpha(pos_2P_selector_btn_left.x, pos_2P_selector_btn_left.y,
			is_btn_2p_ldown ? &img_2P_selector_btn_down_left : &img_2P_selector_btn_idle_left);
		putimage_alpha(pos_2P_selector_btn_right.x, pos_2P_selector_btn_right.y,
			is_btn_2p_rdown ? &img_2P_selector_btn_down_right : &img_2P_selector_btn_idle_right);

		putimage_alpha(camera, pos_img_1P_desc.x, pos_img_1P_desc.y, &img_1P_desc);
		putimage_alpha(camera, pos_img_2P_desc.x, pos_img_2P_desc.y, &img_2P_desc);

		putimage_alpha(camera, pos_img_tip.x, pos_img_tip.y, &img_selector_tip);


	}
	/*处理玩家输入*/
	void on_input(const ExMessage& msg)
	{
		switch (msg.message)
		{
		case WM_KEYDOWN:
			switch (msg.vkcode)
			{
			case 'A':
				is_btn_1p_ldown = true;
				break;
			case 'D':
				is_btn_1p_rdown = true;
				break;
			case VK_LEFT:
				is_btn_2p_ldown = true;
				break;
			case VK_RIGHT:
				is_btn_2p_rdown = true;
				break;
			default:
				break;
			}
			break;
		case WM_KEYUP:
			switch (msg.vkcode)
			{
			case 'A':
				is_btn_1p_ldown = false;
				player_type_1 = (PlayerType)(((int)PlayerType::Invalid + (int)player_type_1 - 1) % (int)PlayerType::Invalid);
				mciSendString(_T("play ui_switch from 0"), nullptr, 0, nullptr);
				break;
			case 'D':
				is_btn_1p_rdown = false;
				player_type_1 = (PlayerType)(((int)PlayerType::Invalid + (int)player_type_1 + 1) % (int)PlayerType::Invalid);
				mciSendString(_T("play ui_switch from 0"), nullptr, 0, nullptr);
				break;
			case VK_LEFT:
				is_btn_2p_ldown = false;
				player_type_2 = (PlayerType)(((int)PlayerType::Invalid + (int)player_type_2 - 1) % (int)PlayerType::Invalid);
				mciSendString(_T("play ui_switch from 0"), nullptr, 0, nullptr);
				break;
			case VK_RIGHT:
				is_btn_2p_rdown = false;
				player_type_2 = (PlayerType)(((int)PlayerType::Invalid + (int)player_type_2 + 1) % (int)PlayerType::Invalid);
				mciSendString(_T("play ui_switch from 0"), nullptr, 0, nullptr);
				break;
			case VK_RETURN:
				scene_manager.exchange_scene(SceneManager::SceneType::Game);
				mciSendString(_T("play ui_confirm from 0"), nullptr, 0, nullptr);
			default:
				break;
			}
			break;
		}
	}
	/*退出游戏场景*/
	void on_exit()
	{
		std::cout << "退出选角界面" << std::endl;
	}
private:
	enum class PlayerType
	{
		Peashooter = 0,
		Sunflower,
		Invalid	//用来计数枚举总数，不实际参与使用
	};

private:
	POINT pos_img_VS = { 0 };
	POINT pos_img_tip = { 0 };
	POINT pos_img_1P = { 0 };
	POINT pos_img_2P = { 0 };
	POINT pos_img_1P_desc = { 0 };
	POINT pos_img_2P_desc = { 0 };
	POINT pos_img_1P_name = { 0 };
	POINT pos_img_2P_name = { 0 };
	POINT pos_ani_1P = { 0 };
	POINT pos_ani_2P = { 0 };
	POINT pos_img_1P_gravestone = { 0 };
	POINT pos_img_2P_gravestone = { 0 };
	POINT pos_1P_selector_btn_left = { 0 };
	POINT pos_1P_selector_btn_right = { 0 };
	POINT pos_2P_selector_btn_left = { 0 };
	POINT pos_2P_selector_btn_right = { 0 };

	Animation ani_peashooter;
	Animation ani_sunflower;
	// 角色类型
	PlayerType player_type_1 = PlayerType::Peashooter;
	PlayerType player_type_2 = PlayerType::Sunflower;
	//角色名
	LPCTSTR str_peashooter_name = _T("婉逗射手");	
	LPCTSTR str_sunflower_name = _T("龙日葵");

	int selector_back_scorll_x = 0;	//滚动距离

	bool is_btn_1p_rdown = false;
	bool is_btn_1p_ldown = false;
	bool is_btn_2p_rdown = false;
	bool is_btn_2p_ldown = false;

private:
	/*阴影效果*/
	void outtextxy_shaded(int x, int y, LPCTSTR str)
	{
		settextcolor(RGB(45, 45, 45));		//设定阴影颜色
		outtextxy(x + 3, y + 3, str);		//设定阴影位置
		settextcolor(RGB(255, 255, 255));	//设定正文颜色
		outtextxy(x, y, str);				//设定正文位置
	}
};

