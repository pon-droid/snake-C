#include <SDL.h>

#define SCR_W 500
#define SCR_H 500
#define RECT_S 50
#define MAP_W 4
#define MAP_H 4

void draw_arr(int arr[], SDL_Renderer *rend) {
  int y, x;
  SDL_Rect rect;
  rect.h = RECT_S;
  rect.w = RECT_S;
  for (y = 0; y < MAP_H; y++) {
    rect.y = y * RECT_S;
    for (x = 0; x < MAP_W; x++) {
      rect.x = x * RECT_S;

      if (arr[y * MAP_W + x] == 1) {
        SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
      } else {
        SDL_SetRenderDrawColor(rend, 0, 255, 0, 255);
      }
      SDL_RenderDrawRect(rend, &rect);
    }
  }
}

int quit(void) {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      return 1;
    }
  }
  return 0;
}

void update(SDL_Renderer *rend) {
  SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
  SDL_RenderClear(rend);
}

int main(void) {
  SDL_Window *win =
      SDL_CreateWindow("snake", 0, 0, SCR_W, SCR_H, SDL_WINDOW_RESIZABLE);
  SDL_Renderer *rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_PRESENTVSYNC);

  int MAP[MAP_W * MAP_H] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  while (1) {
    if (quit()) {
      break;
    };
    update(rend);
    draw_arr(MAP, rend);
    SDL_RenderPresent(rend);
  }
}
