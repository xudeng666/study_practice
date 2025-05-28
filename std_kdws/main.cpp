#include "ResourceManager.h"
#include <chrono>
#include <thread>

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
        _stprintf_s(err_msg, _T("�޷�����: %s"), id);
        MessageBox(hwnd, err_msg, _T("��Դ����ʧ��"), MB_OK | MB_ICONERROR);
        return -1;
    }

    const nanoseconds frame_duration(1000000000 / 144);
    steady_clock::time_point last_tick = steady_clock::now();

    ExMessage msg;
    bool is_quit = false;

    BeginBatchDraw();
    while (!is_quit)
    {
        while (peekmessage(&msg))
        {
            // ������Ϣ
        }

        steady_clock::time_point frome_start = steady_clock::now();
        duration<float> delta = duration<float>(frome_start - last_tick);



        // �������

        setbkcolor(RGB(0, 0, 0));
        cleardevice();

        // �����ͼ

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