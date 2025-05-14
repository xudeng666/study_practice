#pragma once
#include "Animation.h"
#include "Bullet.h"

/*�����*/
class Player
{
public:
	/*
	* ���캯��
	@num ����֡��
	@spd ��ɫ��ʼ�ٶ�
	*/
	Player(int num, double spd);
	/*����*/
	~Player();

	/*
	���ݳ�ʼ��
	@w ���ڿ��
	@h ���ڸ߶�
	*/
	void Init(int w, int h);

	/*
	��ɫ�ƶ�
	@w ���ڿ��
	@h ���ڸ߶�
	*/
	void Move(int w, int h);

	/*�Ƿ��ƶ���*/
	bool isMove();

	/*���ƽ�ɫ*/
	void Draw();

	/*
	���÷�������
	@n	�±� 0123 ��������
	@m	�Ƿ��ƶ�
	*/
	void setFx(int index, bool m);

	/*ˢ������*/
	void upData();

	/*
	* ��Ҳ���
	* @msg	������Ϣ
	*/
	void processEvent(const ExMessage& msg);

	/*
	�����ӵ�����
	@num	��������
	*/
	void addBullet(unsigned int num);

	/*
	�����ӵ�����
	@num	��������
	*/
	void redBullet(unsigned int num);

	/*�ӵ�����*/
	void flyBullet();

	/*�����ӵ�*/
	void drawBullet();

	/*����ӵ�*/
	void clearBullet();

	/*��ȡ��ɫ����*/
	void getPosition(double& x, double& y) const;

private:
	// ��ɫ����x
	double m_x;
	// ��ɫ����y
	double m_y;
	// ��ɫ���
	int _W_;
	// ��ɫ�߶�
	int _H_;
	// ��ɫ����֡��
	const int aniNum;
	// �ٶȼ���ʱ��
	DWORD speed_time = 0;
	// ��ɫ��������
	bool h_fx[4];
	// ��ɫ�ٶ�
	double speed = 10;
	// ����2ֵ
	const double SQRT2 = sqrt(2);
	// ��ɫ����
	Animation* playerAni = nullptr;
	// �ӵ��б�
	vector<Bullet*> bullet_list;
	// �ӵ�����
	unsigned int bul_num = 1;
	// �ӵ��ٶ�(���ٶȣ�Ĭ�ϰ뾶��1��1Ȧ)
	double bul_speed = 1;
	// Ĭ���ӵ����а뾶
	int bul_radius = 60;
	// �ӵ��뾶����ֵ
	int bul_radBf = 0;
	// �뾶��������
	int bul_radBfValue = 40;
	// �ӵ��뾶����״̬
	bool bul_radType = true;
	// �ӵ��Ƕ�
	double bul_degrees = 0;
	// �ӵ��ٶȼ���ʱ��
	DWORD bul_time = 0;
};

