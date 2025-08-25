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

/*�ߴ���㷽ʽ*/
enum class SizeType
{
	AUTO = 0,	// �Զ�		������Դ����Ӧ��С
	PIXEL		// ����		�����������ֵ����
	// �͸��ڵ���� �� ��
	// �͸��ڵ���� �� ��
	// ���ֱ�������͸��ڵ����
	// ���ֱ������ߺ͸��ڵ����
	// ��������û���
};

/*��������*/
enum class SceneType
{
	MENUE = 0,	// �˵�����
	SELECTOR,	// ѡ�񳡾�
	GAME,		// ��Ϸ����
};

/*����ӳ��/����ģʽ*/
enum class TextureMapType
{
	AUTO = 0,	// �Զ�		��ȫ��ʾ��������
	TILE,		// ƽ��		���ݳߴ磬ƽ�̲ü�
	STRETCH		// ����		���ݳߴ磬��������
};

/*��Ⱦ��*/
enum RenderLayer
{
	BACKGROUND,	// ������	��ŵ�ͼ֮��
	ENTITY,		// ʵ����	��Ϸʵ�����֮��
	UI			// UI��
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