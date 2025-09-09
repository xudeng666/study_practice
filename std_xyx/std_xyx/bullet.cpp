#include "bullet.h"
//#include "collision_mgr.h"


Bullet::Bullet()
{
}
Bullet::~Bullet()
{
}

void Bullet::on_enter()
{
	GameObj::on_enter();
}
void Bullet::on_exit()
{
	GameObj::on_exit();
}
void Bullet::on_input(const SDL_Event& event)
{
	GameObj::on_input(event);
}
void Bullet::on_update(float delta)
{
	GameObj::on_update(delta);
}
void Bullet::on_render()
{
	GameObj::on_render();
}
void Bullet::set_velocity(const Vector2& vel)
{
	velocity = vel;
}
const Vector2& Bullet::get_velocity() const
{
	return velocity;
}
/*��ȡ�ƶ��ٶ�*/
void Bullet::set_speed(const float val)
{
	speed_move = val;
}
/*��ȡ�ƶ��ٶ�*/
const float Bullet::get_speed() const
{
	return speed_move;
}
/*�����˺�ֵ*/
void Bullet::set_damage(const int val)
{
	damage = val;
}
/*��ȡ�˺�ֵ*/
const int Bullet::get_damage() const
{
	return damage;
}
/*�����Ƿ���Ч*/
void Bullet::set_valid(bool flag)
{
	valid = flag;
}
/*��ȡ�Ƿ���Ч*/
bool Bullet::get_valid()const
{
	return valid;
}
/*�����Ƿ���Ƴ�*/
void Bullet::set_can_remove(bool flag)
{
	can_remove = flag;
}
/*��ȡ�Ƿ���Ƴ�*/
bool Bullet::check_can_remove()const
{
	return can_remove;
}
