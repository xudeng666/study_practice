#include "../thirdparty/httplib.h"

#include "Path.h"
#include "Player.h"

#include <chrono>
#include <string>
#include <vector>
#include <thread>
#include <codecvt>
#include <fstream>
#include <sstream>

//��Ϸ״̬
enum class Stage
{
	Waiting,//�ȴ���Ҽ���
	Ready,//׼������ʱ
	Racing//������
};

int val_countdown = 4;          // ׼������ʱ
Stage stage = Stage::Waiting;   // ��ǰ��Ϸ�׶�

int id_player = 0;              // ������
std::atomic<int> progress_1 = -1;  // ���1����
std::atomic<int> progress_2 = -1;  // ���2����
int num_total_char = 0;         // ȫ���ַ���

Path path = Path(
	{
		{842, 842}, {1322, 842}, {1322, 442},
		{2762, 442}, {2762, 842}, {3162, 842},
		{3162, 1722}, {2122, 1722}, {2122, 1562},
		{842, 1562}, {842, 842}
	}
);  // ��ɫ�ƶ�·������

int idx_line = 0;               // ��ǰ�ı�������
int idx_char = 0;               // ��ǰ���ı��ַ�����
std::string str_text;           // �ı�����
std::vector<std::string> str_line_list; // ���ı��б�

Atlas atlas_1P_idle_up;    // ���1�������ö���ͼ��
Atlas atlas_1P_idle_down;  // ���1�������ö���ͼ��
Atlas atlas_1P_idle_left;  // ���1�������ö���ͼ��
Atlas atlas_1P_idle_right; // ���1�������ö���ͼ��
Atlas atlas_1P_run_up;     // ���1���ϱ��ܶ���ͼ��
Atlas atlas_1P_run_down;   // ���1���±��ܶ���ͼ��
Atlas atlas_1P_run_left;   // ���1�����ܶ���ͼ��
Atlas atlas_1P_run_right;  // ���1���ұ��ܶ���ͼ��
Atlas atlas_2P_idle_up;    // ���2�������ö���ͼ��
Atlas atlas_2P_idle_down;  // ���2�������ö���ͼ��
Atlas atlas_2P_idle_left;  // ���2�������ö���ͼ��
Atlas atlas_2P_idle_right; // ���2�������ö���ͼ��
Atlas atlas_2P_run_up;     // ���2���ϱ��ܶ���ͼ��
Atlas atlas_2P_run_down;   // ���2���±��ܶ���ͼ��
Atlas atlas_2P_run_left;   // ���2�����ܶ���ͼ��
Atlas atlas_2P_run_right;  // ���2���ұ��ܶ���ͼ��

IMAGE img_ui_1;          // �����ı�1
IMAGE img_ui_2;          // �����ı�2
IMAGE img_ui_3;          // �����ı�3
IMAGE img_ui_fight;      // �����ı�FIGHT
IMAGE img_ui_textbox;    // �����ı���
IMAGE img_background;    // ����ͼ

std::string str_address;       // ��������ַ
httplib::Client* client = nullptr; // HTTP�ͻ��˶���

void load_resources(HWND hwnd)
{
    AddFontResourceEx(_T("resources/IPix.ttf"), FR_PRIVATE, NULL);

    atlas_1P_idle_up.load(_T("resources/hajimi_idle_back %d.png"), 4);
    atlas_1P_idle_down.load(_T("resources/hajimi_idle_front %d.png"), 4);
    atlas_1P_idle_left.load(_T("resources/hajimi_idle_left %d.png"), 4);
    atlas_1P_idle_right.load(_T("resources/hajimi_idle_right %d.png"), 4);
    atlas_1P_run_up.load(_T("resources/hajimi_run_back %d.png"), 4);
    atlas_1P_run_down.load(_T("resources/hajimi_run_front %d.png"), 4);
    atlas_1P_run_left.load(_T("resources/hajimi_run_left %d.png"), 4);
    atlas_1P_run_right.load(_T("resources/hajimi_run_right %d.png"), 4);
    atlas_2P_idle_up.load(_T("resources/mambo_idle_back %d.png"), 4);
    atlas_2P_idle_down.load(_T("resources/mambo_idle_front %d.png"), 4);
    atlas_2P_idle_left.load(_T("resources/mambo_idle_left %d.png"), 4);
    atlas_2P_idle_right.load(_T("resources/mambo_idle_right %d.png"), 4);
    atlas_2P_run_up.load(_T("resources/mambo_run_back %d.png"), 4);
    atlas_2P_run_down.load(_T("resources/mambo_run_front %d.png"), 4);
    atlas_2P_run_left.load(_T("resources/mambo_run_left %d.png"), 4);
    atlas_2P_run_right.load(_T("resources/mambo_run_right %d.png"), 4);

    loadimage(&img_ui_1, _T("resources/ui_1.png"));
    loadimage(&img_ui_2, _T("resources/ui_2.png"));
    loadimage(&img_ui_3, _T("resources/ui_3.png"));
    loadimage(&img_ui_fight, _T("resources/ui_fight.png"));
    loadimage(&img_ui_textbox, _T("resources/ui_textbox.png"));
    loadimage(&img_background, _T("resources/background.png"));

    load_audio(_T("resources/bgm.mp3"), _T("bgm"));
    load_audio(_T("resources/1p_win.mp3"), _T("1p_win"));
    load_audio(_T("resources/2p_win.mp3"), _T("2p_win"));
    load_audio(_T("resources/click_1.mp3"), _T("click_1"));
    load_audio(_T("resources/click_2.mp3"), _T("click_2"));
    load_audio(_T("resources/click_3.mp3"), _T("click_3"));
    load_audio(_T("resources/click_4.mp3"), _T("click_4"));
    load_audio(_T("resources/ui_1.mp3"), _T("ui_1"));
    load_audio(_T("resources/ui_2.mp3"), _T("ui_2"));
    load_audio(_T("resources/ui_3.mp3"), _T("ui_3"));
    load_audio(_T("resources/ui_fight.mp3"), _T("ui_fight"));
}


int main(int argc, char** argv)
{
	httplib::Client client("localhost:25565");

	httplib::Result result = client.Post("/hello");
	if (!result || result->status != 200)
	{
		std::cout << "Hellow Failed!" << std::endl;

		return -1;
	}

	std::cout << result->body << std::endl;

	system("pause");

	return 0;
}