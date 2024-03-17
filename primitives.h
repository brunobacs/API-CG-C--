#ifndef primitives
#define primitives

using namespace std;

void set_pixel(SDL_Surface* surface, int x, int y, Uint8 intensity);
void dda_aa(SDL_Surface* surface, int xi, int yi, int xf, int yf, int intensidade);
void desenha(SDL_Surface* surface);



#endif