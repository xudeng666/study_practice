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
/// 获取旋转后的坐标
/// </summary>
/// <param name="p">起点</param>
/// <param name="c">旋转点</param>
/// <param name="angle">角度</param>
/// <returns>Vector2 p点旋转后的坐标</returns>
inline Vector2 get_Rotate_Vector(const Vector2 p, const Vector2 c, const float angle)
{
    float rotate = getRadiansByAngle(angle);
    float cos = std::cos(rotate);
    float sin = std::sin(rotate);

    Vector2 t = p - c;

    Vector2 m = { t.x * cos - t.y * sin, t.x * sin + t.y * cos };

    return m + c;
}