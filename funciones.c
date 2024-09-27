#include <stdio.h>
#include <stdlib.h>
#include "juego.h"

// Crear tablero con memoria din�mica
celula** crearTablero(unsigned int fil, unsigned int col) {
    // Reserva para las filas (punteros a cada fila)
    celula** vectorFilas = malloc(sizeof(celula*) * fil);
    if (!vectorFilas) {
        return NULL;
    }

    celula** punteroFila = vectorFilas;  // Puntero auxiliar para recorrer las filas

    // Reserva memoria para cada fila
    for (unsigned int x = 0; x < fil; x++, punteroFila++) {
        *punteroFila = calloc(col,sizeof(celula));

        // Si hay alg�n error, libero la memoria previamente asignada
        if (!*punteroFila) {
            while (punteroFila != vectorFilas) {
                punteroFila--;
                free(*punteroFila);
            }
            free(vectorFilas);
            return NULL;
        }
    }

    return vectorFilas;
}

//Destruye un tablero dinamico
void destruirTablero(celula** tablero, unsigned int fil) {
    if (tablero == NULL) {
        return;
    }

    // Puntero auxiliar para recorrer las filas
    celula** punteroFila = tablero;

    // Liberar cada fila usando aritm�tica de punteros
    for (unsigned int i = 0; i < fil; i++, punteroFila++) {
        free(*punteroFila);  // Liberar la fila actual
    }

    // Liberar el array de punteros a filas
    free(tablero);
}

// Actualiza los estados de las c�lulas
void actualizarTablero(celula** matriz, unsigned int fil, unsigned int col)
{
    for (unsigned int x = 0; x < fil; x++)
    {
        for (unsigned int y = 0; y < col; y++)
        {
            matriz[x][y].estadoActual = matriz[x][y].estadoFuturo;
            matriz[x][y].cantVecinosVivos = calCantVecinos(matriz, fil, col, x, y);
        }
    }
}

// Funci�n para imprimir el estado de una c�lula
void prtEstado(bool estado)
{
    printf("%c", (estado == true) ? 'm' : ' ');
}

// Esta funci�n recorre el tablero calculando los estados futuros de las c�lulas seg�n la cantidad de vecinos
void actualizarEstadosFuturos(celula** matriz, unsigned int fil, unsigned int col)
{
    for (unsigned int x = 0; x < fil; x++)
    {
        for (unsigned int y = 0; y < col; y++)
        {
            matriz[x][y].estadoFuturo = calEstadoFuturo(matriz, x, y);
        }
    }
}

// Calcula cu�l va a ser el estado futuro de una c�lula
bool calEstadoFuturo(celula** matriz, unsigned int x, unsigned int y)
{
    if (matriz[x][y].estadoActual == true)
    {
        return (matriz[x][y].cantVecinosVivos == 2 || matriz[x][y].cantVecinosVivos == 3) ? true : false;
    }
    else
    {
        return (matriz[x][y].cantVecinosVivos == 3) ? true : false;
    }
}

// Calcula la cantidad de vecinos vivos de una c�lula
unsigned char calCantVecinos(celula** matriz, unsigned int fil, unsigned int col, unsigned int posX, unsigned int posY)
{
    unsigned char cantVecinos = 0;

    unsigned int limiteLateralIzq = (posY > 0) ? posY - 1 : 0;
    unsigned int limiteSuperior = (posX > 0) ? posX - 1 : 0;
    unsigned int limiteLateralDer = (posY < (col - 1)) ? posY + 1 : col - 1;
    unsigned int limiteInferior = (posX < (fil - 1)) ? posX + 1 : fil - 1;

    for (unsigned int x = limiteSuperior; x <= limiteInferior; x++)
    {
        for (unsigned int y = limiteLateralIzq; y <= limiteLateralDer; y++)
        {
            if (!(x == posX && y == posY))
            {
                if (matriz[x][y].estadoFuturo != 0)
                {
                    cantVecinos++;
                }
            }
        }
    }

    return cantVecinos;
}

// Convierte una matriz plantilla de 1s y 0s en un tablero
void cargarTablero(celula** matriz, unsigned int fil, unsigned int col)
{
    for (unsigned int x = 0; x < fil; x++)
    {
        for (unsigned int y = 0; y < col; y++)
        {
            matriz[x][y].cantVecinosVivos = calCantVecinos(matriz, fil, col, x, y);
            matriz[x][y].estadoFuturo = calEstadoFuturo(matriz, x, y);
        }
    }
}
