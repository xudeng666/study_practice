#pragma once
#include "Animation.h"
#include "Bullet.h"

/*玩家类*/
class Player
{
public:
	/*
	* 构造函数
	@num 动画帧数
	@spd 角色初始速度
	*/
	Player(int num, double spd);
	/*析构*/
	~Player();

	/*
	数据初始化
	@w 窗口宽度
	@h 窗口高度
	*/
	void Init(int w, int h);

	/*
	角色移动
	@w 窗口宽度
	@h 窗口高度
	*/
	void Move(int w, int h);

	/*是否移动中*/
	bool isMove();

	/*绘制角色*/
	void Draw();

	/*
	设置方向数据
	@n	下标 0123 上下左右
	@m	是否移动
	*/
	void setFx(int index, bool m);

	/*刷新数据*/
	void upData();

	/*
	* 玩家操作
	* @msg	按键消息
	*/
	void processEvent(const ExMessage& msg);

	/*
	增加子弹数量
	@num	新增数量
	*/
	void addBullet(unsigned int num);

	/*
	减少子弹数量
	@num	减少数量
	*/
	void redBullet(unsigned int num);

	/*子弹飞行*/
	void flyBullet();

	/*绘制子弹*/
	void drawBullet();

	/*清空子弹*/
	void clearBullet();

	/*获取角色坐标*/
	void getPosition(double& x, double& y) const;

private:
	// 角色坐标x
	double m_x;
	// 角色坐标y
	double m_y;
	// 角色宽度
	int _W_;
	// 角色高度
	int _H_;
	// 角色动画帧数
	const int aniNum;
	// 速度计算时间
	DWORD speed_time = 0;
	// 角色方向数据
	bool h_fx[4];
	// 角色速度
	double speed = 10;
	// 根号2值
	const double SQRT2 = sqrt(2);
	// 角色动画
	Animation* playerAni = nullptr;
	// 子弹列表
	vector<Bullet*> bullet_list;
	// 子弹数量
	unsigned int bul_num = 1;
	// 子弹速度(角速度：默认半径下1秒1圈)
	double bul_speed = 1;
	// 默认子弹飞行半径
	int bul_radius = 60;
	// 子弹半径呼吸值
	int bul_radBf = 0;
	// 半径呼吸长度
	int bul_radBfValue = 40;
	// 子弹半径呼吸状态
	bool bul_radType = true;
	// 子弹角度
	double bul_degrees = 0;
	// 子弹速度计算时间
	DWORD bul_time = 0;
};

