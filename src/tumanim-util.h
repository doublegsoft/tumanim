/*
**  _                               _           
** | |_ _   _ _ __ ___   __ _ _ __ (_)_ __ ___  
** | __| | | | '_ ` _ \ / _` | '_ \| | '_ ` _ \ 
** | |_| |_| | | | | | | (_| | | | | | | | | | |
**  \__|\__,_|_| |_| |_|\__,_|_| |_|_|_| |_| |_|
**                                              
*/
#ifndef __TUMANIM_UTIL_H__
#define __TUMANIM_UTIL_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*!
** 一个点到圆中心的连线，但是不能覆盖到圆，获取到圆边缘的坐标值。
*/
void
tuma_point_to_circle_center(int sx, int sy, int tx, int ty, int radius, int* ex, int* ey);

/*!
** 一个点到直线最短距离，获取直线上与点连线的坐标。
*/
void
tuma_point_to_line_shortest(int sx, int sy, int tx, int ty, int px, int py, int* x, int* y);

#ifdef __cplusplus
}
#endif

#endif // __TUMANIM_UTIL_H__