#include "bullet_xcz.h"


BulletXcz::BulletXcz()
{
	//add_children(hit_box);
	set_anchor_mode(AnchorMode::CENTER);
	set_anchor_referent_mode(AnchorMode::CENTER);
	set_res_name("sword");
	set_texture_map_type(TextureMapType::AUTO);
	set_damage(1);
}
BulletXcz::~BulletXcz()
{
}

void BulletXcz::on_enter()
{
	Bullet::on_enter();
	set_center({ (float)size.x / 2, (float)size.y / 2 });
}
void BulletXcz::on_exit()
{
}
void BulletXcz::on_input(const SDL_Event& event)
{
}
void BulletXcz::on_update(float delta)
{
}
void BulletXcz::on_render()
{
	Bullet::on_render();
}