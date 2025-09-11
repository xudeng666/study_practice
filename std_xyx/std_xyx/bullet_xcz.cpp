#include "bullet_xcz.h"


BulletXcz::BulletXcz()
{
	set_anchor_mode(AnchorMode::CENTER);
	set_anchor_referent_mode(AnchorMode::CENTER);
	set_damage(1);

	auto img_ptr = std::make_unique<GameImg>(Vector2(0, 0));
	img = img_ptr.get();
	img->set_res_name("sword");
	img->set_texture_map_type(TextureMapType::AUTO);
	img->set_anchor_mode(AnchorMode::CENTER);
	img->set_anchor_referent_mode(AnchorMode::CENTER);
	add_children(std::move(img_ptr));

	hit_box->set_position({ 0,0 });
	hit_box->set_size({ 6,6 });
	hit_box->set_anchor_mode(AnchorMode::CENTER);
	hit_box->set_anchor_referent_mode(AnchorMode::CENTER);
	hit_box->set_layer_dst(CollisionLayer::ENEMY);
	hit_box->set_layer_src(CollisionLayer::NONE);
	hit_box->set_ID("bul_hit_box");
	hit_box->set_call_back([&]() {on_hit();});
	hit_box->set_anchor_referent_obj(this);
}

BulletXcz::~BulletXcz()
{
}

void BulletXcz::on_enter()
{
	Bullet::on_enter();
	img->set_texture();
	img->set_size();
	Vector2 p = img->get_anchor_position(AnchorMode::CENTER) - img->get_anchor_position(AnchorMode::TOPLEFT);
	img->set_center({p.x, p.y});

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