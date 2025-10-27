#include "turret_zmdj.h"


INIT_TYPE_NAME(TurretZmdj);

void TurretZmdj::on_init()
{
	// ����������Դ���ߴ�
	set_res_name("battery");
	set_position(Vector2(640, 600));
	set_texture_map_type(TextureMapType::AUTO);
	set_anchor_mode(AnchorMode::CENTER);
	set_anchor_referent_mode(AnchorMode::TOPLEFT);



	// �����ڹ�
	auto b = TreeNode::create_obj<GameImg>("barrel");
	barrel = b;
	b->set_res_name("barrel_idle");
	b->set_position(Vector2(-48, 15));
	b->set_texture_map_type(TextureMapType::AUTO);
	b->set_anchor_mode(AnchorMode::TOPLEFT);
	b->set_anchor_referent_mode(AnchorMode::CENTER);
	b->set_center({ 48, 25 });
	b->set_rotation(270.0);
	// �����ڹ�
	auto bf = TreeNode::create_obj<GameAni>("barrel_fire");
	barrel_fire = bf;
	bf->set_res_name(Ani_Res("barrel_fire_",3));
	bf->set_position(Vector2(-48, 15));
	bf->set_texture_map_type(TextureMapType::AUTO);
	bf->set_anchor_mode(AnchorMode::TOPLEFT);
	bf->set_anchor_referent_mode(AnchorMode::CENTER);
	bf->set_center({ 48, 25 });
	// ͼƬ�ڹ�
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