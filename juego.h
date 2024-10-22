#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include <stdbool.h>

typedef struct {
    bool estadoActual;
    bool estadoFuturo;
    unsigned char cantVecinosVivos;
} celula;

//Funcion para imprimir el tablero
void printTablero(celula** matriz, unsigned int fil, unsigned int col);

//Calcula la cantidad de vecinos vivos en una celda
unsigned char calCantVecinos(celula** matriz, unsigned int fil, unsigned int col, unsigned int posX, unsigned int posY);

//Calcula el estado futuro de una celda
bool calEstadoFuturo(celula** matriz, unsigned int x, unsigned int y);

// Función que actualiza el tablero, pasando los estados futuros a actuales
void actualizarTablero(celula** matriz, unsigned int fil, unsigned int col);

//Crea un nuevo tablero dinamico de celdas
celula** crearTablero(unsigned int fil, unsigned int col);

//Destruye un tablero dinamico
void destruirTablero(celula** tablero, unsigned int fil);

//Lee desde un archivo un tablero
bool cargaTablero(celula** tablero, const char* nombreDelArchivo, int centroX, int centroY, unsigned int fil, unsigned int col);

#endif // JUEGO_H_INCLUDED


