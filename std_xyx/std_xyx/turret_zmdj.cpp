#include "turret_zmdj.h"

#include "game_wnd.h"
#include "res_mgr.h"
#include "event_mgr.h"

#include "assert.h"


INIT_TYPE_NAME(TurretZmdj);

void TurretZmdj::on_init()
{
	GameImg::on_init();
	// 设置自身资源、尺寸
	set_res_name("battery");
	set_position(Vector2(0, -120));
	set_texture_map_type(TextureMapType::AUTO);
	set_anchor_mode(AnchorMode::CENTER);
	set_anchor_referent_mode(AnchorMode::BOTTOMCENTER);

	// 炮管
	auto b = TreeNode::create_obj<GameObj>("barrel");
	barrel = b;
	b->set_position(Vector2(77, 10));
	b->set_size({ 250, 50 });
	b->set_anchor_mode(AnchorMode::CENTER);
	b->set_anchor_referent_mode(AnchorMode::CENTER);
	b->set_center({ -77, 0 });
	b->set_angle_anchor_mode(AnchorMode::CENTER);
	b->set_rotation(-90);
	b->set_enable_angle(true);
	// 图片炮管
	auto bi = TreeNode::create_obj<GameImg>("barrel_idle");
	barrel_img = bi;
	bi->set_res_name("barrel_idle");
	bi->set_texture_map_type(TextureMapType::AUTO);
	bi->set_anchor_mode(AnchorMode::CENTER);
	bi->set_anchor_referent_mode(AnchorMode::CENTER);
	bi->set_display(true);
	// 动画炮管
	auto bf = TreeNode::create_obj<GameAni>("barrel_fire");
	barrel_ani = bf;
	bf->set_res_name(Ani_Res("barrel_fire_",3));
	bf->set_res_int_val(1);
	bf->set_size({ 250, 50 });
	bf->set_texture_map_type(TextureMapType::AUTO);
	bf->set_anchor_mode(AnchorMode::CENTER);
	bf->set_anchor_referent_mode(AnchorMode::CENTER);
	bf->set_display(false);
	bf->set_on_finished([&]() {
		is_cool_down = true;
		});
	bf->set_loop(false);
	bf->set_interval(barrel_speed);


	b->add_children(std::move(bi));
	b->add_children(std::move(bf));
	add_children(std::move(b));
}

void TurretZmdj::on_enter()
{
	GameImg::on_enter();
	auto b = barrel.lock();
	if (b)
	{
		pos_battery = b->get_rotatio_center_position();
	}
}

void TurretZmdj::on_exit()
{
	GameImg::on_exit();
}

void TurretZmdj::on_input(const SDL_Event& event)
{
	GameImg::on_input(event);
	
	switch (event.type)
	{
	case SDL_MOUSEMOTION:
	{
		SDL_Point p = { event.motion.x,event.motion.y };
		// 炮塔转动
		auto b = barrel.lock();
		if (b)
		{
			Vector2 m = { (float)event.motion.x ,(float)event.motion.y };
			Vector2 cc = m - pos_battery;
			b->set_rotation(getAngleByRadians(std::atan2(cc.y, cc.x)));
		}
	}
	break;
	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			// 开火
			is_fire_key_down = true;
		}
		break;
	case SDL_MOUSEBUTTONUP:
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			// 停火
			is_fire_key_down = false;
		}
		break;
	}
}
void TurretZmdj::on_update(float delta)
{
	if (_DE_BUG_)
	{
		//std::cout << ID << "  on_update" << std::endl;
	}
	GameImg::on_update(delta);

	open_fire(delta);
}

void TurretZmdj::on_render()
{
	GameImg::on_render();
}

void TurretZmdj::open_fire(float delta)
{
	auto img = barrel_img.lock();
	auto aa = barrel_ani.lock();
	if (!img || !aa)
	{
		assert(false && "未知原因无法成功获取对象");
	}
	auto ani = aa->get_obj_as<GameAni>();
	if (!is_cool_down)
	{
		GameWnd::instance()->get_camera()->shake(3.0f, 0.1f);
		ani->on_update(delta);
	}

	if (is_cool_down && is_fire_key_down)
	{
		ani->set_display(true);
		img->set_display(false);

		ani->reset();
		is_cool_down = false;

		// 计算子弹出生位置
		double b_angle = getIntRand(-2, 2);  // 在 5°范围内随机偏移
		auto b = barrel.lock();
		if (b)
		{
			b_angle += b->get_angle();
		}
		double radians = getRadiansByAngle(b_angle);
		Vector2 b_pos = { (float)std::cos(radians), (float)sin(radians) };
		b_pos += pos_battery;
		// 发送子弹生成事件
		SDL_Event event;
		event.type = EventMgr::instance()->get_event_type(EventType::LAUNCH_BULLET);
		EventData* data = new EventData();
		data->set("postion", b_pos);
		data->set("angle", b_angle);
		event.user.data1 = data;
		event.user.data2 = nullptr;
		SDL_PushEvent(&event);
		// 播放开火音效
		std::string n = "audio_fire_" + std::to_string(getIntRand(1, 3));
		Mix_PlayChannel(-1, ResMgr::instance()->find_audio(n), 0);
	}
	else
	{
		ani->set_display(false);
		img->set_display(true);
	}

	GameWnd::instance()->get_camera()->on_update(delta);
}