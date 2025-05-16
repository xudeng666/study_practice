#pragma once
#include <graphics.h>
#include <stdlib.h>
#include "Atlas.h"

/*
* ֡��������
*/
class Animation
{
public:
	/*
	���캯��
	@path ��Դ·��
	@speed	�����ٶ�
	*/
	Animation(Atlas* atl, double speed);

	~Animation() = default;
	/*
	��������
	@x	x����λ��
	@y	y����λ��
	*/
	void play(int x, int y);

	/*
	* ���ò������� �����ֹͣ֡
	@isMove �Ƿ��ƶ�
	*/
	void DrawPlayer(bool isMove);
	/*
	* ���ò�������
	*/
	void DrawPlayer();
	/*
	* �����ٶ�
	*/
	void setAniSpeed(double speed);
	/*
	* ���÷���
	*/
	void setFx(bool isLeft);

	/*
	��ȡ�����ߴ�
	@w	��ֵ����w
	@h	��ֵ����h
	*/
	void getAniSize(int& w, int& h);
	/*
	��ȡ����֡��
	*/
	unsigned int getAniFrameNum();
private:
	// ͼ��ָ��
	Atlas* atlas;
	// ���������ٶ�
	double ani_speed = 0;
	// ������ʱ��
	int timer = 0;
	// ����֡����
	int idx_frame = 0;
	// ���� true ���� false ����
	bool ani_fx = false;
	// ����֡��
	unsigned int frameNum = 0;
};

