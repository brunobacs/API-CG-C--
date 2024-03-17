#include <iostream>
#include <SDL2/SDL.h>
#include "primitives.h"

using namespace std;


int main(){

    // Inicializa o SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Cria janela
    SDL_Window* window = SDL_CreateWindow("SDL Pixel Drawing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Cria o renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Cria textura (nao sei se é necessário agora)
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 640, 480);
    if (texture == nullptr) {
        std::cerr << "Texture could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Cria a superficie em que vamos manipular os pixels, a matriz onde vamos jogar o nosso desenho
    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, 640, 480, 32, SDL_PIXELFORMAT_ARGB8888);
    if (surface == nullptr) {
        std::cerr << "Surface could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }


// aqui a gente desenha com as primitivas

    // desenha(surface); // ta dando erro no ponto flutuante, nao vi como ajeitar ainda
    // dda_aa (surface, 0, 0, 100, 300, 255);
    // dda_aa (surface, 300, 100, 10, 10, 255);
    // dda_aa (surface, 150, 200, 630, 10, 255);

    // set_pixel(surface, 610, 460, 255);
    // set_pixel(surface, 161, 101, 255);
    // set_pixel(surface, 162, 102, 255);
    // set_pixel(surface, 163, 103, 255);


    // atualiza textura com a superficie
    SDL_UpdateTexture(texture, NULL, surface->pixels, surface->pitch);

    // renderiza a textura na janela
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    // atualiza tela pra mostrar mudanças
    SDL_UpdateWindowSurface(window);

    // espera o usuario fechar a janela no x
    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        if (event.type == SDL_QUIT) {
            break;
        }
    }

    // limpa tela e libera as memórias
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_FreeSurface(surface);
    SDL_Quit();

    return 0;
}