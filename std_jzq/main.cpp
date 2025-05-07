#include <iostream>
#include <graphics.h>
#include <string>
//  井字棋小游戏

using namespace std;

#define FPS 60
#define _JZQ_WH_ 3
#define _JZQ_WWH_ 720

//打开游戏窗口
void openWindow();
//游戏初始化
void gameInit();
//游戏运行
void gameRun();
//游戏结束-释放资源
void gameOver();
/*读取操作*/
void getOperation();
/*数据处理*/
void dataProcessing();
/*绘制画面*/
void gameDraw();
/*输赢判断*/
bool checkWin();
/*判定该方向是否胜利*/
bool checkWinFx(int fx);
/*走棋结束判断*/
bool checkDraw();
/*绘制棋盘*/
void drawBoard();
/*绘制棋子*/
void drawPiece();
/*绘制文本*/
void drawTipText();

/*消息*/
ExMessage msg{};
// 主循环是否开启
bool running = false;
// 游戏格子数据
char board_data[_JZQ_WH_][_JZQ_WH_] = {};
// 当前落子方
char current_piece;
// 走棋总数
int checkNum;
// 落子索引x
int m_x;
// 落子索引y
int m_y;
// 循环时间
DWORD stime;
DWORD etime;
// 落子时间
DWORD ktime;




int main()
{
	openWindow();
	gameInit();
	gameRun();
	gameOver();
}

void openWindow()
{
	initgraph(_JZQ_WWH_, _JZQ_WWH_, EX_SHOWCONSOLE);
}

void gameInit()
{
	m_x = -1;
	m_y = -1;
	running = true;
	current_piece = 'O';
	checkNum = 0;
	ktime = 0;
	for (int i = 0; i < _JZQ_WH_; ++i)
	{
		for (int j = 0; j < _JZQ_WH_; ++j)
		{
			board_data[i][j] = '-';
		}
	}
	// 清屏
	clearcliprgn();

	drawBoard();
}

void gameRun()
{
	BeginBatchDraw();
	while (running)
	{
		stime = GetTickCount();
		getOperation();
		gameDraw();
		dataProcessing();
		FlushBatchDraw();
		etime = GetTickCount();
		DWORD dtime = etime - stime;
		if (dtime < 1000 / FPS)
		{
			Sleep(1000 / FPS - dtime);
		}
	}
	EndBatchDraw();
}

void gameOver()
{
}

void getOperation()
{
	/*判定落子位置*/
	while (peekmessage(&msg))
	{
		// 检查鼠标左键按下消息
		if (msg.message == WM_LBUTTONDOWN)
		{
			// 鼠标坐标转换格子坐标
			int t = _JZQ_WWH_ / _JZQ_WH_;
			m_x = msg.x / t;
			m_y = msg.y / t;
			if (board_data[m_x][m_y] == '-')
			{
				// 落子
				board_data[m_x][m_y] = current_piece;
				// 落子计数
				checkNum++;
				// 修改棋子类型
				current_piece = current_piece == 'X' ? 'O' : 'X';

				drawPiece();
				drawTipText();
				ktime = GetTickCount();
			}
		}
	}
}

void dataProcessing()
{
	if (ktime == 0 )
		return;

	// 让代码延迟一帧时间执行
	if (stime - ktime <= 1000 / FPS)
		return;

	//cout << "输赢判断" << endl;
	int result = -1;
	if (checkWin())
	{
		wstring path = board_data[m_x][m_y] == 'X' ? L"X 玩家获胜, 本轮游戏结束！\n是否重开游戏？":L"O 玩家获胜, 本轮游戏结束！\n是否重开游戏？";
		result = MessageBox(GetHWnd(), path.c_str(), _T("提示"), MB_YESNO);
		running = false;
	}
	else if (checkDraw())
	{
		result = MessageBox(GetHWnd(), _T("平局, 本轮游戏结束！\n是否重开游戏？"), _T("提示"), MB_YESNO);
		running = false;
	}
	if (result == IDYES)
	{
		gameInit();
	}
	ktime = 0;
}

void gameDraw()
{
}

bool checkWin()
{
	if (checkNum < _JZQ_WH_ * 2 - 1)
	{
		return false;
	}
	for (int i = 0; i < 4; ++i)
	{
		if (checkWinFx(i))
		{
			return true;
		}
	}
	return false;
}

bool checkWinFx(int fx)
{
	int x = m_x;
	int y = m_y;
	char chese = board_data[x][y];
	for (int i = 0; i < _JZQ_WH_;++i)
	{
		switch (fx)
		{
		case 0:// 横
			x = i;
			break;
		case 1:// 竖
			y = i;
			break;
		case 2:// 右下
			if (x != y)
			{
				return false;
			}
			x = y = i;
			break;
		case 3:// 左下
			if (x != _JZQ_WH_ - y - 1)
			{
				return false;
			}
			x = i;
			y = _JZQ_WH_ - i - 1;
			break;
		}

		if (board_data[x][y] != chese)
		{
			return false;
		}
	}
	return true;
}

bool checkDraw()
{
	return checkNum >= _JZQ_WH_ * _JZQ_WH_;
}

void drawBoard()
{
	int t = _JZQ_WWH_ / _JZQ_WH_;
	for (int i = 1; i < _JZQ_WH_; ++i)
	{
		line(0, t * i, _JZQ_WWH_, t * i);
		line(t * i, 0, t * i, _JZQ_WWH_);
	}
}

void drawPiece()
{
	int t = _JZQ_WWH_ / _JZQ_WH_;
	int i = m_x;
	int j = m_y;
	switch (board_data[i][j])
	{
	case 'X':
		// 画X
		line(t * i, t * j, t * (i + 1), t * (j + 1));
		line(t * (i + 1), t * j, t * i, t * (j + 1));
		break;
	case 'O':
		// 画O
		circle(i * t + t / 2, j * t + t / 2, t / 2 - 2);
		break;
	}
}

void drawTipText()
{
	RECT rect = { 0,0,_JZQ_WWH_,20 };
	checkNum % 2 == 0 ? drawtext(_T("当前执棋者为: O"), &rect, DT_CENTER) :
		drawtext(_T("当前执棋者为: X"), &rect, DT_CENTER);
}