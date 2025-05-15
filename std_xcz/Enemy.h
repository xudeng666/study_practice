#pragma once
#include "Player.h"
#include "Bullet.h"
#include <iostream>
#include <random>

enum COllISION
{
	PLAYER = 0,
	BULLET,
	OTHER
};

/*������*/
class Enemy
{
public:
	/*
	* ���캯��
	@w	���ڿ��
	@h	���ڸ߶�
	*/
	Enemy(int w, int h);
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
	void Move(const Player* player);

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
	* �ж��Ƿ��ĳ���������ײ
	* @p ����
	*/
	bool checkOfPoint(const POINT& p);

	/*
	* �������ײ���
	* @plyer
	*/
	bool checkPlayer(Player* player);

	/*
	* ���ӵ���ײ���
	* @bullet
	*/
	bool checkBullet(Bullet* bullet);

	/*
	* �������ײ���
	* @plyer
	*/
	COllISION checkCollision(Player* player);

private:
	// ����
	POINT position;
	// ��ɫ���
	int _W_;
	// ��ɫ�߶�
	int _H_;
	// ��ɫ����֡��
	int aniNum;
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
	// ��ͼ���
	int _mapw_;
	// ��ͼ�߶�
	int _maph_;
};


