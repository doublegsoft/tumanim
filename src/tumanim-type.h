/*
**  _                               _           
** | |_ _   _ _ __ ___   __ _ _ __ (_)_ __ ___  
** | __| | | | '_ ` _ \ / _` | '_ \| | '_ ` _ \ 
** | |_| |_| | | | | | | (_| | | | | | | | | | |
**  \__|\__,_|_| |_| |_|\__,_|_| |_|_|_| |_| |_|
**                                              
*/
#ifndef __TUMANIM_TYPE_H__
#define __TUMANIM_TYPE_H__

#ifdef __cplusplus
extern "C"
{
#endif

#define FRAME_WIDTH     (1600 * 3 / 4)
#define FRAME_HEIGHT    (900 * 3 / 4)

#define ASPECT_RATIO    ((float)FRAME_WIDTH / FRAME_HEIGHT)
#define MARGIN_TOP      (FRAME_HEIGHT / 5)
#define NODE_HEIGHT     (FRAME_HEIGHT / 7)

void
tuma_render_and_run(SDL_Renderer* renderer);

#ifdef __cplusplus
}
#endif

#endif // __TUMANIM_TYPE_H__