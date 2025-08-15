#pragma once

#include <string>

// ��Ϸ����
enum class GameType
{
	START = 0,	// ��Ϸ��ʼ
	XCZ,		// �������Ҵ���
	KDWS,		// �ն���ʿ
	DLD,		// ���Ҷ�
	ZMDJ,		// ������
	PHF			// ƴ�÷�
};

std::string getStrByGameType(GameType type)
{
	switch (type)
	{
	case GameType::START:	return "start";	break;
	case GameType::XCZ:		return "xcz";	break;
	case GameType::KDWS:	return "kdws";	break;
	case GameType::DLD:		return "dld";	break;
	case GameType::ZMDJ:	return "zmdj";	break;
	case GameType::PHF:		return "phf";	break;
	}
}

/*ê��ģʽ*/
enum class AnchorMode
{
	TOPLEFT = 0,	// ����
	TOPCENTER,		// ����
	TOPRIGHT,		// ����
	LEFTCENTER,		// ����
	CENTER,			// ����
	RIGHTCENTER,	// ����
	BOTTOMLEFT,		// ����
	BOTTOMCENTER,	// ����
	BOTTOMRIGHT		// ����
};

/// <summary>
/// ��ȡ����FRect
/// </summary>
/// <param name="src">��ϷFRect</param>
/// <param name="mode">ê������</param>
/// <returns>SDL_FRect</returns>
SDL_FRect get_dst_rect(SDL_FRect& src, AnchorMode mode)
{
	float x, y;

	switch (mode)
	{
	case AnchorMode::TOPLEFT:
		x = src.x;
		y = src.y;
		break;
	case AnchorMode::TOPCENTER:
		x = src.x - src.w / 2;
		y = src.y;
		break;
	case AnchorMode::TOPRIGHT:
		x = src.x - src.w;
		y = src.y;
		break;
	case AnchorMode::LEFTCENTER:
		x = src.x;
		y = src.y - src.h / 2;
		break;
	case AnchorMode::CENTER:
		x = src.x - src.w / 2;
		y = src.y - src.h / 2;
		break;
	case AnchorMode::RIGHTCENTER:
		x = src.x - src.w;
		y = src.y - src.h / 2;
		break;
	case AnchorMode::BOTTOMLEFT:
		x = src.x;
		y = src.y - src.h;
		break;
	case AnchorMode::BOTTOMCENTER:
		x = src.x - src.w / 2;
		y = src.y - src.h;
		break;
	case AnchorMode::BOTTOMRIGHT:
		x = src.x - src.w;
		y = src.y - src.h;
		break;
	}

	return { x, y, (float)src.w, (float)src.h };
}

/*��������*/
enum class SceneType
{
	MENUE = 0,	// �˵�����
	GAME,		// ��Ϸ����
	SELECTOR,	// ѡ�񳡾�
};

/*��ť״̬*/
enum class ButtonState {
	PRESSED = 0,	// ����
	NORMAL,			// ����
	HOVER,			// ��ͣ
	DISABLED		// ����״̬���һ������ɽ�����
};