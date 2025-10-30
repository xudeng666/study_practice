#include "bullet_xcz.h"

INIT_TYPE_NAME(BulletXcz);

void BulletXcz::on_init()
{
	Bullet::on_init();
	set_anchor_mode(AnchorMode::CENTER);
	set_anchor_referent_mode(AnchorMode::CENTER);
	set_enable_angle(true);
	set_angle_anchor_mode(AnchorMode::CENTER);
	set_damage(1);

	auto img_ptr = TreeNode::create_obj<GameImg>("bullet_img");
	img_ptr->set_position(Vector2(0, 0));
	img_ptr->set_res_name("sword");
	img_ptr->set_texture_map_type(TextureMapType::AUTO);
	img_ptr->set_anchor_mode(AnchorMode::CENTER);
	img_ptr->set_anchor_referent_mode(AnchorMode::CENTER);
	img = img_ptr;
	add_children(std::move(img_ptr));

	auto hit_obj = get_hit_box()->get_obj_as<GameCollisionBox>();
	hit_obj->set_position(Vector2(0, 0));
	hit_obj->set_size({ 6,6 });
	hit_obj->set_anchor_mode(AnchorMode::CENTER);
	hit_obj->set_anchor_referent_mode(AnchorMode::CENTER);
	hit_obj->set_layer_dst(CollisionLayer::ENEMY);
	hit_obj->set_layer_src(CollisionLayer::NONE);
	hit_obj->set_ID("bul_hit_box");
	hit_obj->set_call_back([&]() {on_hit();});
	hit_obj->set_anchor_referent_node(self_node);
	auto* hurt_obj = get_hurt_box()->get_obj_as<GameCollisionBox>();
	hurt_obj->set_collision_enabled(false);
}

void BulletXcz::on_enter()
{
	Bullet::on_enter();
	auto img_obj = img.lock()->get_obj_as<GameImg>();
	img_obj->set_texture();
	img_obj->init_size();

	set_display(true);
	auto hit_obj = get_hit_box()->get_obj_as<GameCollisionBox>();
	hit_obj->set_collision_enabled(true);
}
void BulletXcz::on_exit()
{
	set_display(false);
	auto hit_obj = get_hit_box()->get_obj_as<GameCollisionBox>();
	hit_obj->set_collision_enabled(false);
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