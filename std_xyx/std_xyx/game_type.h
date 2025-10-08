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
	PRESSED = 0,	// ����
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

// GameType �ػ� std::hash
namespace std {
	template<> struct hash<GameType> {
		size_t operator()(const GameType& type) const noexcept {
			return hash<int>()(static_cast<underlying_type_t<GameType>>(type));
		}
	};
}

// ͨ���¼����ͣ����н�����������õ���
namespace EventType{
    constexpr const char* MOUSE_CLICK_LEFT          =       "MOUSE_CLICK_LEFT";                 // ���������������������
    constexpr const char* MOUSE_CLICK_RIGHT         =       "MOUSE_CLICK_RIGHT";                // ����Ҽ����������������
    constexpr const char* MOUSE_DOWN_LEFT           =       "MOUSE_DOWN_LEFT";                  // ����������
    constexpr const char* MOUSE_DOWN_RIGHT          =       "MOUSE_DOWN_RIGHT";                 // ����Ҽ�����
    constexpr const char* MOUSE_UP_LEFT             =       "MOUSE_UP_LEFT";                    // ������̧��
    constexpr const char* MOUSE_UP_RIGHT            =       "MOUSE_UP_RIGHT";                   // ����Ҽ�̧��

    constexpr const char* MOUSE_MOVE				=       "MOUSE_MOVE";						// ����ƶ�
}

// SceneType �ػ� std::hash
namespace std {
	template<> struct hash<SceneType> {
		size_t operator()(const SceneType& type) const noexcept {
			return hash<int>()(static_cast<underlying_type_t<SceneType>>(type));
		}
	};
}