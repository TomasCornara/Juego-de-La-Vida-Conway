#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include <stdbool.h>

typedef struct {
    bool estadoActual;
    unsigned char estadoFuturo;
    unsigned char cantVecinosVivos;
} celula;

// Función para cargar un tablero origen en un tablero destino de celdas
void cargarTablero(celula** matriz, unsigned int fil, unsigned int col);

// Función para imprimir el tablero
void printTablero(celula** matriz, unsigned int fil, unsigned int col);

// Función para calcular la cantidad de vecinos vivos en una celda
unsigned char calCantVecinos(celula** matriz, unsigned int fil, unsigned int col, unsigned int posX, unsigned int posY);

// Función para actualizar los estados futuros de las celdas
void actualizarEstadosFuturos(celula** matriz, unsigned int fil, unsigned int col);

// Función que calcula el estado futuro de una celda
bool calEstadoFuturo(celula** matriz, unsigned int x, unsigned int y);

// Función que actualiza el tablero, pasando los estados futuros a actuales
void actualizarTablero(celula** matriz, unsigned int fil, unsigned int col);

// Función para imprimir el estado de una celda (viva o muerta)
void prtEstado(bool estado);

// Función para crear un nuevo tablero de celdas
celula** crearTablero(unsigned int fil, unsigned int col);

//Destruye un tablero dinamico
void destruirTablero(celula** tablero, unsigned int fil);

#endif // JUEGO_H_INCLUDED


