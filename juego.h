#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include <stdbool.h>

typedef struct {
    bool estadoActual;
    unsigned char estadoFuturo;
    unsigned char cantVecinosVivos;
} celula;

// Funci�n para cargar un tablero origen en un tablero destino de celdas
void cargarTablero(celula** matriz, unsigned int fil, unsigned int col);

// Funci�n para imprimir el tablero
void printTablero(celula** matriz, unsigned int fil, unsigned int col);

// Funci�n para calcular la cantidad de vecinos vivos en una celda
unsigned char calCantVecinos(celula** matriz, unsigned int fil, unsigned int col, unsigned int posX, unsigned int posY);

// Funci�n para actualizar los estados futuros de las celdas
void actualizarEstadosFuturos(celula** matriz, unsigned int fil, unsigned int col);

// Funci�n que calcula el estado futuro de una celda
bool calEstadoFuturo(celula** matriz, unsigned int x, unsigned int y);

// Funci�n que actualiza el tablero, pasando los estados futuros a actuales
void actualizarTablero(celula** matriz, unsigned int fil, unsigned int col);

// Funci�n para imprimir el estado de una celda (viva o muerta)
void prtEstado(bool estado);

// Funci�n para crear un nuevo tablero de celdas
celula** crearTablero(unsigned int fil, unsigned int col);

//Destruye un tablero dinamico
void destruirTablero(celula** tablero, unsigned int fil);

#endif // JUEGO_H_INCLUDED


