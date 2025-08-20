#pragma once

#include <string>
#include "SDL.h"

// ��Ϸ����
enum class GameType
{
	//NONE = -1,	// ��
	START = 0,	// ��Ϸ��ʼ
	XCZ,		// �������Ҵ���
	KDWS,		// �ն���ʿ
	DLD,		// ���Ҷ�
	ZMDJ,		// ������
	PHF			// ƴ�÷�
};

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
	SELECTOR,	// ѡ�񳡾�
	GAME,		// ��Ϸ����
};

/*��ť״̬*/
enum class ButtonState {
	PRESSED = 0,	// ����
	NORMAL,			// ����
	HOVER,			// ��ͣ
	DISABLED		// ����״̬���һ������ɽ�����
};

/*��ײ��*/
enum class CollisionLayer
{
	NONE,	// ��
	BULLET,	// �ӵ�
	PLAYER,	// ���
	ENEMY,	// ���ˣ��֣�
};