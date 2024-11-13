
// util.h

#pragma once

#include <graphics.h>

// 连接库
#pragma comment(lib, "WINMM.lib")   // 多媒体库
#pragma comment(lib, "MSIMG32.lib") // 图像库

struct Rect
{
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;
};

inline void
putimage_a(IMAGE* img, const Rect& rect_dst, const Rect& rect_src = Rect{ 0, 0, 0, 0 })
{
    static BLENDFUNCTION blend_func = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };

    AlphaBlend(
        GetImageHDC(GetWorkingImage()),
        rect_dst.x,
        rect_dst.y,
        rect_dst.w,
        rect_dst.h,

        GetImageHDC(img),
        rect_src.x,
        rect_src.y,
        rect_src.w ? rect_src.w : img->getwidth(),
        rect_src.h ? rect_src.h : img->getheight(),

        blend_func);
}

inline int
range_random(int min, int max)
{
    return min + rand() % (max - min + 1);
}
