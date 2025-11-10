#include "bullet_zmdj.h"

INIT_TYPE_NAME(BulletZmdj);

void BulletZmdj::on_init()
{
	Bullet::on_init();
	set_anchor_mode(AnchorMode::CENTER);
	set_anchor_referent_mode(AnchorMode::TOPLEFT);
	set_enable_angle(true);
	set_angle_anchor_mode(AnchorMode::CENTER);
	set_size(3,3);
	set_damage(1);

	auto img_ptr = TreeNode::create_obj<GameImg>("bullet_img");
	img_ptr->set_position(Vector2(0, 0));
	img_ptr->set_res_name("bullet");
	img_ptr->set_texture_map_type(TextureMapType::AUTO);
	img_ptr->set_anchor_mode(AnchorMode::CENTER);
	img_ptr->set_anchor_referent_mode(AnchorMode::CENTER);
	img = img_ptr;
	add_children(std::move(img_ptr));

	auto hit_obj = get_hit_box()->get_obj_as<GameCollisionBox>();
	hit_obj->set_position(Vector2(0, 0));
	hit_obj->set_size(3,3);
	hit_obj->set_anchor_mode(AnchorMode::CENTER);
	hit_obj->set_anchor_referent_mode(AnchorMode::CENTER);
	hit_obj->set_layer_dst(CollisionLayer::ENEMY);
	hit_obj->set_layer_src(CollisionLayer::NONE);
	hit_obj->set_ID("bul_hit_box");
	hit_obj->set_call_back([&]() {
		set_display(false);
		set_can_remove(true);
		on_hit();
		});
	hit_obj->set_anchor_referent_node(self_node);
	auto* hurt_obj = get_hurt_box()->get_obj_as<GameCollisionBox>();
	hurt_obj->set_collision_enabled(false);
}

void BulletZmdj::on_enter()
{
	Bullet::on_enter();
	auto img_obj = img.lock()->get_obj_as<GameImg>();
	img_obj->set_texture();
	img_obj->init_size();
	speed_move = 1000.0f;

	double radians = getRadiansByAngle(angle);
	velocity.x = (float)std::cos(radians) * speed_move;
	velocity.y = (float)std::sin(radians) * speed_move;

	set_display(true);
	set_can_remove(false);

	auto hit_obj = get_hit_box()->get_obj_as<GameCollisionBox>();
	hit_obj->set_collision_enabled(true);
}
void BulletZmdj::on_exit()
{
	set_display(false);
	auto hit_obj = get_hit_box()->get_obj_as<GameCollisionBox>();
	hit_obj->set_collision_enabled(false);
	Bullet::on_exit();
}
void BulletZmdj::on_input(const SDL_Event& event)
{
	Bullet::on_input(event);
}
void BulletZmdj::on_update(float delta)
{
	Bullet::on_update(delta);
	position += velocity * delta;
	if (!check_in_screen(0))
	{
		valid = false;
	}
}
void BulletZmdj::on_render()
{
	Bullet::on_render();
}