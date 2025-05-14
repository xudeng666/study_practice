#pragma once
#include <graphics.h>

/*×Óµ¯Àà*/
class Bullet
{
public:
	/*×ø±ê*/
	POINT position = { 0,0 };
public:
	Bullet()
	{
	}
	~Bullet()
	{
	}
	void Draw() const
	{
		setlinecolor(RGB(255,155,50));
		setfillcolor(RGB(200,75,10));
		fillcircle(position.x, position.y, RADIUS);
	}
	void setPosition(int x, int y)
	{
		position.x = x;
		position.y = y;
	}
private:
	/*°ë¾¶*/
	const int RADIUS = 10;
};

