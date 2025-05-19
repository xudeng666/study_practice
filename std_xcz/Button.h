#pragma once
#include <graphics.h>
#include <iostream>

// ��ѭ���Ƿ���
extern bool running;
/*��Ϸ�Ƿ�ʼ*/
extern bool gamestart;

/*��ť��*/
class Button
{
public:
	Button(RECT rect, LPCTSTR path_idl, LPCTSTR path_hov, LPCTSTR path_pus)
	{
		region = rect;
		loadimage(&img_idle, path_idl);
		loadimage(&img_hovered, path_hov);
		loadimage(&img_pushed, path_pus);
	}
	virtual ~Button() = default;

	/*���ư�ť*/
	void Draw()
	{
		switch (status)
		{
		case Button::Status::Idle:
			putimage(region.left, region.top, &img_idle);
			break;
		case Button::Status::Hovered:
			putimage(region.left, region.top, &img_hovered);
			break;
		case Button::Status::Pushed:
			putimage(region.left, region.top, &img_pushed);
			break;
		default:
			break;
		}
	}

	/*������*/
	void ProcessEvent(const ExMessage& msg)
	{
		switch (msg.message)
		{
		case WM_MOUSEMOVE:
			if (checkCursor(msg.x, msg.y))
			{
				status = status == Status::Pushed ? Status::Pushed : Status::Hovered;
			}
			else
			{
				status = Status::Idle;
			}
			break;
		case WM_LBUTTONDOWN:
			if (checkCursor(msg.x, msg.y))
			{
				status = Status::Pushed;
			}
			break;
		case WM_LBUTTONUP:
			if (status == Status::Pushed)
			{
				status = Status::Idle;
				OnClick();
			}
			break;
		}
	}

	/*
	* �ж����λ��
	*@ x	���x
	*@ y	���y
	*/
	bool checkCursor(int x, int y)
	{
		return region.left < x && region.right > x && region.top < y && region.bottom > y;
	}

	/*ִ�е��*/
	virtual void OnClick() = 0;

private:
	/*
	* ��ť״̬
	*@Idle		Ĭ��
	*@Hovered	��ͣ
	*@Pushed	����
	*/
	enum class Status
	{
		Idle = 0,
		Hovered,
		Pushed
	};

private:
	/*��ť��Χ*/
	RECT region;
	IMAGE img_idle;
	IMAGE img_hovered;
	IMAGE img_pushed;
	Status status = Status::Idle;
};

class StartGameBut :public Button
{
public:
	StartGameBut(RECT rect, LPCTSTR path_idl, LPCTSTR path_hov, LPCTSTR path_pus) 
		:Button(rect, path_idl, path_hov, path_pus) {}
	~StartGameBut() = default;
protected:
	void OnClick()
	{
		gamestart = true;
		// ���ű�������
		mciSendString(_T("play bgm repeat from 0"), nullptr, 0, nullptr);// repeat��ʾѭ������ from 0ָ��ͷ��ʼ����
	}
};

class OverGameBut :public Button
{
public:
	OverGameBut(RECT rect, LPCTSTR path_idl, LPCTSTR path_hov, LPCTSTR path_pus)
		:Button(rect, path_idl, path_hov, path_pus) {}
	~OverGameBut() = default;
protected:
	void OnClick()
	{
		running = false;
	}
};

