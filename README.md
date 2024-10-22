# El Juego de la Vida - TP UNLaM Topicos de Programacion.

Este repositorio es una implementacion en C y usando la libreria SDL2 del **Juego de la Vida** creado por el matematico britanico **John Horton Conway** en 1970.

El **Juego de la Vida de Conway** es una simulación que se lleva a cabo en una cuadrícula de celdas que pueden estar en dos estados: vivas o muertas. La evolución de las células está determinada por las siguientes reglas:

1. Una célula viva con menos de dos vecinos vivos muere (subpoblación).
2. Una célula viva con dos o tres vecinos vivos sobrevive.
3. Una célula viva con más de tres vecinos vivos muere (sobrepoblación).
4. Una célula muerta con exactamente tres vecinos vivos revive (reproducción).

## Tabla de Contenidos

- [Descripción del Proyecto](#descripción-del-proyecto)
- [Instrucciones de Uso](#instrucciones-de-uso)
- [Preview](#preview)



## Descripción del Proyecto

Este proyecto esta escrito en C y utiliza un vector bidimensional de estructuras 'Celula', donde cada una almacena su estado actual, estado futuro y el número de vecinos vivos. El programa carga un tablero de juego inicial desde un archivo de texto y calcula sus nuevos estados recorriendo la matriz e intercambiando el estado actual por el futuro.

Incluye 3 mapas de estados iniciales

- [canon.txt](#canon)
- [puffer.txt](#puffer)
- [filler.txt](#filler)



## Instrucciones de Uso

### Compilacion
Para compilar y ejecutar el proyecto:

1. Clonar este repositorio.
2. Compilar usando GCC

```
gcc -o main.exe main.c -lmingw32 -lSDL2main -lSDL2 -I./SDL2/include -L./SDL2/lib
```
3. Asegurese de copiar SDL2.dll de ./SDL2/bin a la carpeta donde esta el .exe resultante
4. Asegurese de tener en la misma carpeta del .exe una sub carpeta llamada maps y coloque ahi el mapa que quiere cargar

### Archivos de estados iniciales
El archivo de texto del mapa inicial debe estar en una sub carpeta llamada "maps" que se encuentre en el mismo directorio que el .exe y debe estar formateado de la siguiente forma:

| Fila,Columna |
| -------------|
|X,Y|
|X1,Ya|
|X2,Yb|
|Xn,Yn'|


### Utilizar
Debe navegar a la carpeta donde se encuentre el punto el ejecutable, abrir una consola de comandos y ejecutar el programa enviando el nombre del estado inicial como argumento. 
Ejemplo:
```
juegoDeLaVida.exe filler.txt
```

## Preview


### Canon
![canon](https://github.com/TomasCornara/Juego-de-La-Vida-Conway/blob/main/maps/canon.gif "canon.txt")

### Puffer
![puffer](https://github.com/TomasCornara/Juego-de-La-Vida-Conway/blob/main/maps/puffer.gif "puffer.txt")

### Filler
![filler](https://github.com/TomasCornara/Juego-de-La-Vida-Conway/blob/main/maps/filler.gif "filler.txt")
