#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED
#define MAX_FIL 50
#define MAX_COL 50

typedef struct {
    unsigned char estadoActual;
    unsigned char estadoFuturo;
    unsigned char cantVecinosVivos;
} celula;

void cargarTablero(int origen[MAX_FIL][MAX_COL], celula destino[MAX_FIL][MAX_COL], unsigned int fil, unsigned int col);
void printTablero(celula matriz[MAX_FIL][MAX_COL], unsigned int fil, unsigned int col);
char calCantVecinos(celula matriz[MAX_FIL][MAX_COL],unsigned int fil, unsigned int col,unsigned int posX, unsigned int posY);
char calCantVecinosInt(int matriz[MAX_FIL][MAX_COL], unsigned int fil, unsigned int col, unsigned int posX, unsigned int posY);
void actualizarEstadosFuturos(celula matriz[MAX_FIL][MAX_COL],unsigned int fil, unsigned int col);
int calEstadoFuturo(celula matriz[MAX_FIL][MAX_COL],unsigned int x, unsigned int y);
void actualizarTablero(celula matriz[MAX_FIL][MAX_COL],unsigned int fil, unsigned int col);
void prtEstado(char caracter);

#endif // JUEGO_H_INCLUDED
