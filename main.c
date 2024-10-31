#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#ifdef __MINGW32__
#endif
#include <SDL2/SDL.h>
#include "juego.h"
#define CELL_HEIGHT 3
#define CELL_WIDTH 3
#define RES_H 720
#define RES_W 1280
#define TAM_TABLERO_W 600
#define TAM_TABLERO_H 300
#define CENTER_W RES_W/CELL_HEIGHT/2
#define CENTER_H RES_H/CELL_WIDTH/2

int main(int argc, char *argv[])
{
    ///BLOQUE PARAMETROS PARA SDL
    int delay               = 50;
    SDL_Window* window      = NULL;
    SDL_Renderer* renderer  = NULL;
    SDL_Event e;
    SDL_Rect fillRect;
    SDL_Surface *icon;

    ///BLOQUE DECLARACION
    unsigned char done = 0;
    unsigned int k = 0;
    unsigned int cantGen = 0;
    int temp;
    char titulo[50];
    char tableroNombre[100];

    ///Verifico que se haya ingresado algun tablero por parametros
    if (argc < 2) {
        printf("Error. No se ingreso un tablero.\n");
        return -1;
    }

    //Verifico el largo del nombre
    if(strlen(argv[1]) > 95){
        printf("Error. Nombre de archivo es demasiado largo. Pruebe cambiando el nombre de este por uno mas corto.\n");
        return -1;
    }

    strcpy(tableroNombre,argv[1]); //Paso el nombre del archivo al buffer "tablero"

    ///Si el user se olvido de agregar el formato, se lo agrego yo
    if(strstr(tableroNombre,".txt") == NULL){
        strcat(tableroNombre,".txt");
    }

    ///CREACION DEL TABLERO
    celula** tablero = crearTablero(TAM_TABLERO_H, TAM_TABLERO_W);
    if (!tablero)
    {
        printf("Error al crear el tablero.\n");
        return -1;
    }

    ///CARGA DE UN TABLERO DESDE UN ARCHIVO
    if (!cargaTablero(tablero, tableroNombre, CENTER_H, CENTER_W,TAM_TABLERO_H,TAM_TABLERO_W))
    {
        printf("Error al cargar el tablero desde el archivo.\n");
        destruirTablero(tablero, TAM_TABLERO_H);
        return -1;
    }


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
                              RES_W,
                              RES_H,
                              SDL_WINDOW_SHOWN); //SDL_WINDOW_BORDERLESS
    if (!window)
    {
        SDL_Log("Error en la creacion de la ventana: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    //Establece icono
    icon = SDL_LoadBMP("icon.bmp");
    if (!icon) {
        printf("Error cargando icono: %s\n", SDL_GetError());
    } else {
        SDL_SetWindowIcon(window, icon);  // Establece el icono en la ventana
        SDL_FreeSurface(icon); // Liberar el recurso una vez asignado
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
            //Comprueba si el usuario cierra la ventana
            if (e.type == SDL_QUIT)
            {
                done = 1;
            }

            else if (e.type == SDL_KEYDOWN)
            {
                // Comprobar si la tecla es la tecla Escape
                if (e.key.keysym.sym == SDLK_ESCAPE)
                {
                    done = 1;  // Terminar el programa cuando se presiona Escape
                }
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
                // Ajustar la posicion del rectangulo
                fillRect.x = j * CELL_WIDTH;
                fillRect.y = i * CELL_HEIGHT;

                // Elegir el color segun el estado de la celula
                if (tablero[i][j].estadoActual)
                {
                    SDL_SetRenderDrawColor(renderer, 0xB3, 0xB3, 0xB3, 0xB3); // Gris para celula viva
                }
                else
                {
                    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF); // Negro para celula muerta
                }

                // Dibujar la celula
                SDL_RenderFillRect(renderer, &fillRect);
            }
        }

        // Actualizar el lienzo
        SDL_RenderPresent(renderer);

        // Procesar la lógica del juego (actualizar estados y tablero)
        actualizarTablero(tablero, TAM_TABLERO_H, TAM_TABLERO_W);

        // Retraso para controlar la velocidad de actualización
        SDL_Delay(delay);

        // Actualizar titulo de la ventana
        snprintf(titulo, sizeof(titulo), "Juego De La Vida. Generacion: %d", k);
        SDL_SetWindowTitle(window, titulo);

        // Si ya se alcanzo el numero de generaciones, preguntar cuántas más generar
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
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    ///Liberacion del tablero
    destruirTablero(tablero,TAM_TABLERO_H);

    return 0;
}


