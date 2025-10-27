#pragma once

#include <SDL.h>

/// <summary>
/// 0xRRGGBBAA ��ʽת��
/// </summary>
/// <param name="hexColor"></param>
/// <returns></returns>
inline SDL_Color get_SDLColor_RGBA(Uint32 hexColor) {
    SDL_Color color;
    // ��ȡ��ɫ��������16-23λ��
    color.r = (hexColor >> 24) & 0xFF;
    // ��ȡ��ɫ��������8-15λ��
    color.g = (hexColor >> 16) & 0xFF;
    // ��ȡ��ɫ��������0-7λ��
    color.b = (hexColor >> 8) & 0xFF;
    // ��ȡ͸���ȷ�������0-7λ��
    color.a = hexColor & 0xFF;
    return color;
}


/// <summary>
/// 0xAARRGGBB ��ʽת��
/// </summary>
/// <param name="hexColor"></param>
/// <returns></returns>
inline SDL_Color get_SDLColor_ARGB(Uint32 hexColor) {
    SDL_Color color;
    // ��ȡ͸���ȷ�������24-31λ��
    color.a = (hexColor >> 24) & 0xFF;
    // ��ȡ��ɫ��������16-23λ��
    color.r = (hexColor >> 16) & 0xFF;
    // ��ȡ��ɫ��������8-15λ��
    color.g = (hexColor >> 8) & 0xFF;
    // ��ȡ��ɫ��������0-7λ��
    color.b = hexColor & 0xFF;
    return color;
}
/// <summary>
/// ��ȡ��ת�������
/// </summary>
/// <param name="p">���</param>
/// <param name="c">��ת��</param>
/// <param name="angle">�Ƕ�</param>
/// <returns>Vector2 p����ת�������</returns>
inline Vector2 get_Rotate_Vector(const Vector2 p, const Vector2 c, const float angle)
{
    float rotate = getRadiansByAngle(angle);
    float cos = std::cos(rotate);
    float sin = std::sin(rotate);

    Vector2 t = p - c;

    Vector2 m = { t.x * cos - t.y * sin, t.x * sin + t.y * cos };

    return m + c;
}