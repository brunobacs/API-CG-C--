#include <SDL2/SDL.h>
#include "primitives.h"

using namespace std;

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
// desenha está dando erro de ponto flutuante, deve ser por conta do calculo do y com muita divisao
    int xant = 0;
    int yant = 0;

    for (int x = 0; x<surface->w; x++){

        int y = (int) 100*sin(x/16) + (int) surface->h/2;
        dda(surface, xant, yant, floor(x), floor(y), 255);
        xant = x;
        yant = y;
    }

}

void dda (SDL_Surface* surface, int xi, int yi, int xf, int yf, int intensidade){
    int dx = xf - xi;
    int dy = yf - yi;

    if (abs(dx) > abs(dy)){
        int passos = abs(dx);
    }
    
    int passos = abs(dy);
    

    int passo_x = dx/passos;
    int passo_y = dy/passos;

    int  x = xi;
    int  y = yi;

    set_pixel(surface, round(x), round(y), intensidade);

    for (int p = 0; p < passos; p++){
        x = x + passo_x;
        y = y + passo_y;

        set_pixel(surface, round(x), round(y), intensidade);
    }

}

