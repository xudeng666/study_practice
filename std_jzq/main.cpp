#include <iostream>
#include <graphics.h>
#include <string>
//  ������С��Ϸ

using namespace std;

#define FPS 60
#define _JZQ_WH_ 3
#define _JZQ_WWH_ 720

//����Ϸ����
void openWindow();
//��Ϸ��ʼ��
void gameInit();
//��Ϸ����
void gameRun();
//��Ϸ����-�ͷ���Դ
void gameOver();
/*��ȡ����*/
void getOperation();
/*���ݴ���*/
void dataProcessing();
/*���ƻ���*/
void gameDraw();
/*��Ӯ�ж�*/
bool checkWin();
/*�ж��÷����Ƿ�ʤ��*/
bool checkWinFx(int fx);
/*��������ж�*/
bool checkDraw();
/*��������*/
void drawBoard();
/*��������*/
void drawPiece();
/*�����ı�*/
void drawTipText();

/*��Ϣ*/
ExMessage msg{};
// ��ѭ���Ƿ���
bool running = false;
// ��Ϸ��������
char board_data[_JZQ_WH_][_JZQ_WH_] = {};
// ��ǰ���ӷ�
char current_piece;
// ��������
int checkNum;
// ��������x
int m_x;
// ��������y
int m_y;
// ѭ��ʱ��
DWORD stime;
DWORD etime;
// ����ʱ��
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
	// ����
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
	/*�ж�����λ��*/
	while (peekmessage(&msg))
	{
		// ���������������Ϣ
		if (msg.message == WM_LBUTTONDOWN)
		{
			// �������ת����������
			int t = _JZQ_WWH_ / _JZQ_WH_;
			m_x = msg.x / t;
			m_y = msg.y / t;
			if (board_data[m_x][m_y] == '-')
			{
				// ����
				board_data[m_x][m_y] = current_piece;
				// ���Ӽ���
				checkNum++;
				// �޸���������
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

	// �ô����ӳ�һ֡ʱ��ִ��
	if (stime - ktime <= 1000 / FPS)
		return;

	//cout << "��Ӯ�ж�" << endl;
	int result = -1;
	if (checkWin())
	{
		wstring path = board_data[m_x][m_y] == 'X' ? L"X ��һ�ʤ, ������Ϸ������\n�Ƿ��ؿ���Ϸ��":L"O ��һ�ʤ, ������Ϸ������\n�Ƿ��ؿ���Ϸ��";
		result = MessageBox(GetHWnd(), path.c_str(), _T("��ʾ"), MB_YESNO);
		running = false;
	}
	else if (checkDraw())
	{
		result = MessageBox(GetHWnd(), _T("ƽ��, ������Ϸ������\n�Ƿ��ؿ���Ϸ��"), _T("��ʾ"), MB_YESNO);
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
		case 0:// ��
			x = i;
			break;
		case 1:// ��
			y = i;
			break;
		case 2:// ����
			if (x != y)
			{
				return false;
			}
			x = y = i;
			break;
		case 3:// ����
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
		// ��X
		line(t * i, t * j, t * (i + 1), t * (j + 1));
		line(t * (i + 1), t * j, t * i, t * (j + 1));
		break;
	case 'O':
		// ��O
		circle(i * t + t / 2, j * t + t / 2, t / 2 - 2);
		break;
	}
}

void drawTipText()
{
	RECT rect = { 0,0,_JZQ_WWH_,20 };
	checkNum % 2 == 0 ? drawtext(_T("��ǰִ����Ϊ: O"), &rect, DT_CENTER) :
		drawtext(_T("��ǰִ����Ϊ: X"), &rect, DT_CENTER);
}