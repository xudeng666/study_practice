#pragma once

#include "region.h"
#include "meal.h"
#include "timer.h"

#include <vector>
/*����Ա��*/
class DeliveryDriver :
    public Region
{
public:
    DeliveryDriver(int x, int y);
    ~DeliveryDriver() = default;

    void on_cursor_up() override;
    void on_update(float delta) override;
    void on_render(SDL_Renderer* renderer) override;

private:
    // ��Ʒ״̬
    enum class Status
    {
        Waiting,   // ���ڵȴ�
        Completed  // �Ѿ����
    };

private:
    Timer timer_refresh;                // ����Աˢ�¼�ʱ��
    float time_waited = 0;              // �Ѿ��ȴ���ʱ��
    bool is_waiting = false;            // ��ǰ�Ƿ����ڵȴ�
    bool is_meituan = false;            // �Ƿ�����������Ա
    std::vector<Meal> meal_list;        // ��Ʒ�б�
    std::vector<Status> status_list;    // ��Ʒ״̬�б�
    int num_drink = 0, num_dish = 0;    // ���ϺͲ�Ʒ����
    const float time_waited_limit = 40; // �ȴ�ʱ������

private:
    // ˢ������Ա
    void refresh(); 
    /// <summary>
    /// ���ò�Ʒ
    /// </summary>
    /// <param name="target">��Ʒ����</param>
    /// <returns></returns>
    bool check_and_place(Meal target);
};

