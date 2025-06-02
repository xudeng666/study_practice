#include "ResourceManager.h"
#include "CollisionManager.h"
#include "CharacterManager.h"
#include "BulletTimeManager.h"

#include <chrono>
#include <thread>

/**
* @brief 帧率
*/
#define _FPS_ 144
/*绘制背景图*/
static void draw_background()
{
    static IMAGE* img_background = ResourceManager::instance()->find_image("background");
    static Rect rect_dst =
    {
        (getwidth() - img_background->getwidth()) / 2,//除以2是为了居中显示
        (getheight() - img_background->getheight()) / 2,
        img_background->getwidth(),
        img_background->getheight()
    };
    putimage_alpha_ex(img_background, &rect_dst);
}
/*显示玩家血量*/
static void draw_remain_hp()
{
    static IMAGE* img_ui_heart = ResourceManager::instance()->find_image("ui_heart");
    Rect rect_dst = { 0, 10, img_ui_heart->getwidth(), img_ui_heart->getheight() };
    for (int i = 0; i < CharacterManager::instance()->get_player()->get_hp(); i++)
    {
        rect_dst.x = 10 + i * 40;
        putimage_alpha_ex(img_ui_heart, &rect_dst);
    }
}

int main(int argc, char** argv)
{
    using namespace std::chrono;

    HWND hwnd = initgraph(1280, 720, EW_SHOWCONSOLE);
    SetWindowText(hwnd, _T("Hollow Katana"));

    try
    {
        ResourceManager::instance()->load();
    }
    catch (const LPCTSTR id)
    {
        TCHAR err_msg[512];
        _stprintf_s(err_msg, _T("无法加载: %s"), id);
        MessageBox(hwnd, err_msg, _T("资源加载失败"), MB_OK | MB_ICONERROR);
        return -1;
    }

    play_audio(_T("bgm"), true);

    const nanoseconds frame_duration(1000000000 / _FPS_);
    steady_clock::time_point last_tick = steady_clock::now();

    ExMessage msg;
    bool is_quit = false;

    BeginBatchDraw();
    while (!is_quit)
    {
        while (peekmessage(&msg))
        {
            CharacterManager::instance()->on_input(msg);
        }

        steady_clock::time_point frome_start = steady_clock::now();
        duration<float> delta = duration<float>(frome_start - last_tick);

        // 处理更新
        float s_delta = BulletTimeManager::instance()->on_update(delta.count());
        CharacterManager::instance()->on_update(s_delta);
        CollisionManager::instance()->processCollide();

        setbkcolor(RGB(0, 0, 0));
        cleardevice();

        // 处理绘图
        draw_background();
        CharacterManager::instance()->on_draw();
        CollisionManager::instance()->onDebugRender();
        draw_remain_hp();

        FlushBatchDraw();
        last_tick = frome_start;
        nanoseconds sleep_duration = frame_duration - (steady_clock::now() - frome_start);
        if (sleep_duration > nanoseconds(0))
        {
            std::this_thread::sleep_for(sleep_duration);
        }
    }
    EndBatchDraw();
	return 0;
}