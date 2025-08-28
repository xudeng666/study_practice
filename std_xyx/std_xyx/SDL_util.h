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
