#pragma once

#include <string>

// ��Ϸ����
enum class GameType
{
	NONE = 0,	// ��
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
	case GameType::NONE:	return "";		break;
	case GameType::XCZ:		return "xcz";	break;
	case GameType::KDWS:	return "kdws";	break;
	case GameType::DLD:		return "dld";	break;
	case GameType::ZMDJ:	return "zmdj";	break;
	case GameType::PHF:		return "phf";	break;
	}
}