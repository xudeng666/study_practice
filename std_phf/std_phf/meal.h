#pragma once

/*��Ʒ����*/
enum class Meal
{
	None,                // ��
	Cola,                // ����
	Sprite,              // �ױ�
	BraisedChicken_Hot,  // ���˼����ȣ�
	BraisedChicken_Cold, // ���˼����䣩
	MeatBall_Hot,        // ���裨�ȣ�
	MeatBall_Cold,       // ���裨�䣩
	RedCookedPork_Hot,   // �����⣨�ȣ�
	RedCookedPork_Cold,  // �����⣨�䣩

	BraisedChicken_Box,  // ���˼�����Ʒ�У�
	MeatBall_Box,        // ���裨��Ʒ�У�
	RedCookedPork_Box,   // �����⣨��Ʒ�У�

	TakeoutBox,          // ������
};