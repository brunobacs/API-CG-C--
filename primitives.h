#ifndef primitives
#define primitives
#include <vector>
#include <utility>

using namespace std;

void set_pixel(SDL_Surface* surface, int x, int y, Uint8 intensity);
void dda_aa(SDL_Surface* surface, int xi, int yi, int xf, int yf, int intensidade);
void desenha(SDL_Surface* surface);
void bresenham (SDL_Surface* pixels, int xi, int yi, int xf, int yf, int intensidade);
void insertPoint(vector<pair<int, int>>& pol, int x, int y);
void poligono(SDL_Surface* surface, vector<pair<int, int>>& pol, int intensidade);



#endif