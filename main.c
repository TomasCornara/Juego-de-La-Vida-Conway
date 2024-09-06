#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "juego.h"

int main()
{
    // Tablero de carga para configurar de forma sencilla

    //Fabrica naves espaciales 14 x 36
    int tableroCarga[MAX_FIL][MAX_COL] =
{
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0}, // Fila 1
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0}, // Fila 2
    {0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1}, // Fila 3
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1}, // Fila 4
    {1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // Fila 5
    {1,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0}, // Fila 6
    {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0}, // Fila 7
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // Fila 8
    {0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // Fila 9
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // Fila 10
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // Fila 11
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // Fila 12
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // Fila 13
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}  // Fila 14
};


    //Ocilador 6 x 6
    /*int tableroCarga[MAX_FIL][MAX_COL] =
    {
        {0,0,0,0,0,0},
        {0,0,0,1,1,0},
        {0,0,0,1,1,0},
        {0,1,1,0,0,0},
        {0,1,1,0,0,0},
        {0,0,0,0,0,0},
    };*/

    // Tablero real
    celula tablero[MAX_FIL][MAX_COL];

    // Carga del tablero
    cargarTablero(tableroCarga, tablero, 14, 36);

    //printf("\nDEBUG: Cant vecinos %d", calCantVecinos(tablero, 6, 6, 5, 5));
    //printf("\nDEBUG: Cant vecinos %d", tablero[1][3].cantVecinosVivos);

    // Loop principal
    system("cls");
    while (1)
    {
        //Imprime tablero
        printTablero(tablero, 14, 36);

        //Actualiza estados futuros
        actualizarEstadosFuturos(tablero, 14, 36);

        //Actualizo celulas
        actualizarEstadosCelulas(tablero, 14, 36);

        //Actualizo sus vecinos
        actualizarVecinos(tablero, 14, 36);


        Sleep(50); // Espera 50ms antes de volver a actualizar
        system("cls"); // Limpia la pantalla
    }

    return 0;
}
