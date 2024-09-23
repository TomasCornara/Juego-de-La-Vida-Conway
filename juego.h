#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED
#include <stdbool.h>
#define MAX_FIL 50
#define MAX_COL 50

typedef struct
{
    bool estadoActual;
    unsigned char estadoFuturo;
    unsigned char cantVecinosVivos;
} celula;

void cargarTablero(int origen[MAX_FIL][MAX_COL], celula destino[MAX_FIL][MAX_COL], unsigned int fil, unsigned int col);
void printTablero(celula matriz[MAX_FIL][MAX_COL], unsigned int fil, unsigned int col);
unsigned char calCantVecinos(celula matriz[MAX_FIL][MAX_COL],unsigned int fil, unsigned int col,unsigned int posX, unsigned int posY);
unsigned char calCantVecinosInt(int matriz[MAX_FIL][MAX_COL], unsigned int fil, unsigned int col, unsigned int posX, unsigned int posY);
void actualizarEstadosFuturos(celula matriz[MAX_FIL][MAX_COL],unsigned int fil, unsigned int col);
bool calEstadoFuturo(celula matriz[MAX_FIL][MAX_COL],unsigned int x, unsigned int y);
void actualizarTablero(celula matriz[MAX_FIL][MAX_COL],unsigned int fil, unsigned int col);
void prtEstado(bool estado);

#endif // JUEGO_H_INCLUDED
