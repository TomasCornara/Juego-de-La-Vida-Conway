#include <stdio.h>
#include <stdlib.h>
#include "juego.h"

//Leer tablero
bool cargaTablero(celula** tablero, char* archivoName, int centroX, int centroY, unsigned int fil, unsigned int col)
{
    int coordenadaX, coordenadaY;

    // Abro el archivo
    FILE* archivo = fopen(archivoName, "rt");
    if (!archivo)  // Chequeo si se pudo abrir el archivo
    {
        return false; //Devuelvo false porque hubo un error
    }

    // Si se encuentra el archivo, leo las coordenadas y actualizo el tablero
    while (fscanf(archivo, "%d,%d", &coordenadaX, &coordenadaY) != EOF)
    {

        tablero[coordenadaX + centroX][coordenadaY + centroY ].estadoActual = true;  // Cargo el estado
    }

    // Cierro el archivo
    fclose(archivo);

    // Les calculo sus vecinos
    for (unsigned int x = 0; x < fil; x++)
    {
        for (unsigned int y = 0; y < col; y++)
        {
            tablero[x][y].cantVecinosVivos = calCantVecinos(tablero, fil, col, x, y);
            tablero[x][y].estadoFuturo = calEstadoFuturo(tablero, x, y);
        }
    }

    return true;  // Salió true porque salio todo bien
}


// Crear tablero con memoria dinámica usando calloc
celula** crearTablero(unsigned int fil, unsigned int col)
{
    // Reserva para las filas (punteros a cada fila) usando calloc
    celula** vectorFilas = calloc(fil, sizeof(celula*));
    if (!vectorFilas)
    {
        return NULL;
    }

    celula** punteroFila = vectorFilas;  // Puntero auxiliar para recorrer las filas

    // Reserva memoria para cada fila
    for (unsigned int x = 0; x < fil; x++, punteroFila++)
    {
        *punteroFila = calloc(col, sizeof(celula));

        // Si hay algun error, libero la memoria previamente asignada
        if (!*punteroFila)
        {
            while (punteroFila != vectorFilas)
            {
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
void destruirTablero(celula** tablero, unsigned int fil)
{
    if (tablero == NULL)
    {
        return;
    }

    // Liberar cada fila
    for (unsigned int i = 0; i < fil; i++)
    {
        free(tablero[i]);  // Liberar la fila actual
    }

    // Liberar el array de punteros a filas
    free(tablero);
}

// Actualiza los estados de las células
void actualizarTablero(celula** matriz, unsigned int fil, unsigned int col)
{
    // Actualiza el estado actual basado en el futuro
    for (unsigned int x = 0; x < fil; x++)
    {
        for (unsigned int y = 0; y < col; y++)
        {
            matriz[x][y].estadoActual = matriz[x][y].estadoFuturo;
        }
    }

    //Actualiza la cantidad de vecinos vivos para cada célula y luego su estado futuro
    for (unsigned int x = 0; x < fil; x++)
    {
        for (unsigned int y = 0; y < col; y++)
        {
            matriz[x][y].cantVecinosVivos = calCantVecinos(matriz, fil, col, x, y);
            matriz[x][y].estadoFuturo = calEstadoFuturo(matriz, x, y);
        }
    }
}

// Calcula cuál va a ser el estado futuro de una célula
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

// Calcula la cantidad de vecinos vivos de una célula
unsigned char calCantVecinos(celula** matriz, unsigned int fil, unsigned int col, unsigned int posX, unsigned int posY)
{
    unsigned char cantVecinos = 0;

    // Definir los límites de la submatriz
    unsigned int limiteLateralIzq = (posY > 0) ? posY - 1 : 0;
    unsigned int limiteSuperior = (posX > 0) ? posX - 1 : 0;
    unsigned int limiteLateralDer = (posY < (col - 1)) ? posY + 1 : col - 1;
    unsigned int limiteInferior = (posX < (fil - 1)) ? posX + 1 : fil - 1;

    // Recorrer la submatriz
    for (unsigned int x = limiteSuperior; x <= limiteInferior; x++)
    {
        for (unsigned int y = limiteLateralIzq; y <= limiteLateralDer; y++)
        {
            // No contar la posición central
            if (!(x == posX && y == posY))
            {
                // Sumar el estado actual (1 si está viva, 0 si no)
                cantVecinos += matriz[x][y].estadoActual;
            }
        }
    }

    return cantVecinos;
}
