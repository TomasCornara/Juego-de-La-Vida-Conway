#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifdef __MINGW32__
#endif
#include <SDL.h>
#include "juego.h"
#define CELL_HEIGHT 5
#define CELL_WIDTH 5
#define TAM_TABLERO_W 256
#define TAM_TABLERO_H 144
#define CENTER_W TAM_TABLERO_W/2
#define CENTER_H TAM_TABLERO_H/2

int main(int argc, char *argv[])
{
    ///BLOQUE PARAMETROS PARA SDL
    int delay               = 100;
    SDL_Window* window      = NULL;
    SDL_Renderer* renderer  = NULL;
    SDL_Event e;
    SDL_Rect fillRect;

    ///BLOQUE DECLARACION
    unsigned char done = 0;
    unsigned int k = 0;
    unsigned int cantGen = 0;
    unsigned int random;
    int temp;
    char titulo[50];

    ///CREACION DEL TABLERO
    celula** tablero = crearTablero(TAM_TABLERO_H, TAM_TABLERO_W);
    if (!tablero)
    {
        printf("Error al crear el tablero.\n");
        return -1;
    }

    ///GENERACION DE UN TABLERO RANDOM
    //Calculo de estados random
    for(int aux = 0; aux < TAM_TABLERO_H; aux++)
    {
        for(int aux2 = 0; aux2 < TAM_TABLERO_W; aux2++)
        {
            random = rand()%2;
            tablero[aux][aux2].estadoFuturo = (random)? true : false; //Es importante que se cargue en el estado futuro por como funciona el programa
            tablero[aux][aux2].estadoActual = tablero[aux][aux2].estadoFuturo; //Aca cargo en el actual solo para que el primer frame no este vacio
        }
    }

    //Cargar tablero (Calculo de vecinos)
    cargarTablero(tablero, TAM_TABLERO_H, TAM_TABLERO_W);


    ///BLOQUE PROGRAMA (SDL)
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL No se ha podido inicializar! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    //Create window
    window = SDL_CreateWindow("Juego de la vida",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              1280,
                              720,
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

    ///RENDERIZADO
    do
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

        ///DIBUJAR LA MATRIZ
        for (int i = 0; i < TAM_TABLERO_H; ++i)
        {
            for (int j = 0; j < TAM_TABLERO_W; ++j)
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
        actualizarEstadosFuturos(tablero, TAM_TABLERO_H, TAM_TABLERO_W); // Función que calcula el estado futuro
        actualizarTablero(tablero, TAM_TABLERO_H, TAM_TABLERO_W);        // Función que aplica los estados futuros

        // Retraso para controlar la velocidad de actualización
        SDL_Delay(delay);

        // Actualizar título de la ventana
        snprintf(titulo, sizeof(titulo), "Juego De La Vida. Generacion: %d", k);
        SDL_SetWindowTitle(window, titulo);

        // Si ya se alcanzó el número de generaciones, preguntar cuántas más generar
        if (cantGen == k)
        {
            system("cls");
            do
            {
                printf("Cuantas generaciones quiere generar? ");
                scanf("%d", &temp);

                if (temp <= 0)
                {
                    printf("Error: el numero tiene que ser mayor que 0.\n");
                }
            }
            while (temp <= 0);

            cantGen += temp;
        }


        k++;

    }
    while(!done);

    ///Liberaciones de SDL
    //destruyo todos los elementos creados
    //Observar ni mas ni menos que destructores, en la asignatura no inventamos nada!
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    ///Liberacion del tablero
    destruirTablero(tablero,TAM_TABLERO_W);

    return 0;
}


