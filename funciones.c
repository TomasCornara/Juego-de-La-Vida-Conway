#include <stdio.h>
#include <stdlib.h>
#include "juego.h"
#include <string.h>
//Leer tablero
bool cargaTablero(celula** tablero, const char* nombreDelArchivo, int centroX, int centroY, unsigned int fil, unsigned int col)
{
    int coordenadaX;
    int coordenadaY;
    char caracter;
    char* archivoName;
    unsigned int x = 0;
    unsigned int y = 0;
    FILE* archivo;

    archivoName = (char*)malloc(strlen(nombreDelArchivo) + 8); // "./maps/" + nombreDelArchivo + '\0'

    //Armo la dir del archivo
    sprintf(archivoName,"%s%s","./maps/",nombreDelArchivo);

    // Abro el archivo
    archivo = fopen(archivoName, "rt");
    free(archivoName); //No necesito mas el nombre del archivo
    if (!archivo)  // Chequeo si se pudo abrir el archivo
    {
        return false; //Devuelvo false porque hubo un error
    }

    //Si lo que encuentro es un #, tengo que buscar donde termina el comentario
    while((caracter = fgetc(archivo)) == '#'){
        //avanzo hasta la siguiente linea
        while((caracter = fgetc(archivo)) != '\n' && caracter != EOF);
    }

    //En la variable "caracter" queda lo que hay despues del \n del ultimo comment
    //Si no es EOF, tengo que devolverlo porque es parte de una coordenada
    if(caracter != EOF) fseek(archivo,-1,SEEK_CUR);



    // Si se encuentra el archivo, leo las coordenadas y actualizo el tablero
    while (fscanf(archivo, "%d,%d", &coordenadaX, &coordenadaY) != EOF)
    {

        tablero[coordenadaX + centroX][coordenadaY + centroY ].estadoActual = true;  // Cargo el estado
    }

    // Cierro el archivo
    fclose(archivo);

    // Les calculo sus vecinos
    for (x = 0; x < fil; x++)
    {
        for (y = 0; y < col; y++)
        {
            tablero[x][y].cantVecinosVivos = calCantVecinos(tablero, fil, col, x, y);
            tablero[x][y].estadoFuturo = calEstadoFuturo(tablero, x, y);
        }
    }

    return true;  // Salio true porque salio todo bien
}


// Crear tablero con memoria dinamica usando calloc
celula** crearTablero(unsigned int fil, unsigned int col)
{
    celula** vectorFilas;
    celula** punteroFila;
    unsigned int x;


    // Reserva para las filas (punteros a cada fila) usando calloc
    vectorFilas = calloc(fil, sizeof(celula*));
    if (!vectorFilas)
    {
        return NULL;
    }

    punteroFila = vectorFilas;  // Puntero auxiliar para recorrer las filas

    // Reserva memoria para cada fila
    for (x = 0; x < fil; x++, punteroFila++)
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


// Destruye un tablero dinamico
void destruirTablero(celula** tablero, unsigned int fil)
{
    celula** fin;

    // Liberar cada fila usando aritmética de punteros
    for (fin = tablero + fil; tablero < fin; tablero++)
    {
        free(*tablero);  // Liberar la fila actual
    }

    // Liberar el array de punteros a filas
    free(tablero - fil);
}


// Actualiza los estados de las células
void actualizarTablero(celula** matriz, unsigned int fil, unsigned int col)
{
    unsigned int x;
    unsigned int y;

    // Actualiza el estado actual basado en el futuro
    for (x = 0; x < fil; x++)
    {
        for (y = 0; y < col; y++)
        {
            matriz[x][y].estadoActual = matriz[x][y].estadoFuturo;
        }
    }

    //Actualiza la cantidad de vecinos vivos para cada celula y luego su estado futuro
    for (x = 0; x < fil; x++)
    {
        for (y = 0; y < col; y++)
        {
            matriz[x][y].cantVecinosVivos = calCantVecinos(matriz, fil, col, x, y);
            matriz[x][y].estadoFuturo = calEstadoFuturo(matriz, x, y);
        }
    }
}

// Calcula cual va a ser el estado futuro de una celula
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

// Calcula la cantidad de vecinos vivos de una celula
unsigned char calCantVecinos(celula** matriz, unsigned int fil, unsigned int col, unsigned int posX, unsigned int posY)
{
    unsigned int limiteLateralIzq;
    unsigned int limiteSuperior;
    unsigned int limiteLateralDer;
    unsigned int limiteInferior;
    unsigned char cantVecinos;
    unsigned int x;
    unsigned int y;

    cantVecinos = 0;

    // Definir los limites de la submatriz
    limiteLateralIzq = (posY > 0) ? posY - 1 : 0;
    limiteSuperior = (posX > 0) ? posX - 1 : 0;
    limiteLateralDer = (posY < (col - 1)) ? posY + 1 : col - 1;
    limiteInferior = (posX < (fil - 1)) ? posX + 1 : fil - 1;

    // Recorrer la submatriz
    for (x = limiteSuperior; x <= limiteInferior; x++)
    {
        for (y = limiteLateralIzq; y <= limiteLateralDer; y++)
        {
            // No contar la posicion central
            if (!(x == posX && y == posY))
            {
                // Sumar el estado actual (1 si esta viva, 0 si no)
                cantVecinos += matriz[x][y].estadoActual;
            }
        }
    }

    return cantVecinos;
}
