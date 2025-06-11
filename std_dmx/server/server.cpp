#include "../thirdparty/httplib.h"

#include <mutex>
#include <string>
#include <fstream>

std::mutex g_mutex;//全局互斥锁
std::string str_text;//文本内容

int progress_1 = -1;//玩家1进度
int progress_2 = -1;//玩家2进度

int main(int argc, char** argv)
{
	std::ifstream file("text.txt");

	if (!file.good())
	{
		MessageBox(nullptr, L"无法打开文本文件 text.txt", L"启动失败", MB_OK || MB_ICONERROR);
		return -1;
	}

	return 0;
}