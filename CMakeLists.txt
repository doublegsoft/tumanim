##
##  _                               _           
## | |_ _   _ _ __ ___   __ _ _ __ (_)_ __ ___  
## | __| | | | '_ ` _ \ / _` | '_ \| | '_ ` _ \ 
## | |_| |_| | | | | | | (_| | | | | | | | | | |
##  \__|\__,_|_| |_| |_|\__,_|_| |_|_|_| |_| |_|
##                                              
##

cmake_minimum_required(VERSION 3.6)

project(tumanim VERSION 1.0.0 DESCRIPTION "hand coded 2D animation")

if (APPLE)
  set(BUILD "build/darwin")
endif(APPLE)

set(SDL           "../SDL-2.28.5")
set(SDL_IMAGE     "../SDL_image-2.8.2")

include_directories(
  "src"
  "${SDL}/${BUILD}/include"
  "${SDL}/${BUILD}/include-config-/SDL2"
  "${SDL}/${BUILD}/include/SDL2"
  "${SDL_IMAGE}/include"
)

link_directories(
  "${SDL}/${BUILD}"
  "${SDL_IMAGE}/${BUILD}"
)

set(SOURCES
  "src/tumanim.c"
  "src/tumanim-util.c"
  "src/tumanim-image.c"
  "src/tumanim-renderer.c"
#  "src/diagram/modelbase.c"
  "src/diagram/goalkeeper.c"
)

add_executable(tumanim
  ${SOURCES}
)

target_link_libraries(tumanim PRIVATE
  SDL2-2.0.0
  SDL2_image
)
