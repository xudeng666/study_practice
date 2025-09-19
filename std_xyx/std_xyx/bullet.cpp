#include "bullet.h"


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
