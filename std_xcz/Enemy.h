#pragma once
#include "Player.h"

/*������*/

class Enemy
{
public:
	/*
	* ���캯��
	@num ����֡��
	@spd ��ɫ��ʼ�ٶ�
	*/
	Enemy(int num, double spd);
	/*����*/
	~Enemy();

	/*
	���ݳ�ʼ��
	*/
	void Init();

	/*������ݳ�ʼ��*/
	void InitRandom();

	/*
	�ƶ� ׷�����
	* @player	�������
	*/
	void Move(const Player& player);

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
	// ��������
	unsigned int _type = 1;
};


