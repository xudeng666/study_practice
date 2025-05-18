#pragma once
#include "Animation.h"
#include "Bullet.h"


/*�����*/
class Player
{
public:
	/*
	* ���캯��
	@atl ��Դָ��
	*/
	//Player(Atlas* atl);
	/*����*/
	~Player();

	/*
	���ݳ�ʼ��
	@w ���ڿ��
	@h ���ڸ߶�
	@atl ��Դָ��
	*/
	void Init(int w, int h, Atlas* atl);

	/*
	��ɫ�ƶ�
	@w ���ڿ��
	@h ���ڸ߶�
	*/
	void Move();

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

	/*��ȡ�ӵ�����*/
	unsigned int getBulletNum();

	/*
	* ��ȡ�ӵ�
	* @index �ӵ��±�
	*/
	Bullet* getBulletOfIndex(int index);

	/*
	* ��ȡ�ӵ��б�
	*/
	vector<Bullet*>& getBulletList();

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
	const POINT& getPosition() const;

	/*
	* �ж��Ƿ��ĳ���������ײ
	* @p ����
	*/
	bool checkOfPoint(const POINT& p);

	/*��ȡ��������*/
	static Player* _getPlayer();

private:
	// ��ɫ����
	POINT position;
	// ��ɫ���
	int _W_;
	// ��ɫ�߶�
	int _H_;
	// �ٶȼ���ʱ��
	DWORD speed_time = 0;
	// ��ɫ��������
	bool h_fx[4];
	// ��ɫ�ٶ�
	double speed = 15;
	// ����2ֵ
	const double SQRT2 = sqrt(2);
	// ��ɫ����
	Animation* playerAni = nullptr;
	// �ӵ��б�
	vector<Bullet*> bullet_list;
	// �ӵ�����
	unsigned int bul_num = 3;
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
	// ��ͼ���
	int _mapw_ = 0;
	// ��ͼ�߶�
	int _maph_ = 0;

private:
	/*
	* ���캯��
	*/
	Player();
};

static Player* _THIS_ = nullptr;

