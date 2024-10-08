# El Juego de la Vida - TP UNLaM Topicos de Programacion.

Este repositorio es una implementacion en C del **Juego de la Vida** creado por el matematico britanico **John Horton Conway** en 1970.

El **Juego de la Vida de Conway** es una simulación que se lleva a cabo en una cuadrícula de celdas que pueden estar en dos estados: vivas o muertas. La evolución de las células está determinada por las siguientes reglas:

1. Una célula viva con menos de dos vecinos vivos muere (subpoblación).
2. Una célula viva con dos o tres vecinos vivos sobrevive.
3. Una célula viva con más de tres vecinos vivos muere (sobrepoblación).
4. Una célula muerta con exactamente tres vecinos vivos revive (reproducción).
5. 
## Tabla de Contenidos

- [Descripción del Proyecto](#descripción-del-proyecto)
- [Instrucciones de Uso](#instrucciones-de-uso)
- [Preview](#preview)



## Descripción del Proyecto

Este proyecto esta escrito en C y utiliza un vector bidimensional de estructuras 'Celula', donde cada una almacena su estado actual, estado futuro y el número de vecinos vivos. El programa carga un tablero de juego inicial desde un archivo de texto y calcula uno nuevo recorriendo la matriz e intercambiando el estado actual por el futuro. A partir de este nuevo tablero, calcula los vecinos y actualiza los estados futuros.
La parte visual se muestra mediante SDL2.



## Instrucciones de Uso

Para compilar y ejecutar el proyecto:

1. Clonar este repositorio.
2. Cargar una matriz de estado inicial
3. Compilar usando GCC

```
gcc -o main.c
```
El archivo de texto del mapa inicial debe estar en una sub carpeta llamada "maps" que se encuentre en el mismo directorio que el .exe y debe estar formateado de la siguiente forma:

| Fila,Columna |
| -------------|
|X,Y|
|X1,Ya|
|X2,Yb|
|Xn,Yn'|

El nombre del archivo debe ser enviado al programa mediante linea de comandos y debe incluir el formato. Por ejemeplo: "canon.txt"



## Preview

![home](https://i.postimg.cc/7L6tBTns/ezgif-1-230a36c304.gif)
