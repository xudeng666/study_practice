#pragma once
#include <vector>
#include <graphics.h>

/*
*��Դ����
* @PLAYER	��ɫ��Դ
* @ENEMY_1	������Դ1
* @ENEMY_2	������Դ2
* @ENEMY_3	������Դ3
* @ENEMY_4	������Դ4
*/
enum FRAME_TYPE
{
	FRAME_TYPE_PLAYER = 0,
	FRAME_TYPE_ENEMY_1,
	FRAME_TYPE_ENEMY_2,
	FRAME_TYPE_ENEMY_3,
	FRAME_TYPE_ENEMY_4,
	FRAME_TYPE_COUNT
};

using namespace std;

#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "MSIMG32.LIB")

/*��ȾͼƬ��ʶ��͸������*/
inline void putimage_alpha(int x, int y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(nullptr), x, y, w, h, GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER, 0,255,AC_SRC_ALPHA });
}

/*ͼ����*/
class Atlas
{
public:
	/*
	���캯��
	*@path ��Դ·��
	*@num ��Դ����
	*/
	Atlas(LPCTSTR path, int num);

	/*
	���캯��
	@path ��Դ·��
	@type ����
	@num ��Դ����
	*/
	Atlas(LPCTSTR path, unsigned int type, int num);

	/*
	���캯��
	@path ��Դ·��
	@ice_path	��ѩ��Դ·��
	@type ����
	@num ��Դ����
	*/
	Atlas(LPCTSTR path, LPCTSTR ice_path, unsigned int type, int num);

	/*
	���캯��
	@path ��Դ·��
	@ice_path	��ѩ��Դ·��
	@num ��Դ����
	*/
	Atlas(LPCTSTR path, LPCTSTR ice_path, int num);

	~Atlas();
	/*��ȡ��Դ�б�*/
	vector <IMAGE*> getFrameList();

	/*
	��ȡͼƬ
	@index �±�
	*/
	IMAGE* getFrameByIndex(unsigned int index);

	/*
	��ȡ��Դ����
	*/
	unsigned int getFrameNum();

	/*
	��ȡ�����ߴ�
	@w	��ֵ����w
	@h	��ֵ����h
	*/
	void getFrameSize(int& w, int& h);

	/*���ɷ�����Դ*/
	void greatRightDirect();

	/*���ɰ�ɫ��Ӱ��Դ*/
	void greatWhitePix();

	/*���ɱ�ѩ��Ч��Դ*/
	void greatIcePix();

private:
	vector <IMAGE*> frame_list;
	IMAGE* img_ice;
	unsigned int frame_num;
};

