#include <SDL2/SDL.h>
#include "primitives.h"

using namespace std;


int sign (int numero){
    if (numero > 0){
        return numero;
    }
    return -1*numero;
}

// Function to set a pixel at (x, y) with the given intensity
void set_pixel(SDL_Surface* surface, int x, int y, Uint8 intensity) {

    if (x < 0 || x >= surface->w || y < 0 || y >= surface->h) {
        return;  // Ignore pixels outside the screen
    }

    Uint32 color = SDL_MapRGB(surface->format, intensity, intensity, intensity);
    Uint32* pixels = (Uint32*)surface->pixels;
    pixels[(y * surface->pitch) / sizeof(Uint32) + x] = color;
}


void desenha(SDL_Surface* surface){
  
    int xant = 320;
    int yant = 240;

    float wave_factor = 16;
    for (int x = 0; x<surface->w; x++){
        float y = 100 * sin(x/wave_factor) + surface->h / 2;
        dda_aa(surface, xant, yant, floor(x), floor(y), 255);
        xant = x;
        yant = y;
    }

}

void dda_aa (SDL_Surface* surface, int xi, int yi, int xf, int yf, int intensidade){
    int dx = xf - xi;
    int dy = yf - yi;
    int passos = 1;

    if (abs(dx) > abs(dy)){
        passos = abs(dx);
    }else {
        passos = abs(dy);
    }
    
    int passo_x= floor(dx/passos);
    int passo_y = floor(dy/passos);

    int  x = xi;
    int  y = yi;

    set_pixel(surface, round(x), round(y), intensidade);

    for (int p = 0; p < passos+1; p++){
        x = x + passo_x;
        y = y + passo_y;

        if (passo_x == 1){
            int prop = abs(y - floor(y));
            set_pixel(surface, floor(x), floor(y), round((1-prop)*intensidade));
            set_pixel(surface, floor(x), floor(y + sign(passo_y)), round((prop)*intensidade));
        }else {
            int prop = abs(x - floor(x));

            set_pixel(surface, floor(x), floor(y), round((1-prop)*intensidade));
            set_pixel(surface, floor(x + sign(passo_x)), floor(y), round((prop)*intensidade));
        }
        set_pixel(surface, round(x), round(y), intensidade);
    }

}

