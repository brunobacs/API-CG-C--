#include <SDL2/SDL.h>
#include "primitives.h"

using namespace std;


int sign (int numero){
    if (numero > 0){
        return 1;
    }else if (numero == 0){
        return 0;
    }else {
        return -1;
    }
}

// Function to set a pixel at (x, y) with the given intensity
void set_pixel(SDL_Surface* surface, int x, int y, Uint8 intensity) {

    if (x < 0 || x >= surface->w || y < 0 || y >= surface->h) {
        return;  
    }

    Uint32 color = SDL_MapRGB(surface->format, intensity, intensity, intensity);
    Uint32* pixels = (Uint32*)surface->pixels;
    pixels[(y * surface->pitch) / sizeof(Uint32) + x] = color;
}


void desenha(SDL_Surface* surface){
  
    int xant = 320;
    double yant = 240;

    double wave_factor = 16;
    for (int x = 0; x<(surface->w-1); x++){
        double y = 100 * sin(x/wave_factor) + surface->h / 2;
        dda_aa(surface, xant, yant, x, floor(y), 255);
        xant = x;
        yant = y;
    }

}

void dda_aa (SDL_Surface* surface, int xi, int yi, int xf, int yf, int intensidade){
    double dx = xf - xi;
    double dy = yf - yi;
    double passos = max(abs(dx), abs(dy));
    
    double passo_x = dx/passos;
    double passo_y = dy/passos; 

    double  x = xi;
    double  y = yi;

    set_pixel(surface, floor(x), floor(y), intensidade);

    for (int p = 0; p < passos; p++){
        x = x + passo_x;
        y = y + passo_y;

        if (passo_x == 1){
            double prop = abs(y - floor(y));
            set_pixel(surface, floor(x), floor(y), round((1-prop)*intensidade));
            set_pixel(surface, floor(x), floor(y + sign(passo_y)), round((prop)*intensidade));
        }else{
            double prop = abs(x - floor(x));
            set_pixel(surface, floor(x), floor(y), round((1-prop)*intensidade));
            set_pixel(surface, floor(x + sign(passo_x)), floor(y), round((prop)*intensidade));
        }
        
        set_pixel(surface, floor(x), floor(y), intensidade);
    }

}

