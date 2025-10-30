#pragma once

#include <string>
#include <iostream>
#include <functional>
#include <type_traits>

// ��Ϸ����
enum class GameType
{
	NONE = 0,	// ��
	START,		// ��Ϸ��ʼ
	XCZ,		// �������Ҵ���
	KDWS,		// �ն���ʿ
	DLD,		// ���Ҷ�
	ZMDJ,		// ������
	PHF			// ƴ�÷�
};

/*ê��ģʽ*/
enum class AnchorMode	// ע�⣬��Ÿ�ֵǿ�����������޸�
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
	MENU = 0,	// �˵�����
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
	PRESSED = 0,	// 
	NORMAL,			// ����
	HOVER,			// ��ͣ
	DISABLED		// ����״̬���һ������ɽ�����
};

/*��ײ��*/
enum class CollisionLayer
{
	NONE,		// ��
	BULLET,		// �ӵ�
	PLAYER_1,	// ���1
	PLAYER_2,	// ���2
	ENEMY,		// ���ˣ��֣�
};

/*����ڵ�����*/
enum class NodeType
{
	ROOT,       // ���ڵ�
	LAYER,		// �㼶�ڵ㣨����/��Ϸ/UI��
	GAMENODE    // ��Ϸ����ڵ�
};

// �Զ����¼�����
enum class EventType {

	COLLISION,			// ��ײ���������δ�����
	ADD_BULLET,			// ����ӵ�
	REDUCE_BULLET,		// �����ӵ�
	LAUNCH_BULLET,		// �����ӵ�
	PLAYER_DIE,			// ��ɫ����
	PLAYER_MOVE,		// ��ɫ�ƶ�
	ENEMY_DIE,			// ��������
	ADD_ENEMY,			// ��������
	REDUCE_ENEMY,		// ���ٵ���
	COUNT				// �ڱ�λ,���ڼ�¼��ö������������ʹ�ã�����ɾ��
};

// GameType �ػ� std::hash
namespace std {
	template<> struct hash<GameType> {
		size_t operator()(const GameType& type) const noexcept {
			return hash<int>()(static_cast<underlying_type_t<GameType>>(type));
		}
	};
}

// SceneType �ػ� std::hash
namespace std {
	template<> struct hash<SceneType> {
		size_t operator()(const SceneType& type) const noexcept {
			return hash<int>()(static_cast<underlying_type_t<SceneType>>(type));
		}
	};
}