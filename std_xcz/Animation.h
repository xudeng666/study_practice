#pragma once
#include <vector>
#include <graphics.h>


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

	~Animation();
	/*
	��������
	@x	x����λ��
	@y	y����λ��
	*/
	void play(int x, int y);

	/*
	* ���ò�������
	@isMove �Ƿ��ƶ�
	*/
	void DrawPlayer(bool isMove);
	/*
	* �����ٶ�
	*/
	void setAniSpeed(double speed);
	/*
	* ���÷���
	*/
	void setFx(bool isLeft);
private:
	std::vector<IMAGE*> frame_list;
	// ���������ٶ�
	double ani_speed = 0;
	// ������ʱ��
	int timer = 0;
	// ����֡����
	int idx_frame = 0;
	// ���� true ���� false ����
	bool ani_fx = false;
};

