#pragma once
#include "Vector2.h"
#include "Collision_layer.h"
#include <functional>

class CollisionManager;

/**
*@brief		��ײ��
*@note		���������˽�У�����Ϊ�������ⴴ����ײ�䡣������ײ�������������ײ��û������
*@author 	xd  
*@date 		20-5-9  
*/
class CollisionBox
{
	friend class CollisionManager;
private:
    // ��ײ�������ê��Ϊ���ĵ�
	Vector2 position;
	Vector2 size;
	// �Ƿ�������ײ���
	bool enabled = true;
	// ��ײ��Ļص�����
	std::function<void()> call_back;
	// ������ײ��
	CollisionLayer layer_src = CollisionLayer::None;
	// Ŀ����ײ��
	CollisionLayer layer_dst = CollisionLayer::None;
private:
	CollisionBox() = default;
	~CollisionBox() = default;
public:
    /**
    *@note ��ײ����߼�����ײ�������ܣ����Դ˴���Ҫ�ṩset�ӿڼ���
    */
    /// <summary>
    /// ������ײ������״̬
    /// </summary>
    /// <param name="flag"></param>
    void set_enabled(bool flag)
    {
        enabled = flag;
    }
    /// <summary>
    /// ����������ײ��
    /// </summary>
    /// <param name="layer"></param>
    void set_layer_src(CollisionLayer layer)
    {
        layer_src = layer;
    }
    /// <summary>
    /// ����Ŀ����ײ��
    /// </summary>
    /// <param name="layer"></param>
    void set_layer_dst(CollisionLayer layer)
    {
        layer_dst = layer;
    }

    void set_call_back(std::function<void()> call_back)
    {
        this->call_back = call_back;
    }

    void set_size(const Vector2& size)
    {
        this->size = size;
    }

    const Vector2& get_size() const
    {
        return size;
    }

    void set_position(const Vector2& pos)
    {
        position = pos;
    }
};

