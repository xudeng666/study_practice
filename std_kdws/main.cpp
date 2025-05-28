#include "ResourceManager.h"
#include <chrono>
#include <thread>

int main(int argc, char** argv)
{
    HWND hwnd = initgraph(1280, 720, EW_SHOWCONSOLE);
    SetWindowText(hwnd, _T("Hollow Katana"));

    ExMessage msg;
    bool is_quit = false;

    BeginBatchDraw();
    while (!is_quit)
    {
        while (peekmessage(&msg))
        {
            // 处理消息
        }

        // 处理更新

        setbkcolor(RGB(0, 0, 0));
        cleardevice();

        // 处理绘图

        FlushBatchDraw();
    }
    EndBatchDraw();
	return 0;
}