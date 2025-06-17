#pragma once

#include "Vector2.h"

#include <vector>

class Path
{
public:
	Path(const std::vector<Vector2>& p_list)
	{
		point_list = p_list;

		for (size_t i = 1; i < point_list.size(); i++)
		{
			float len = (point_list[i] - point_list[i - 1]).length();
			segment_len_list.push_back(len);
			total_len += len;
		}
	}
	/// <summary>
	/// 获取进度对应的坐标
	/// </summary>
	/// <param name="pro">进度值（0~1）</param>
	/// <returns></returns>
	Vector2 get_position_at_progress(float pro)const
	{
		if (pro <= 0)
		{
			return point_list.front();
		}
		if (pro>=1)
		{
			return point_list.back();
		}
		float tag = total_len * pro;
		float len = 0.0f;
		for (size_t i = 1; i < point_list.size(); i++)
		{
			len += segment_len_list[i - 1];
			if (len >= tag)
			{
				return point_list[i - 1] + (point_list[i] - point_list[i - 1]) * ((tag - len + segment_len_list[i - 1]) / segment_len_list[i - 1]);
			}
		}
		return point_list.back();
	}

	~Path() = default;

private:
	float total_len = 0;//路径总长度
	std::vector<Vector2> point_list;//所有顶点位置坐标
	std::vector<float> segment_len_list;//每两个顶点之间片段长度列表
};