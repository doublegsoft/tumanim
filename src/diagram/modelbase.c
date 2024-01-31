/*
**  _                               _           
** | |_ _   _ _ __ ___   __ _ _ __ (_)_ __ ___  
** | __| | | | '_ ` _ \ / _` | '_ \| | '_ ` _ \ 
** | |_| |_| | | | | | | (_| | | | | | | | | | |
**  \__|\__,_|_| |_| |_|\__,_|_| |_|_|_| |_| |_|
**                                              
*/
#include <SDL2/SDL.h>
#include <SDL_image.h>

#include "tumanim-type.h"
#include "tumanim-image.h"

int
tuma_frame_width(void)
{
  return FRAME_WIDTH;
}

int
tuma_frame_height(void)
{
  return FRAME_HEIGHT;
}

void
tuma_render_and_run(SDL_Renderer* renderer)
{
  SDL_Surface* background = SDL_CreateRGBSurface(0, tuma_frame_width(), tuma_frame_height(), 32, 0, 0, 0, 0);
  SDL_Texture* tex_bg = SDL_CreateTextureFromSurface(renderer, background);
  
  // Create a texture from the image surface
  tuma_image_t* img_manager = tuma_image_load("../../img/manager.png");
  tuma_image_t* img_studio = tuma_image_load("../../img/studio.png");
  tuma_image_t* img_git = tuma_image_load("../../img/git.png");
  tuma_image_t* img_maven = tuma_image_load("../../img/maven.png");
  
  tuma_image_t* img_groovy = tuma_image_load("../../img/groovy.png");
  tuma_image_t* img_jar = tuma_image_load("../../img/jar.png");
  
  tuma_image_t* img_developer1 = tuma_image_load("../../img/developer1.png");
  tuma_image_t* img_developer2 = tuma_image_load("../../img/developer2.png");
  
  img_manager->w = NODE_HEIGHT;
  img_manager->h = NODE_HEIGHT;
  img_studio->w = NODE_HEIGHT * ((float)img_studio->orig_w / img_studio->orig_h);
  img_studio->h = NODE_HEIGHT;
  img_git->w = NODE_HEIGHT * ((float)img_git->orig_w / img_git->orig_h);
  img_git->h = NODE_HEIGHT;
  img_maven->w = NODE_HEIGHT * ((float)img_maven->orig_w / img_maven->orig_h);
  img_maven->h = NODE_HEIGHT;
  
  img_developer1->w = NODE_HEIGHT * ((float)img_developer1->orig_w / img_developer1->orig_h);
  img_developer1->h = NODE_HEIGHT;
  img_developer2->w = NODE_HEIGHT * ((float)img_developer2->orig_w / img_developer2->orig_h);
  img_developer2->h = NODE_HEIGHT;
  
  img_groovy->w = 22;
  img_groovy->h = 22;
  img_jar->w = 22;
  img_jar->h = 22;
  
  tuma_image_resize(renderer, img_manager, img_manager->w, img_manager->h);
  tuma_image_resize(renderer, img_studio, img_studio->w, img_studio->h);
  tuma_image_resize(renderer, img_git, img_git->w, img_git->h);
  tuma_image_resize(renderer, img_maven, img_maven->w, img_maven->h);
  
  tuma_image_resize(renderer, img_groovy, img_groovy->w, img_groovy->h);
  tuma_image_resize(renderer, img_jar, img_jar->w, img_jar->h);
  
  tuma_image_resize(renderer, img_developer1, img_developer1->w, img_developer1->h);
  tuma_image_resize(renderer, img_developer2, img_developer2->w, img_developer2->h);
  
  int margin;
  int tot_width = 0;
  tot_width += img_manager->w;
  tot_width += img_studio->w;
  tot_width += img_git->w;
  // tot_width += img_maven->w;
  
  margin = (FRAME_WIDTH - tot_width) / 7;
  
  float offset_studio_to_git = 0.0;
  float offset_studio_to_maven = 0.0;
  float offset_dash = 0.0;
  
  const int LENGTH_DASH = 5;
  const int LENGTH_GAP = 5;
  
  // Main loop
  SDL_Event event;
  int quit = 0;
  while (!quit) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        quit = 1;
      }
    }

    // Clear the renderer
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, tex_bg, NULL, NULL);
    
    SDL_Rect rect_manager;
    rect_manager.x = margin;
    rect_manager.y = MARGIN_TOP;
    rect_manager.w = img_manager->w;
    rect_manager.h = img_manager->h;
    SDL_RenderCopy(renderer, img_manager->tex, NULL, &rect_manager);
    
    SDL_Rect rect_developer2;
    rect_developer2.x = margin;
    rect_developer2.y = FRAME_HEIGHT - MARGIN_TOP / 3 - img_developer2->h;
    rect_developer2.w = img_developer2->w;
    rect_developer2.h = img_developer2->h;
    SDL_RenderCopy(renderer, img_developer2->tex, NULL, &rect_developer2);
    
    SDL_Rect rect_developer1;
    rect_developer1.x = margin;
    rect_developer1.y = rect_manager.y + rect_manager.h + (rect_developer2.y - rect_manager.y - rect_manager.h - img_developer1->h) / 2;
    rect_developer1.w = img_developer1->w;
    rect_developer1.h = img_developer1->h;
    SDL_RenderCopy(renderer, img_developer1->tex, NULL, &rect_developer1);
    
    SDL_Rect rect_studio;
    rect_studio.x = margin * 3 + img_manager->w;
    rect_studio.y = MARGIN_TOP;
    rect_studio.w = img_studio->w;
    rect_studio.h = img_studio->h;
    SDL_RenderCopy(renderer, img_studio->tex, NULL, &rect_studio);
    
    SDL_Rect rect_git;
    rect_git.x = margin * 5 + img_manager->w + img_studio->w;
    rect_git.y = MARGIN_TOP / 3;
    rect_git.w = img_git->w;
    rect_git.h = img_git->h;
    SDL_RenderCopy(renderer, img_git->tex, NULL, &rect_git);
    
    SDL_Rect rect_maven;
/*    rect_maven.x = margin * 7 + img_manager->w + img_studio->w + img_git->w;*/
    rect_maven.x = margin * 5 + img_manager->w + img_studio->w;
    rect_maven.y = MARGIN_TOP / 3 * 3 + img_git->h;
    rect_maven.w = img_maven->w;
    rect_maven.h = img_maven->h;
    SDL_RenderCopy(renderer, img_maven->tex, NULL, &rect_maven);
    
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    
    for (int x = margin + img_manager->w; x < (margin * 3 + img_manager->w); x += (LENGTH_DASH + LENGTH_GAP)) 
    {
      SDL_RenderDrawLine(renderer, 
                         x + offset_dash, 
                         MARGIN_TOP + NODE_HEIGHT / 2, 
                         x + LENGTH_DASH + offset_dash, 
                         MARGIN_TOP + NODE_HEIGHT / 2);
    }
    
    /*!
    ** the connection between studio and git
    */
    int vert_dist = rect_studio.y - rect_git.y - rect_git.h / 2;
    int hori_dist = rect_git.x - rect_studio.x - rect_studio.w / 2;
    
    for (int y = rect_studio.y; (y - LENGTH_DASH - LENGTH_GAP) >= (rect_git.y + rect_git.h / 2); y -= (LENGTH_DASH + LENGTH_GAP)) 
    {
      SDL_RenderDrawLine(renderer, 
                         rect_studio.x + rect_studio.w / 2, 
                         y - (offset_dash), 
                         rect_studio.x + rect_studio.w / 2, 
                         y - (LENGTH_DASH + offset_dash));
    }
    
    for (int x = rect_studio.x + rect_studio.w / 2; x < rect_git.x; x += (LENGTH_DASH + LENGTH_GAP)) 
    {
      SDL_RenderDrawLine(renderer, 
                         x + offset_dash, 
                         rect_git.y + rect_git.h / 2, 
                         x + LENGTH_DASH + offset_dash, 
                         rect_git.y + rect_git.h / 2);
    }
    
    SDL_Rect rect_groovy;
    rect_groovy.x = rect_studio.x + rect_studio.w / 2 - img_groovy->w * 1.2;
    rect_groovy.y = rect_studio.y;
    rect_groovy.w = img_groovy->w;
    rect_groovy.h = img_groovy->h;
      
    if (offset_studio_to_git <= vert_dist + rect_groovy.h * 1.2) {
      rect_groovy.y -= offset_studio_to_git;
    } else {
      rect_groovy.y = rect_studio.y - vert_dist - rect_groovy.h * 1.2;
      rect_groovy.x += offset_studio_to_git - (vert_dist + rect_groovy.h * 1.2);         
    }
    
    SDL_RenderCopy(renderer, img_groovy->tex, NULL, &rect_groovy);
    
    /*!
    ** the connection between studio and maven
    */
    for (int y = rect_studio.y; (y + LENGTH_DASH + LENGTH_GAP) <= (rect_maven.y + rect_maven.h / 2); y += (LENGTH_DASH + LENGTH_GAP)) 
    {
      SDL_RenderDrawLine(renderer, 
                         rect_studio.x + rect_studio.w / 2, 
                         y + (offset_dash), 
                         rect_studio.x + rect_studio.w / 2, 
                         y + (LENGTH_DASH + offset_dash));
    }
    
    for (int x = rect_studio.x + rect_studio.w / 2; x < rect_git.x; x += (LENGTH_DASH + LENGTH_GAP)) 
    {
      SDL_RenderDrawLine(renderer, 
                         x + offset_dash, 
                         rect_maven.y + rect_maven.h / 2, 
                         x + LENGTH_DASH + offset_dash, 
                         rect_maven.y + rect_maven.h / 2);
    }
    
    SDL_Rect rect_jar;
    rect_jar.x = rect_studio.x + rect_studio.w / 2 - img_groovy->w * 1.2;
    rect_jar.y = rect_studio.y + rect_studio.h - img_jar->h;
    rect_jar.w = img_jar->w;
    rect_jar.h = img_jar->h;
    
    if (offset_studio_to_maven <= vert_dist + rect_jar.h * 1.2) {
      rect_jar.y += offset_studio_to_maven;
    } else {
      rect_jar.y = rect_studio.y + rect_studio.h + vert_dist + rect_jar.h * 0.5;
      rect_jar.x += offset_studio_to_maven - (vert_dist + rect_jar.h * 1.2);         
    }
    SDL_RenderCopy(renderer, img_jar->tex, NULL, &rect_jar);
    
    /*!
    ** connections to developers
    */
    for (int x = rect_git.x + rect_git.w; (x + LENGTH_DASH + LENGTH_GAP) <= FRAME_WIDTH - margin; x += (LENGTH_DASH + LENGTH_GAP)) 
    {
      SDL_RenderDrawLine(renderer, 
                         x + offset_dash, 
                         rect_git.y + rect_git.h / 2, 
                         x + LENGTH_DASH + offset_dash, 
                         rect_git.y + rect_git.h / 2);
    }
    
    for (int x = rect_maven.x + rect_maven.w; (x + LENGTH_DASH + LENGTH_GAP) <= FRAME_WIDTH - margin; x += (LENGTH_DASH + LENGTH_GAP)) 
    {
      SDL_RenderDrawLine(renderer, 
                         x + offset_dash, 
                         rect_maven.y + rect_maven.h / 2, 
                         x + LENGTH_DASH + offset_dash, 
                         rect_maven.y + rect_maven.h / 2);
    }
    
    for (int y = rect_git.y + rect_git.h / 2; y < FRAME_HEIGHT - MARGIN_TOP / 3 - rect_developer2.h / 2; y += (LENGTH_DASH + LENGTH_GAP)) 
    {
      SDL_RenderDrawLine(renderer, 
                         FRAME_WIDTH - margin, 
                         y + offset_dash, 
                         FRAME_WIDTH - margin, 
                         y + (LENGTH_DASH + offset_dash));
    }
    
    for (int x = rect_developer1.x + rect_developer1.w + LENGTH_DASH + LENGTH_GAP; x <= FRAME_WIDTH - margin + LENGTH_DASH; x += (LENGTH_DASH + LENGTH_GAP)) 
    {
      SDL_RenderDrawLine(renderer, 
                         x - offset_dash, 
                         rect_developer1.y + rect_developer1.h / 2, 
                         x - (LENGTH_DASH + offset_dash), 
                         rect_developer1.y + rect_developer1.h / 2);
    }
    
    for (int x = rect_developer2.x + rect_developer2.w + LENGTH_DASH + LENGTH_GAP; x <= FRAME_WIDTH - margin + LENGTH_DASH; x += (LENGTH_DASH + LENGTH_GAP)) 
    {
      SDL_RenderDrawLine(renderer, 
                         x - offset_dash, 
                         rect_developer2.y + rect_developer2.h / 2, 
                         x - (LENGTH_DASH + offset_dash), 
                         rect_developer2.y + rect_developer2.h / 2);
    }
    
    
    // Update dash offset for animation
    offset_dash += 2.0;
    offset_studio_to_git += 2.0;
    offset_studio_to_maven += 2.0;
    
    // Reset dash offset when it exceeds the pattern length
    if (offset_dash > LENGTH_DASH + LENGTH_GAP) 
    {
      offset_dash = 0;
    }
    
    if (offset_studio_to_git > (vert_dist + hori_dist + rect_groovy.w * 2)) 
    {
      offset_studio_to_git = 0.0;
    }
    if (offset_studio_to_maven > (vert_dist + hori_dist + rect_jar.w * 2))
    {
      offset_studio_to_maven = 0.0;
    }

    // Present the renderer
    SDL_RenderPresent(renderer);
    SDL_Delay(1000 / 30);
  }
}