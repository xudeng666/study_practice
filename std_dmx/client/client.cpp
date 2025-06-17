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

//游戏状态
enum class Stage
{
	Waiting,//等待玩家加入
	Ready,//准备倒计时
	Racing//比赛中
};

int val_countdown = 4;          // 准备倒计时
Stage stage = Stage::Waiting;   // 当前游戏阶段

int id_player = 0;              // 玩家序号
std::atomic<int> progress_1 = -1;  // 玩家1进度
std::atomic<int> progress_2 = -1;  // 玩家2进度
int num_total_char = 0;         // 全部字符数

Path path = Path(
	{
		{842, 842}, {1322, 842}, {1322, 442},
		{2762, 442}, {2762, 842}, {3162, 842},
		{3162, 1722}, {2122, 1722}, {2122, 1562},
		{842, 1562}, {842, 842}
	}
);  // 角色移动路径对象

int idx_line = 0;               // 当前文本行索引
int idx_char = 0;               // 当前行文本字符索引
std::string str_text;           // 文本内容
std::vector<std::string> str_line_list; // 行文本列表

Atlas atlas_1P_idle_up;    // 玩家1向上闲置动画图集
Atlas atlas_1P_idle_down;  // 玩家1向下闲置动画图集
Atlas atlas_1P_idle_left;  // 玩家1向左闲置动画图集
Atlas atlas_1P_idle_right; // 玩家1向右闲置动画图集
Atlas atlas_1P_run_up;     // 玩家1向上奔跑动画图集
Atlas atlas_1P_run_down;   // 玩家1向下奔跑动画图集
Atlas atlas_1P_run_left;   // 玩家1向左奔跑动画图集
Atlas atlas_1P_run_right;  // 玩家1向右奔跑动画图集
Atlas atlas_2P_idle_up;    // 玩家2向上闲置动画图集
Atlas atlas_2P_idle_down;  // 玩家2向下闲置动画图集
Atlas atlas_2P_idle_left;  // 玩家2向左闲置动画图集
Atlas atlas_2P_idle_right; // 玩家2向右闲置动画图集
Atlas atlas_2P_run_up;     // 玩家2向上奔跑动画图集
Atlas atlas_2P_run_down;   // 玩家2向下奔跑动画图集
Atlas atlas_2P_run_left;   // 玩家2向左奔跑动画图集
Atlas atlas_2P_run_right;  // 玩家2向右奔跑动画图集

IMAGE img_ui_1;          // 界面文本1
IMAGE img_ui_2;          // 界面文本2
IMAGE img_ui_3;          // 界面文本3
IMAGE img_ui_fight;      // 界面文本FIGHT
IMAGE img_ui_textbox;    // 界面文本框
IMAGE img_background;    // 背景图

std::string str_address;       // 服务器地址
httplib::Client* client = nullptr; // HTTP客户端对象

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