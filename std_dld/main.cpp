/*��Ϸ----���Ҷ�*/
#include "Bullet.h"
#include "Player.h"
#include "Platform.h"
#include "MenuScene.h"
#include "GamaScene.h"
#include "SelectorScene.h"
#include "SceneManager.h"

#pragma comment(lib, "Winmm.lib")

bool is_debug = false;


IMAGE img_menu_background;						// ���˵�����ͼƬ

IMAGE img_VS;									// VS ������ͼƬ
IMAGE img_1P;									// 1P �ı�ͼƬ
IMAGE img_2P;									// 2P �ı�ͼƬ
IMAGE img_1P_desc;								// 1P ��λ����ͼƬ
IMAGE img_2P_desc;								// 2P ��λ����ͼƬ
IMAGE img_gravestone_left;						// �������Ĺ��ͼƬ
IMAGE img_gravestone_right;						// �����ҵ�Ĺ��ͼƬ
IMAGE img_selector_tip;							// ѡ�ǽ�����ʾ��Ϣ�ı�ͼƬ
IMAGE img_selector_background;					// ѡ�ǽ��汳��ͼƬ
IMAGE img_1P_selector_btn_idle_left;			// 1P ����ѡ��ťĬ��״̬ͼƬ
IMAGE img_1P_selector_btn_idle_right;			// 1P ����ѡ��ťĬ��״̬ͼƬ
IMAGE img_1P_selector_btn_down_left;			// 1P ����ѡ��ť����״̬ͼƬ
IMAGE img_1P_selector_btn_down_right;			// 1P ����ѡ��ť����״̬ͼƬ
IMAGE img_2P_selector_btn_idle_left;			// 2P ����ѡ��ťĬ��״̬ͼƬ
IMAGE img_2P_selector_btn_idle_right;			// 2P ����ѡ��ťĬ��״̬ͼƬ
IMAGE img_2P_selector_btn_down_left;			// 2P ����ѡ��ť����״̬ͼƬ
IMAGE img_2P_selector_btn_down_right;			// 2P ����ѡ��ť����״̬ͼƬ
IMAGE img_peashooter_selector_background_left;  // ѡ�ǽ��泯������㶹���ֱ���ͼƬ
IMAGE img_peashooter_selector_background_right; // ѡ�ǽ��泯���ҵ��㶹���ֱ���ͼƬ
IMAGE img_sunflower_selector_background_left;   // ѡ�ǽ��泯��������տ�����ͼƬ
IMAGE img_sunflower_selector_background_right;  // ѡ�ǽ��泯���ҵ����տ�����ͼƬ

IMAGE img_sky;									// ���ͼƬ
IMAGE img_hills;								// ɽ��ͼƬ
IMAGE img_platform_large;						// ����ƽ̨ͼƬ
IMAGE img_platform_small;						// С��ƽ̨ͼƬ

IMAGE img_1P_cursor;							// 1P ָʾ���ͼƬ
IMAGE img_2P_cursor;							// 2P ָʾ���ͼƬ

Atlas atlas_peashooter_idle_left;				// �㶹���ֳ������Ĭ�϶���ͼ��
Atlas atlas_peashooter_idle_right;				// �㶹���ֳ����ҵ�Ĭ�϶���ͼ��
Atlas atlas_peashooter_run_left;				// �㶹���ֳ�����ı��ܶ���ͼ��
Atlas atlas_peashooter_run_right;				// �㶹���ֳ����ҵı��ܶ���ͼ��
Atlas atlas_peashooter_attack_ex_left;			// �㶹���ֳ���������⹥������ͼ��
Atlas atlas_peashooter_attack_ex_right;			// �㶹���ֳ����ҵ����⹥������ͼ��
Atlas atlas_peashooter_die_left;				// �㶹���ֳ��������������ͼ��
Atlas atlas_peashooter_die_right;				// �㶹���ֳ����ҵ���������ͼ��

Atlas atlas_sunflower_idle_left;				// ���տ��������Ĭ�϶���ͼ��
Atlas atlas_sunflower_idle_right;				// ���տ������ҵ�Ĭ�϶���ͼ��
Atlas atlas_sunflower_run_left;					// ���տ�������ı��ܶ���ͼ��
Atlas atlas_sunflower_run_right;				// ���տ������ҵı��ܶ���ͼ��
Atlas atlas_sunflower_attack_ex_left;			// ���տ�����������⹥������ͼ��
Atlas atlas_sunflower_attack_ex_right;			// ���տ������ҵ����⹥������ͼ��
Atlas atlas_sunflower_die_left;					// ���տ����������������ͼ��
Atlas atlas_sunflower_die_right;				// ���տ������ҵ���������ͼ��

IMAGE img_pea;									// �㶹ͼƬ

Atlas atlas_pea_break;							// �㶹���鶯��ͼ��
Atlas atlas_sun;								// �չ⶯��ͼ��
Atlas atlas_sun_explode;						// �չⱬը����ͼ��
Atlas atlas_sun_ex;								// �����չ⶯��ͼ��
Atlas atlas_sun_ex_explode;						// �����չⱬը����ͼ��
Atlas atlas_sun_text;							// ���ա� �ı�����ͼ�� 

Atlas atlas_run_effect;							// ������Ч����ͼ��
Atlas atlas_jump_effect;						// ��Ծ��Ч����ͼ��
Atlas atlas_land_effect;						// �����Ч����ͼ��

IMAGE img_1P_winnner;							// 1P ��ʤ�ı�ͼƬ
IMAGE img_2P_winnner;							// 2P ��ʤ�ı�ͼƬ
IMAGE img_winnner_bar;							// ��ʤ����ı�����ͼƬ

IMAGE img_avatar_peashooter;					// �㶺����ͷ��ͼƬ
IMAGE img_avatar_sunflower;						// ���տ�ͷ��ͼƬ 

Scene* game_scene = nullptr;
Scene* menu_scene = nullptr;
Scene* selector_scene = nullptr;


Camera main_camera;
SceneManager scene_manager;

std::vector<Platform> platform_list;
std::vector<Bullet*> bullet_list;

Player* player_1 = nullptr;
Player* player_2 = nullptr;

IMAGE* img_head_player_1 = nullptr;
IMAGE* img_head_player_2 = nullptr;

/*��Դ���غ���*/
void load_game_resources()
{
	/*��������*/
	AddFontResourceEx(_T("resources/IPix.ttf"), FR_PRIVATE, nullptr);

	/*����ͼƬ*/
	loadimage(&img_menu_background, _T("resources/menu_background.png"));

	loadimage(&img_VS, _T("resources/VS.png"));
	loadimage(&img_1P, _T("resources/1P.png"));
	loadimage(&img_2P, _T("resources/2P.png"));
	loadimage(&img_1P_desc, _T("resources/1P_desc.png"));
	loadimage(&img_2P_desc, _T("resources/2P_desc.png"));
	loadimage(&img_gravestone_right, _T("resources/gravestone.png"));
	hor_flip_img(&img_gravestone_right, &img_gravestone_left);
	loadimage(&img_selector_tip, _T("resources/selector_tip.png"));
	loadimage(&img_selector_background, _T("resources/selector_background.png"));
	loadimage(&img_1P_selector_btn_idle_right, _T("resources/1P_selector_btn_idle.png"));
	hor_flip_img(&img_1P_selector_btn_idle_right, &img_1P_selector_btn_idle_left);
	loadimage(&img_1P_selector_btn_down_right, _T("resources/1P_selector_btn_down.png"));
	hor_flip_img(&img_1P_selector_btn_down_right, &img_1P_selector_btn_down_left);
	loadimage(&img_2P_selector_btn_idle_right, _T("resources/2P_selector_btn_idle.png"));
	hor_flip_img(&img_2P_selector_btn_idle_right, &img_2P_selector_btn_idle_left);
	loadimage(&img_2P_selector_btn_down_right, _T("resources/2P_selector_btn_down.png"));
	hor_flip_img(&img_2P_selector_btn_down_right, &img_2P_selector_btn_down_left);
	loadimage(&img_peashooter_selector_background_right, _T("resources/peashooter_selector_background.png"));
	hor_flip_img(&img_peashooter_selector_background_right, &img_peashooter_selector_background_left);
	loadimage(&img_sunflower_selector_background_right, _T("resources/sunflower_selector_background.png"));
	hor_flip_img(&img_sunflower_selector_background_right, &img_sunflower_selector_background_left);

	loadimage(&img_sky, _T("resources/sky.png"));
	loadimage(&img_hills, _T("resources/hills.png"));
	loadimage(&img_platform_large, _T("resources/platform_large.png"));
	loadimage(&img_platform_small, _T("resources/platform_small.png"));

	loadimage(&img_1P_cursor, _T("resources/1P_cursor.png"));
	loadimage(&img_2P_cursor, _T("resources/2P_cursor.png"));

	atlas_peashooter_idle_right.load_from_file(_T("resources/peashooter_idle_%d.png"), 9);
	hor_flip_Atlas(atlas_peashooter_idle_right, atlas_peashooter_idle_left);
	atlas_peashooter_run_right.load_from_file(_T("resources/peashooter_run_%d.png"), 5);
	hor_flip_Atlas(atlas_peashooter_run_right, atlas_peashooter_run_left);
	atlas_peashooter_attack_ex_right.load_from_file(_T("resources/peashooter_attack_ex_%d.png"), 3);
	hor_flip_Atlas(atlas_peashooter_attack_ex_right, atlas_peashooter_attack_ex_left);
	atlas_peashooter_die_right.load_from_file(_T("resources/peashooter_die_%d.png"), 4);
	hor_flip_Atlas(atlas_peashooter_die_right, atlas_peashooter_die_left);

	atlas_sunflower_idle_right.load_from_file(_T("resources/sunflower_idle_%d.png"), 8);
	hor_flip_Atlas(atlas_sunflower_idle_right, atlas_sunflower_idle_left);
	atlas_sunflower_run_right.load_from_file(_T("resources/sunflower_run_%d.png"), 5);
	hor_flip_Atlas(atlas_sunflower_run_right, atlas_sunflower_run_left);
	atlas_sunflower_attack_ex_right.load_from_file(_T("resources/sunflower_attack_ex_%d.png"), 9);
	hor_flip_Atlas(atlas_sunflower_attack_ex_right, atlas_sunflower_attack_ex_left);
	atlas_sunflower_die_right.load_from_file(_T("resources/sunflower_die_%d.png"), 2);
	hor_flip_Atlas(atlas_sunflower_die_right, atlas_sunflower_die_left);

	loadimage(&img_pea, _T("resources/pea.png"));
	atlas_pea_break.load_from_file(_T("resources/pea_break_%d.png"), 3);
	atlas_sun.load_from_file(_T("resources/sun_%d.png"), 5);
	atlas_sun_explode.load_from_file(_T("resources/sun_explode_%d.png"), 5);
	atlas_sun_ex.load_from_file(_T("resources/sun_ex_%d.png"), 5);
	atlas_sun_ex_explode.load_from_file(_T("resources/sun_ex_explode_%d.png"), 5);
	atlas_sun_text.load_from_file(_T("resources/sun_text_%d.png"), 6);

	atlas_run_effect.load_from_file(_T("resources/run_effect_%d.png"), 4);
	atlas_jump_effect.load_from_file(_T("resources/jump_effect_%d.png"), 5);
	atlas_land_effect.load_from_file(_T("resources/land_effect_%d.png"), 2);

	loadimage(&img_1P_winnner, _T("resources/1P_winner.png"));
	loadimage(&img_2P_winnner, _T("resources/2P_winner.png"));
	loadimage(&img_winnner_bar, _T("resources/winnner_bar.png"));

	loadimage(&img_avatar_peashooter, _T("resources/avatar_peashooter.png"));
	loadimage(&img_avatar_sunflower, _T("resources/avatar_sunflower.png"));

	/*��������*/
	mciSendString(_T("open resources/bgm_game.mp3 alias bgm_game"), nullptr, 0, nullptr);
	mciSendString(_T("open resources/bgm_menu.mp3 alias bgm_menu"), nullptr, 0, nullptr);
	mciSendString(_T("open resources/pea_break_1.mp3 alias pea_break_1"), nullptr, 0, nullptr);
	mciSendString(_T("open resources/pea_break_2.mp3 alias pea_break_2"), nullptr, 0, nullptr);
	mciSendString(_T("open resources/pea_break_3.mp3 alias pea_break_3"), nullptr, 0, nullptr);
	mciSendString(_T("open resources/pea_shoot_1.mp3 alias pea_shoot_1"), nullptr, 0, nullptr);
	mciSendString(_T("open resources/pea_shoot_2.mp3 alias pea_shoot_2"), nullptr, 0, nullptr);
	mciSendString(_T("open resources/pea_shoot_ex.mp3 alias pea_shoot_ex"), nullptr, 0, nullptr);
	mciSendString(_T("open resources/sun_explode.mp3 alias sun_explode"), nullptr, 0, nullptr);
	mciSendString(_T("open resources/sun_explode_ex.mp3 alias sun_explode_ex"), nullptr, 0, nullptr);
	mciSendString(_T("open resources/sun_text.mp3 alias sun_text"), nullptr, 0, nullptr);
	mciSendString(_T("open resources/ui_confirm.wav alias ui_confirm"), nullptr, 0, nullptr);
	mciSendString(_T("open resources/ui_switch.wav alias ui_switch"), nullptr, 0, nullptr);
	mciSendString(_T("open resources/ui_win.wav alias ui_win"), nullptr, 0, nullptr);
}


int main()
{
	ExMessage msg;
	const int FPS = 60;
	load_game_resources();
	initgraph(1280, 720, EX_SHOWCONSOLE);

	settextstyle(28, 0, _T("IPix"));//��������
	setbkmode(TRANSPARENT);			//�����ı�����Ϊ͸��

	BeginBatchDraw();

	menu_scene = new MenuScene();
	game_scene = new GamaScene();
	selector_scene = new SelectorScene();

	scene_manager.set_current_scene(menu_scene);



	while (true)
	{
		DWORD stime = GetTickCount();

		while (peekmessage(&msg))
		{
			scene_manager.on_input(msg);
		}
		static DWORD last_tick_time = GetTickCount();
		DWORD current_tick_time = GetTickCount();
		DWORD delta = current_tick_time - last_tick_time;
		scene_manager.on_update(delta);
		last_tick_time = current_tick_time;

		cleardevice();
		scene_manager.on_draw(main_camera);
		FlushBatchDraw();

		DWORD etime = GetTickCount();
		DWORD dtime = etime - stime;
		if (dtime < 1000 / FPS)
		{
			Sleep(1000 / FPS - dtime);
		}
	}
	EndBatchDraw();
	return 0;
}