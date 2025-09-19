#include "bullet.h"


void Bullet::set_velocity(const Vector2& vel)
{
	velocity = vel;
}
const Vector2& Bullet::get_velocity() const
{
	return velocity;
}
/*获取移动速度*/
void Bullet::set_speed(const float val)
{
	speed_move = val;
}
/*获取移动速度*/
const float Bullet::get_speed() const
{
	return speed_move;
}
/*设置伤害值*/
void Bullet::set_damage(const int val)
{
	damage = val;
}
/*获取伤害值*/
const int Bullet::get_damage() const
{
	return damage;
}
/*设置是否有效*/
void Bullet::set_valid(bool flag)
{
	valid = flag;
}
/*获取是否有效*/
bool Bullet::get_valid()const
{
	return valid;
}
/*设置是否可移除*/
void Bullet::set_can_remove(bool flag)
{
	can_remove = flag;
}
/*获取是否可移除*/
bool Bullet::check_can_remove()const
{
	return can_remove;
}
