#pragma once

#include <SDL.h>

/// <summary>
/// 0xRRGGBBAA 格式转换
/// </summary>
/// <param name="hexColor"></param>
/// <returns></returns>
inline SDL_Color get_SDLColor_RGBA(Uint32 hexColor) {
    SDL_Color color;
    // 提取红色分量（高16-23位）
    color.r = (hexColor >> 24) & 0xFF;
    // 提取绿色分量（高8-15位）
    color.g = (hexColor >> 16) & 0xFF;
    // 提取蓝色分量（高0-7位）
    color.b = (hexColor >> 8) & 0xFF;
    // 提取透明度分量（低0-7位）
    color.a = hexColor & 0xFF;
    return color;
}


/// <summary>
/// 0xAARRGGBB 格式转换
/// </summary>
/// <param name="hexColor"></param>
/// <returns></returns>
inline SDL_Color get_SDLColor_ARGB(Uint32 hexColor) {
    SDL_Color color;
    // 提取透明度分量（高24-31位）
    color.a = (hexColor >> 24) & 0xFF;
    // 提取红色分量（高16-23位）
    color.r = (hexColor >> 16) & 0xFF;
    // 提取绿色分量（高8-15位）
    color.g = (hexColor >> 8) & 0xFF;
    // 提取蓝色分量（低0-7位）
    color.b = hexColor & 0xFF;
    return color;
}
/// <summary>
/// 获取旋转后的全局坐标
/// </summary>
/// <param name="p">计算坐标</param>
/// <param name="c">旋新坐标</param>
/// <param name="angle">旋转角度</param>
/// <returns>Vector2 p点旋转后的坐标</returns>
inline Vector2 get_Angle_Vector(const Vector2 p, const Vector2 c, const double angle)
{
    float rotate = getRadiansByAngle(angle);
    float cos = std::cos(rotate);
    float sin = std::sin(rotate);

    Vector2 t = p - c;

    Vector2 m = { t.x * cos - t.y * sin, t.x * sin + t.y * cos };

    return m + c;
}
/// <summary>
/// 获取旋转后的全局坐标
/// </summary>
/// <param name="p">计算坐标</param>
/// <param name="c">旋新坐标</param>
/// <param name="rotation">旋转弧度</param>
/// <returns>Vector2 p点旋转后的坐标</returns>
inline Vector2 get_Rotate_Vector(const Vector2 p, const Vector2 c, const double rotation)
{
    float cos = std::cos(rotation);
    float sin = std::sin(rotation);

    Vector2 t = p - c;

    Vector2 m = { t.x * cos - t.y * sin, t.x * sin + t.y * cos };

    return m + c;
}