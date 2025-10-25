#include "enemy_zmdj.h"
#include "event_mgr.h"
#include "game_wnd.h"


INIT_TYPE_NAME(EnemyZmdj);

void EnemyZmdj::on_init()
{
	Character::on_init();

	ani_pool["fast"] = Ani_Res("chicken_fast_", 4);
	ani_pool["mediu"] = Ani_Res("chicken_medium_", 6);
	ani_pool["slow"] = Ani_Res("chicken_slow_", 8);
	ani_pool["die"] = Ani_Res("explosion_", 5);

	click_enabled = false;
	size = { 32,52 };
	anchor_mode = AnchorMode::BOTTOMCENTER;
	anchor_referent_mode = AnchorMode::TOPLEFT;

	auto ani = current_ani.lock()->get_obj_as<GameAni>();
	ani->set_position({ 0,0 });
	ani->set_size({ 32,52 });
	ani->set_anchor_mode(AnchorMode::BOTTOMCENTER);
	ani->set_anchor_referent_mode(AnchorMode::BOTTOMCENTER);
	ani->set_anchor_referent_node(self_node);
	ani->set_ID("enemy_ani");
	ani->set_res_int_val(1);
	ani->set_loop(true);
	ani->set_on_finished([&]() {
			valid = true;
			on_exit();
			// ����ɾ��������Ϣ
			SDL_Event event;
			event.type = EventMgr::instance()->get_event_type(EventType::REDUCE_ENEMY);
			EventData* data = new EventData();
			data->set("node", self_node);
			event.user.data1 = data;
			event.user.data2 = nullptr;
			SDL_PushEvent(&event);
		}); 

	auto hit_obj = hit_box.lock()->get_obj_as<GameCollisionBox>();
	hit_obj->set_collision_enabled(false);

	auto hurt_obj = hurt_box.lock()->get_obj_as<GameCollisionBox>();
	hurt_obj->set_position({ 0,0 });
	hurt_obj->set_size({ 32,52 });
	hurt_obj->set_anchor_mode(AnchorMode::CENTER);
	hurt_obj->set_anchor_referent_mode(AnchorMode::CENTER);
	hurt_obj->set_layer_dst(CollisionLayer::NONE);
	hurt_obj->set_layer_src(CollisionLayer::ENEMY);
	hurt_obj->set_ID("enemy_hurt_box");
	hurt_obj->set_call_back([&]() {
		decrease_hp(1);
		if (!get_alive())
		{
			// �ر���ײ
			hurt_obj->set_collision_enabled(false);
			// �л�Ϊ��������
			ani->set_res_name(ani_pool["die"]);
			ani->set_loop(false);
			ani->set_interval(0.08f);
			// ���͵���������Ϣ
			SDL_Event event;
			event.type = EventMgr::instance()->get_event_type(EventType::ENEMY_DIE);
			event.user.data1 = nullptr;
			event.user.data2 = nullptr;
			SDL_PushEvent(&event);
		}
		});
	hurt_obj->set_anchor_referent_node(self_node);
}

void EnemyZmdj::on_enter()
{
	if (_DE_BUG_)
	{
		//std::cout << ID << "  EnemyZmdj on_enter" << std::endl;
	}
	Character::on_enter();

	// ��ʼ��������Ļ�Ϸ����
	int w = GameWnd::instance()->get_width();
	position = { getRealRand(40.0f, w-40.0f), -50.0f };

	set_enemy_of_type(get_rand_enemy_type());

	hp = 1;
	set_display(true);

	valid = false;
	alive = true;
	
	auto hurt_obj = hurt_box.lock()->get_obj_as<GameCollisionBox>();
	hurt_obj->set_collision_enabled(true);
}

void EnemyZmdj::on_exit()
{
	set_display(false);
	Character::on_exit();
}


void EnemyZmdj::on_input(const SDL_Event& event)
{
}
void EnemyZmdj::on_update(float delta)
{
	if (_DE_BUG_)
	{
		//std::cout << ID << "  on_update" << std::endl;
	}
	Character::on_update(delta);
	if (alive)
	{
		on_move(delta);
	}
}

void EnemyZmdj::on_render()
{
	Character::on_render();
}

void EnemyZmdj::on_move(float delta)
{
	position += velocity * delta;
}

ZmdjEnemyType EnemyZmdj::get_rand_enemy_type()
{
	int val = getIntRand(0, 9);
	if (val < 5)       // 50%
		return ZmdjEnemyType::E_S;
	else if (val < 8)  // 30%
		return ZmdjEnemyType::E_M;
	else                // 20%
		return ZmdjEnemyType::E_F;
}

void EnemyZmdj::set_enemy_of_type(ZmdjEnemyType type)
{
	auto ani = current_ani.lock()->get_obj_as<GameAni>();
	ani->set_loop(true);
	ani->set_interval(0.1f);
	switch (type)
	{
	case ZmdjEnemyType::E_S:
		set_velocity(Vector2(0,30.f));
		ani->set_res_name(ani_pool["slow"]);
		break;
	case ZmdjEnemyType::E_M:
		set_velocity(Vector2(0, 50.f));
		ani->set_res_name(ani_pool["mediu"]);
		break;
	case ZmdjEnemyType::E_F:
		set_velocity(Vector2(0, 80.f));
		ani->set_res_name(ani_pool["fast"]);
		break;
	default:
		break;
	}
}

