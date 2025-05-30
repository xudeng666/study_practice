#pragma once
/// <summary>
/// �ӵ�ʱ�����
/// </summary>
class BulletTimeManager
{
public:
    /// <summary>
    /// ��ע����/�˳��ӵ�ʱ��
    /// </summary>
    enum class Status
    {
        Entering,   //�����ӵ�ʱ��
        Exiting     //�˳��ӵ�ʱ��
    };

public:
    static BulletTimeManager* instance();
    /// <summary>
    /// ȫ������
    /// ����������⣬����ȫ��������
    /// </summary>
    void post_process();
    void set_status(Status status);

    float on_update(float delta);

private:
    static BulletTimeManager* manager;

private:
    /**
    * @brief 	��ǽ����ӵ�ʱ�����
    * @details 	ȡֵ��Χ0.0~1.0  0��ʾ��ȫû��ȥ��1��ʾ��ȫ��ȥ
    */
    float progress = 0;
    Status status = Status::Exiting;        // ��ǵ�ǰ�ӵ�ʱ�䵱ǰ״̬
    const float SPEED_PROGRESS = 2.0f;      // ����/�˳��ӵ�ʱ����ٶ�
    const float DST_DELTA_FACTOR = 0.35f;   // �ӵ�ʱ���֡����ʱ�������ֵ
    const float DST_COLOR_FACTOR = 0.35f;   // �ӵ�ʱ��Ļ���ɫ�ʸı����

private:
    BulletTimeManager();
    ~BulletTimeManager();

    /**
    * @brief 	    ��ֵ����
    * @param start  ��ʼֵ
    * @param end    ����ֵ
    * @param t      ����0.0~1.0
    * @return       ����start���ȵ�endʱ�����ȵ�tʱ��ֵ
    */
    float lerp(float start, float end, float t)
    {
        return (1 - t) * start + t * end;
    }
};

