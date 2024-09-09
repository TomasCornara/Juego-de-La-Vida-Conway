# El Juego de la Vida - TP UNLaM Topicos de Programacion.

Este repositorio es una implementacion en C del **Juego de la Vida** creado por el matematico britanico **John Horton Conway** en 1970.

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

Este proyecto escrito en C consiste de una vector bidimensional de estructuras "celula" donde cada una guarda su estado actual, su estado futuro y la cantidad de vecinos que tiene. El programa recorre la matriz una primera calculando su estado futuro de cada celula y luego una segunda para actualizar sus estados pasados e imprimir el estado actual. 

## Instrucciones de Uso

Para compilar y ejecutar el proyecto:

1- Clonar este repositorio.
2- Cargar una matriz de estado inicial
3- Compilar usando GCC

    gcc -o main.c
    
## Preview

![home](https://cdn.discordapp.com/attachments/673346179152609280/1282736156923920488/23.png?ex=66e070a3&is=66df1f23&hm=7ce1f14067baf4783ac84d3523a8278e48c78422cb750c20d1e4f5ab89c17fb9&)
