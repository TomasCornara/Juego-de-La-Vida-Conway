#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifdef __MINGW32__
#endif
#include <SDL.h>
#include "juego.h"
#define CELL_HEIGHT 10
#define CELL_WIDTH 10

int main(int argc, char *argv[])
{
    ///BLOQUE DECLARACION
    int tableroCarga[MAX_FIL][MAX_COL] =
    {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0}, // Fila 1
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0}, // Fila 2
        {0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1}, // Fila 3
        {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1}, // Fila 4
        {1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // Fila 5
        {1,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0}, // Fila 6
        {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0}, // Fila 7
        {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // Fila 8
        {0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // Fila 9
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // Fila 10
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // Fila 11
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // Fila 12
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // Fila 13
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}  // Fila 14
    };
    celula tablero[MAX_FIL][MAX_COL];
    cargarTablero(tableroCarga, tablero, 14, 36);
    unsigned char done;
    unsigned int k = 0;
    unsigned int cantGen = 0;
    unsigned int temp;
    char titulo[50];

    ///BLOQUE PARAMETROS
    int delay               = 100;
    SDL_Window* window      = NULL;
    SDL_Renderer* renderer  = NULL;
    SDL_Event e;
    SDL_Rect fillRect;

    ///BLOQUE PROGRAMA
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL No se ha podido inicializar! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    //Create window
    window = SDL_CreateWindow("Juego de la vida",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              640,
                              480,
                              SDL_WINDOW_SHOWN);
    if (!window)
    {
        SDL_Log("Error en la creacion de la ventana: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // Creamos el lienzo
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        SDL_Log("No se ha podido crear el lienzo! SDL Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    while (!done)
    {
        // Procesar eventos SDL
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                done = 1;
            }
        }

        // Limpiar la pantalla
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);

        // Dimensiones del rectángulo
        fillRect.h = CELL_HEIGHT;  // Alto de cada célula
        fillRect.w = CELL_WIDTH;   // Ancho de cada célula

        // Dibujar cada célula en la matriz
        for (int i = 0; i < MAX_FIL; ++i)
        {
            for (int j = 0; j < MAX_COL; ++j)
            {
                // Ajustar la posición del rectángulo
                fillRect.x = j * CELL_WIDTH;
                fillRect.y = i * CELL_HEIGHT;

                // Elegir el color según el estado de la célula
                if (tablero[i][j].estadoActual == true)
                {
                    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF); // Verde para célula viva
                }
                else
                {
                    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF); // Negro para célula muerta
                }

                // Dibujar la célula
                SDL_RenderFillRect(renderer, &fillRect);
            }
        }

        // Actualizar el lienzo
        SDL_RenderPresent(renderer);

        // Procesar la lógica del juego (actualizar estados y tablero)
        actualizarEstadosFuturos(tablero, 14, 36); // Función que calcula el estado futuro
        actualizarTablero(tablero, 14, 36);        // Función que aplica los estados futuros

        // Retraso para controlar la velocidad de actualización
        SDL_Delay(delay);

        // Actualizar título de la ventana
        snprintf(titulo, sizeof(titulo), "Juego De La Vida. Generacion: %d", k);
        SDL_SetWindowTitle(window, titulo);

                // Si ya se alcanzó el número de generaciones, preguntar cuántas más generar
        if (cantGen == k)
        {
            printf("Cuantas generaciones quiere generar? ");
            scanf("%d", &temp);
            cantGen += temp;
        }

        // Procesar eventos SDL
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                done = 1;
            }
        }


        k++;
    }


    //destruyo todos los elementos creados
    //Observar ni mas ni menos que destructores, en la asignatura no inventamos nada!
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


