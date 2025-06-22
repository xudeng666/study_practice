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

	std::stringstream str_stream;
	str_stream << file.rdbuf();
	str_text = str_stream.str();

	file.close();

	httplib::Server server;

	server.Post("/login", [&](const httplib::Request& req, httplib::Response& res)//创建了一个 HTTP 服务器的 POST 接口 /login
		{
			std::lock_guard<std::mutex> lock(g_mutex);	// 加锁保护共享变量

			if (progress_1 >= 0 && progress_2 >= 0)		// 判定两个玩家是否都登录了
			{
				res.set_content("-1", "text/plain");	// 都登陆则返给多余登录的客户端-1，并跳出
				return;
			}
			res.set_content(progress_1 >= 0 ? "2" : "1", "text/plain");	//给先后登录的玩家返回id 1 2
			(progress_1 >= 0) ? (progress_2 = 0) : (progress_1 = 0);	//给先后登录的玩家初始化进度为0
		});

	server.Post("/query_text", [&](const httplib::Request& req, httplib::Response& res)
		{
			res.set_content(str_text, "text/plain");
		});

	server.Post("/update_1", [&](const httplib::Request& req, httplib::Response& res)//创建了一个 HTTP 服务器的 POST 接口 /update_1
		{
			std::lock_guard<std::mutex> lock(g_mutex);

			progress_1 = std::stoi(req.body);	// 解析请求体中的数值，更新 progress_1

			res.set_content(std::to_string(progress_2), "text/plain"); // 返回 progress_2 的值 MIME 类型为 text/plain（纯文本）
		});

	server.Post("/update_2", [&](const httplib::Request& req, httplib::Response& res)
		{
			std::lock_guard<std::mutex> lock(g_mutex);

			progress_2 = std::stoi(req.body);

			res.set_content(std::to_string(progress_1), "text/plain");
		});

	server.listen("0.0.0.0", 25565); //监听在 所有网络接口 的 25565 端口

	return 0;
}