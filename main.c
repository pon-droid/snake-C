#include <SDL.h>
#include <stdio.h>
#define SCR_W 500
#define SCR_H 500
#define RECT_S 50
#define CELL_W (SCR_W/MAP_W)
#define CELL_H (SCR_H/MAP_H)
#define MAP_W 20
#define MAP_H 20
#define YS 1
#define XS 1

typedef struct Body {
  struct Body *b;
  int x, y;
  int dx, dy;
} Body;

typedef struct Snake {
  int x, y;
  //Direction
  int dx, dy;
  
} Snake;

void draw_arr(int arr[], SDL_Renderer *rend) {
  int y, x;
  SDL_Rect rect;
  rect.h = CELL_H;
  rect.w = CELL_W;
  for (y = 0; y < MAP_H; y++) {
    rect.y = y * CELL_H;
    for (x = 0; x < MAP_W; x++) {
      rect.x = x * CELL_W;

      if (arr[y * MAP_W + x] == 1) {
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
      } else {
        SDL_SetRenderDrawColor(rend, 0, 255, 0, 255);
      }
      if (arr[y * MAP_W + x] == 2){
	SDL_SetRenderDrawColor(rend, 0, 0, 255, 255);
      }
      SDL_RenderFillRect(rend, &rect);
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

void mouse(int* MAP){
  int x, y;
  Uint32 keys = SDL_GetMouseState(&x, &y);
  int nx = x/CELL_W;
  int ny = y/CELL_H;
  if((keys & SDL_BUTTON_LMASK) != 0){
    MAP[ny*MAP_W+nx] = 1;
  }
  if((keys & SDL_BUTTON_RMASK) != 0){
    MAP[ny*MAP_W+nx] = 0;
  }
  
  //printf("X: %d, Y: %d\n",x/RECT_S,y/RECT_S);
  
}

Snake new_snake(void){
  Snake new;
  new.x = MAP_W/2;
  new.y = MAP_H/2;
  new.dx = 0;
  new.dy = 0;
  return new;
}

Body new_body(void){
  Body new;
  new.x = MAP_W/2;
  new.y = MAP_H/2;
  new.dx = 0;
  new.dy = 0;
  new.b = 0;
  return new;
}

void  body_man(Body *body, int MAP[], Snake *s){
  body->x = s->dx + s->x;
  body->y = s->dy + s->y;

  MAP[body->y*MAP_W+body->x] = 2;
  s->dy = 0;
  s->dx = 0;
}
  

void snake_man(Snake *s, int MAP[]){
  const Uint8* keys = SDL_GetKeyboardState(NULL);

  int UP, DOWN, LEFT, RIGHT;

  UP = (s->y - YS);
  DOWN = (s->y + YS);
  RIGHT = (s->x + XS);
  LEFT = (s->x - XS);

  
  if(keys[SDL_SCANCODE_UP] && UP < MAP_H && UP >= 0){
    // MAP[s->y*MAP_W+s->x] = 1;
    s->y = UP;
    s->dy = 1;
    // s->dx = 0;
    
  }
  if(keys[SDL_SCANCODE_RIGHT] && RIGHT < MAP_W && RIGHT >= 0){
    // MAP[s->y*MAP_W+s->x] = 1;
    s->x = RIGHT;
    s->dx = -1;
    // s->dy = 0;
  }
  if(keys[SDL_SCANCODE_DOWN] && DOWN < MAP_H && DOWN >= 0){
    // MAP[s->y*MAP_W+s->x] = 1;
    s->y = DOWN;
    s->dy = -1;
    // s->dx = 0;
    
  }
  if(keys[SDL_SCANCODE_LEFT] && LEFT < MAP_W && LEFT >= 0){
    //  MAP[s->y*MAP_W+s->x] = 1;
    s->x = LEFT;
    s->dx = 1;
    // s->dy = 0;
    
  }
  /*
  if(s->dx == s->dy && s->dx != 0){
    MAP[s->y*MAP_W+s->x] = 0;
    return;
  }
  */
  MAP[s->y*MAP_W+s->x] = 1;
}


  

int main(void) {
  SDL_Window *win =
      SDL_CreateWindow("snake", 0, 0, SCR_W, SCR_H, SDL_WINDOW_RESIZABLE);
  SDL_Renderer *rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_PRESENTVSYNC);

  int MAP[MAP_W * MAP_H] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  
  Snake snake = new_snake();
  Body body = new_body();
  while (1) {
    SDL_Delay(75);
    if (quit()) {
      break;
    };
    update(rend);
    mouse(MAP);
    snake_man(&snake, MAP);
    body_man(&body, MAP, &snake);
    draw_arr(MAP, rend);
    //Clean board
    memset(MAP, 0, sizeof(int)*(MAP_W * MAP_H));
    SDL_RenderPresent(rend);
  }
}
