#pragma once
#include <graphics.h>
#include <iostream>

// 主循环是否开启
extern bool running;
/*游戏是否开始*/
extern bool gamestart;

/*按钮类*/
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

	/*绘制按钮*/
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

	/*鼠标监听*/
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
	* 判断鼠标位置
	*@ x	鼠标x
	*@ y	鼠标y
	*/
	bool checkCursor(int x, int y)
	{
		return region.left < x && region.right > x && region.top < y && region.bottom > y;
	}

	/*执行点击*/
	virtual void OnClick() = 0;

private:
	/*
	* 按钮状态
	*@Idle		默认
	*@Hovered	悬停
	*@Pushed	按下
	*/
	enum class Status
	{
		Idle = 0,
		Hovered,
		Pushed
	};

private:
	/*按钮范围*/
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
		// 播放背景音乐
		mciSendString(_T("play bgm repeat from 0"), nullptr, 0, nullptr);// repeat表示循环播放 from 0指从头开始播放
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

