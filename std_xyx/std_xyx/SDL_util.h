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
