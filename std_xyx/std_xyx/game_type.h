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

/*��������*/
enum class SceneType
{
	MENUE = 0,	// �˵�����
	GAME,		// ��Ϸ����
	SELECTOR,	// ѡ�񳡾�
};