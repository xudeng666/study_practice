#include "../thirdparty/httplib.h"

#include <mutex>
#include <string>
#include <fstream>

std::mutex g_mutex;//ȫ�ֻ�����
std::string str_text;//�ı�����

int progress_1 = -1;//���1����
int progress_2 = -1;//���2����

int main(int argc, char** argv)
{
	std::ifstream file("text.txt");

	if (!file.good())
	{
		MessageBox(nullptr, L"�޷����ı��ļ� text.txt", L"����ʧ��", MB_OK || MB_ICONERROR);
		return -1;
	}

	return 0;
}