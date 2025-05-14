#pragma once
#include "Animation.h"

class Player
{
public:
	/*
	* ���캯��
	@w ��ɫ���
	@h ��ɫ�߶�
	@num ����֡��
	@spd ��ɫ��ʼ�ٶ�
	*/
	Player(int w, int h, int num, double spd);
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


private:
	// ��ɫ����x
	double m_x;
	// ��ɫ����y
	double m_y;
	// ��ɫ���
	const int _W_;
	// ��ɫ�߶�
	const int _H_;
	// ��ɫ����֡��
	const int aniNum;
	// �ٶȼ���ʱ��
	DWORD speed_time;
	// ��ɫ��������
	bool h_fx[4];
	// ��ɫ�ٶ�
	double speed;
	// ����2ֵ
	const double SQRT2 = sqrt(2);
	// ��ɫ����
	Animation* playerAni = nullptr;

};

