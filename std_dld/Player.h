#pragma once
#include "PlayerID.h"
#include "Camera.h"
#include "Animation.h"
#include <graphics.h>



/*玩家基类*/
class Player
{
public:
	Player()
	{
		currentAni = &ani_idle_right;
		position.x = position.y = 0;
	}
    ~Player() = default;

    virtual void on_update(int delta)
    {
		if (is_right_kd != is_left_kd)
		{
			is_face_right = is_right_kd > is_left_kd;
			currentAni = is_face_right ? &ani_run_right : &ani_run_left;
		}
		else
		{
			currentAni = is_face_right ? &ani_idle_right : &ani_idle_left;
		}
		currentAni->on_updata(delta);
    }

    virtual void on_draw(const Camera& camera)
    {
		currentAni->on_draw(camera, (int)position.x, (int)position.y);
    }

    virtual void on_input(const ExMessage& msg)
    {
		switch (msg.message)
		{
		case WM_KEYDOWN:
			switch (id)
			{
			case PlayerID::P1:
				switch (msg.vkcode)
				{
				case 'A':
					is_left_kd = true;
					break;
				case 'D':
					is_right_kd = true;
					break;
				}
				break;
			case PlayerID::P2:
				switch (msg.vkcode)
				{
				case VK_LEFT:
					is_left_kd = true;
					break;
				case VK_RIGHT:
					is_right_kd = true;
					break;
				}
				break;
			}
			break;
		case WM_KEYUP:
			switch (id)
			{
			case PlayerID::P1:
				switch (msg.vkcode)
				{
				case 'A':
					is_left_kd = false;
					break;
				case 'D':
					is_right_kd = false;
					break;
				}
				break;
			case PlayerID::P2:
				switch (msg.vkcode)
				{
				case VK_LEFT:
					is_left_kd = false;
					break;
				case VK_RIGHT:
					is_right_kd = false;
					break;
				}
				break;
			}
			break;
		}
    }

    void setId(PlayerID id)
    {
        this->id = id;
    }

	void setPosition(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	void setFaceRight(bool isRight)
	{
		is_face_right = isRight;
	}

protected:
	Vector2 position;

    Animation ani_idle_left;    // 站立（默认）动画左边
    Animation ani_idle_right;
    Animation ani_run_left;      // 移动动画左边
    Animation ani_run_right;

	Animation* currentAni = nullptr;	// 当前动画

    PlayerID id = PlayerID::P1; // 玩家序号

    bool is_left_kd = false;
    bool is_right_kd = false;

	bool is_face_right = false;
};

