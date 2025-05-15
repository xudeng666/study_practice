#pragma once
#include <vector>
#include <graphics.h>
#include <stdlib.h>


using namespace std;
//srand((unsigned int)time(NULL));


#pragma comment(lib, "MSIMG32.LIB")
/*��ȾͼƬ��ʶ��͸������*/
inline void putimage_alpha(int x, int y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(nullptr), x, y, w, h, GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER, 0,255,AC_SRC_ALPHA });
}

/*
* ֡��������
*/
class Animation
{
public:
	/*
	���캯��
	@path ��Դ·��
	@num ��Դ����
	@speed	�����ٶ�
	*/
	Animation(LPCTSTR path, int num, double speed);

	/*
	���캯��
	@path ��Դ·��
	@type ����
	@num ��Դ����
	@speed	�����ٶ�
	*/
	Animation(LPCTSTR path, unsigned int type, int num, double speed);

	~Animation();
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
	void getAniSize(int& w, int& h)
	{
		w = frame_list[0]->getwidth();
		h = frame_list[0]->getheight();
	}
private:
	vector<IMAGE*> frame_list;
	// ���������ٶ�
	double ani_speed = 0;
	// ������ʱ��
	int timer = 0;
	// ����֡����
	int idx_frame = 0;
	// ���� true ���� false ����
	bool ani_fx = false;
};

