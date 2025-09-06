#include "bullet_xcz.h"


BulletXcz::BulletXcz()
{
	set_anchor_mode(AnchorMode::CENTER);
	set_anchor_referent_mode(AnchorMode::CENTER);
	set_res_name("sword");
	set_texture_map_type(TextureMapType::AUTO);
	set_damage(1);

	hit_box->set_position({ 0,0 });
	hit_box->set_size({ 6,6 });
	hit_box->set_anchor_mode(AnchorMode::CENTER);
	hit_box->set_anchor_referent_mode(AnchorMode::CENTER);
	hit_box->set_layer_dst(CollisionLayer::ENEMY);
	hit_box->set_layer_src(CollisionLayer::BULLET);
	hit_box->set_ID("hit_box");
	hit_box->set_anchor_referent_obj(this);
	//add_children(hit_box);
}

BulletXcz::~BulletXcz()
{
}

void BulletXcz::on_enter()
{
	Bullet::on_enter();
	set_center({ (float)size.x / 2, (float)size.y / 2 });

	set_display(true);
	hit_box->set_collision_enabled(true);
	hurt_box->set_collision_enabled(false);
}
void BulletXcz::on_exit()
{
	set_display(false);
	hit_box->set_collision_enabled(false);
	hurt_box->set_collision_enabled(false);
	Bullet::on_exit();
}
void BulletXcz::on_input(const SDL_Event& event)
{
	Bullet::on_input(event);
}
void BulletXcz::on_update(float delta)
{
	Bullet::on_update(delta);
}
void BulletXcz::on_render()
{
	Bullet::on_render();
}