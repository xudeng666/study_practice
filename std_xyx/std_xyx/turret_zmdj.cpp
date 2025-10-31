#include "turret_zmdj.h"


INIT_TYPE_NAME(TurretZmdj);

void TurretZmdj::on_init()
{
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
	bf->set_texture_map_type(TextureMapType::AUTO);
	bf->set_anchor_mode(AnchorMode::CENTER);
	bf->set_anchor_referent_mode(AnchorMode::CENTER);
	bf->set_display(false);

	b->add_children(std::move(bi));
	b->add_children(std::move(bf));
	add_children(std::move(b));

	pos_battery = get_center_position();
	std::cout << "炮台中心点位置： " << pos_battery.x<<"    "<< pos_battery.y << std::endl;
}

void TurretZmdj::on_enter()
{
	GameImg::on_enter();
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
		}
		break;
	case SDL_MOUSEBUTTONUP:
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			// 停火
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
}

void TurretZmdj::on_render()
{
	GameImg::on_render();
}