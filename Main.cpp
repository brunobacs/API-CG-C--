#include <iostream>
#include <SDL2/SDL.h>
#include "primitives.h"
#include <vector>
#include <utility>

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

// teste poligono

    vector<pair<int, int>> pol;
    insertPoint(pol, 400, 500);
    insertPoint(pol, 500, 300);
    insertPoint(pol, 300, 300);

    // Assuming pixels is your SDL_Surface*
    poligono(surface, pol, (255, 255, 255)); // White color


    // teste bresenham

    //bresenham(surface, 10, 10, 500, 500, (255,255,255));

    // desenha(surface); 
    //teste 1
    // dda_aa (surface, 20, 20, 50, 50, 255); //45 graus
    // dda_aa (surface, 80, 80, 30, 30, 255); // 45 graus ao contrario

    // dda_aa (surface, 40, 40, 150, 390, 255);
    // dda_aa (surface, 20, 400, 120, 10, 255);

    // dda_aa (surface, 30, 30, 450, 30, 255); // reta no y 30
    // dda_aa (surface, 450, 450, 40, 450, 255); // reta voltando no 450

    // dda_aa (surface, 160, 40, 160, 400, 255); // reta vertical x= 160
    // dda_aa (surface, 20, 20, 50, 50, 255);

    // dda_aa (surface, 590, 400, 590, 50, 255); // reta vertical voltando x = 590

    // dda_aa (surface, 500, 40, 200, 310, 255);
    // dda_aa (surface, 450, 450, 200, 200, 255);

// teste 2
    // dda_aa (surface, 100, 100, 280, 140, 255); // maior que 45 graus = erro
    // dda_aa (surface, 100, 100, 280, 280, 255); // 45 graus
    // dda_aa (surface, 100, 100, 200, 380, 255); // menor q 45 == erro
    // dda_aa (surface, 110, 380, 580, 200, 255);
    // dda_aa (surface, 580, 200, 210, 10, 255);
    // dda_aa (surface, 580, 40, 480, 400, 255);
    // dda_aa (surface, 210, 380, 500, 40, 255);
    // dda_aa (surface, 40, 20, 210, 410, 255);

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