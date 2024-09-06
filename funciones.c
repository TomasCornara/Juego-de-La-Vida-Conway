#include <stdio.h>
#include <stdlib.h>
#include "juego.h"

//Actualiza los vecinos en las celulas
void actualizarVecinos(celula matriz[MAX_FIL][MAX_COL], unsigned int fil, unsigned int col)
{
    for (unsigned int x = 0; x < fil; x++)
    {
        for (unsigned int y = 0; y < col; y++)
        {
            matriz[x][y].cantVecinosVivos = calCantVecinos(matriz,fil,col,x,y);
        }
    }
}

//Actualiza los estados de las celulas
void actualizarEstadosCelulas(celula matriz[MAX_FIL][MAX_COL], unsigned int fil, unsigned int col)
{
    for (unsigned int x = 0; x < fil; x++)
    {
        for (unsigned int y = 0; y < col; y++)
        {
            matriz[x][y].estadoActual = matriz[x][y].estadoFuturo;
        }
    }
}

void actualizarEstadosFuturos(celula matriz[MAX_FIL][MAX_COL], unsigned int fil, unsigned int col)
{
    for (unsigned int x = 0; x < fil; x++)
    {
        for (unsigned int y = 0; y < col; y++)
        {
            matriz[x][y].estadoFuturo = calEstadoFuturo(matriz, x, y);
        }
    }
}

//Calcula cual va a ser el estado futuro de una celula
int calEstadoFuturo(celula matriz[MAX_FIL][MAX_COL],unsigned int x, unsigned int y)
{
    if (matriz[x][y].estadoActual == 1)
    {
        // Si la célula está viva
        return (matriz[x][y].cantVecinosVivos == 2 || matriz[x][y].cantVecinosVivos == 3) ? 1 : 0;
    }
    else
    {
        // Si la célula está muerta
        return (matriz[x][y].cantVecinosVivos == 3) ? 1 : 0;
    }
}

//Celcula la cantidad de vecinos vivos de una celula
char calCantVecinos(celula matriz[MAX_FIL][MAX_COL], unsigned int fil, unsigned int col, unsigned int posX, unsigned int posY)
{
    char cantVecinos = 0;

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
                if (matriz[x][y].estadoActual != 0)
                {
                    cantVecinos++;
                }
            }
        }
    }

    return cantVecinos;
}

char calCantVecinosInt(int matriz[MAX_FIL][MAX_COL], unsigned int fil, unsigned int col, unsigned int posX, unsigned int posY)
{
    char cantVecinos = 0;

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
                if (matriz[x][y] != 0)
                {
                    cantVecinos++;
                }
            }
        }
    }

    return cantVecinos;
}

//Convierte una matriz plantilla de 1s y 0s en un tablero
void cargarTablero(int origen[MAX_FIL][MAX_COL], celula destino[MAX_FIL][MAX_COL], unsigned int fil, unsigned int col)
{
    for(unsigned int x = 0; x < fil; x++)
    {
        for(unsigned int y = 0; y < col; y++)
        {
            destino[x][y].estadoActual = origen[x][y];
            destino[x][y].cantVecinosVivos = calCantVecinosInt(origen,fil,col,x,y);
            destino[x][y].estadoFuturo = calEstadoFuturo(destino,x,y);
        }
    }
}

//Imprimir el tablero
void printTablero(celula matriz[MAX_FIL][MAX_COL], unsigned int fil, unsigned int col)
{
    for(unsigned int x = 0; x < fil; x++)
    {
        for(unsigned int y = 0; y < col; y++)
        {
            printf("%c", (matriz[x][y].estadoActual == 1) ? '#' : ' ');
        }
        printf("\n");
    }

}
