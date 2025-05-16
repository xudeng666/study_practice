#pragma once
#include <graphics.h>

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
		/*if (msg.message == MOUSEEVENTF_MOVE || msg.message == MOUSEEVENTF_LEFTDOWN || msg.message == MOUSEEVENTF_LEFTUP)
		{
			if (checkCursor(msg.x,msg.y))
			{
				if (msg.message == MOUSEEVENTF_LEFTDOWN)
				{
					status = Status::Pushed;
				}
				else
				{
					status = Status::Hovered;
				}
			}
			else
			{
				status = Status::Idle;
			}	
		}*/
		switch (msg.message)
		{
		case WM_MOUSEMOVE:
			if (status == Status::Idle && checkCursor(msg.x, msg.y))
			{
				status = Status::Hovered;
			}
			else if (status == Status::Hovered && !checkCursor(msg.x, msg.y))
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
	}
};

class StartOverBut :public Button
{
public:
	StartOverBut(RECT rect, LPCTSTR path_idl, LPCTSTR path_hov, LPCTSTR path_pus)
		:Button(rect, path_idl, path_hov, path_pus) {}
	~StartOverBut() = default;
protected:
	void OnClick()
	{
	}
};

