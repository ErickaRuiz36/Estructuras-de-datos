/*******************
COMPILACIÓN:    gcc Laberinto2.c presentacionWin.c TADPila.c -o Laberinto2
Ejecucion:      Laberinto2.exe

Autor: Ericka Ruiz López --- Septiembre 2021
*********************/

//librerías
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "presentacion.h"
#include "TADPila.h"

//Definición de constantes
#define FILAS 7
#define COLUMNAS 7
#define TIEMPO_ESPERA 300

//Prototipos de funciones
void mostrarMatriz(int laberinto[FILAS][COLUMNAS]);
void buscarCamino(int laberinto[FILAS][COLUMNAS], int fil, int col);
int obtenerDireccionesDisponibles(elemento e);
void mapear(int fil, int col, elemento * e, int laberinto[FILAS][COLUMNAS]);
void buscarEnPasos(int fil, int col, elemento * e);
void buscarEnSinSalida(int fil, int col, elemento * e);
int avanzar(int direccion, char * direcciones, int laberinto[FILAS][COLUMNAS], elemento e);
void retroceder(int laberinto[FILAS][COLUMNAS], elemento e);
char * crearArregloDirecciones(int numDirecciones);

//Variables auxiliares
pila pasos;
pila sinSalida;
pila dir;
int numPasos = 0;

void main(){
    //Inicialización srand
    srand(time(NULL));
    //Inicialización de pilas auxiliares
    Initialize(&pasos);
    Initialize(&sinSalida);
    //Solo para que el ejecutable no se cierre de inmediato
    int espera;

    //Arreglo laberinto
    int laberinto[FILAS][COLUMNAS] = {
        2, 7, 7, 7, 7, 0, 0,
        0, 0, 0, 0, 7, 0, 0,
        7, 0, 7, 7, 7, 0, 0,
        0, 0, 7, 0, 0, 7, 0,
        7, 0, 7, 7, 7, 0, 7,
        0, 0, 0, 0, 0, 0, 0,
        0, 7, 0, 0, 7, 0, 3
    };

    //Limpia la pantalla para la simulación
    BorrarPantalla();

    //Muestra el estado original del laberinto
    mostrarMatriz(laberinto);
    EsperarMiliSeg(TIEMPO_ESPERA);

    //Inicia la búsqueda del camino
    buscarCamino(laberinto, 0, 0);

    printf("\nNumero de recursiones/pasos: %d", numPasos);

    //Solo para que el ejecutable no se cierre de inmediato
    printf("\n\nIngresa 1 para continuar...");
    scanf("%d", &espera);
}

/*
Efecto: Busca el camino a la meta desde las coordenadas dadas.
Devuelve: -
*/
void buscarCamino(int laberinto[FILAS][COLUMNAS], int fil, int col){
    //structs auxiliares con fil, col de la posición actual, y up, down, left, right con las coordenadas a su alrededor
    elemento e;
    elemento tmp;
    //Numero de direcciones a las que puede avanzar
    int numDirecciones;
    //Arreglo con caracteres para saber qué direcciones se pueden tomar 
    char * direcciones;
    //Dirección que va a tomar
    int direccion;
    //Resultado de avanzar un paso
    int llegada;

    //Almacena en el struct las coordenadas actuales
    e.fil = fil;
    e.col = col;

    //Obtiene las coordenadas que rodean a la posición actual y las almacena en el mismo struct
    mapear(fil, col, &e, laberinto);

    //Obtiene el número de caminos que puede tomar
    numDirecciones = obtenerDireccionesDisponibles(e);

    //Obtiene las direcciones a las que puede avanzar
    direcciones = crearArregloDirecciones(numDirecciones);

    //Escoge al azar la dirección a la que va a ir
    if(numDirecciones != 0){
        direccion = rand() % numDirecciones;
    }else{
        //Si no hay direcciones disponibles para escoger
        direccion = -1;
    }
    
    //Da un paso, de acuerdo a la dirección seleccionada
    llegada = avanzar(direccion, direcciones, laberinto, e);

    //Muestra el laberinto actualizado
    mostrarMatriz(laberinto);

    //De acuerdo al resultado del movimiento

    //Avanzó sin ningún problema
    if(llegada == 0){
        EsperarMiliSeg(TIEMPO_ESPERA);
        //llamada recursiva
        if(direcciones[direccion] == 'u'){
            buscarCamino(laberinto, e.up, e.col);
        }
        if(direcciones[direccion] == 'd'){
            buscarCamino(laberinto, e.down, e.col);
        }
        if(direcciones[direccion] == 'l'){
            buscarCamino(laberinto, e.fil, e.left);
        }
        if(direcciones[direccion] == 'r'){
            buscarCamino(laberinto, e.fil, e.right);
        }
    }else{
        //No pudo avanzar, retrocede
        if(llegada == -1){
            retroceder(laberinto, e);
            tmp = Pop(&pasos);
            mostrarMatriz(laberinto);
            EsperarMiliSeg(TIEMPO_ESPERA);
            buscarCamino(laberinto, tmp.fil, tmp.col);
        }else{
            //Ha encontrado el final del laberinto, caso base
            if(llegada == 1){
                MoverCursor(0,9);
                printf("\nFin");
                EsperarMiliSeg(TIEMPO_ESPERA);
            }
        }
    }
    
    numPasos++;

    return;
}

/*
Efecto: Obtiene las las coordenadas a las que se puede avanzar desde la posición actual.
Devuelve: -
*/
void mapear(int fil, int col, elemento * e, int laberinto[FILAS][COLUMNAS]){
    /*
    Si se puede avanzar, se almacena la coordenada
    Si no se puede avanzar, se alacena el número 7 como indicador
    */

    if(fil + 1 < FILAS){
        if(laberinto[fil + 1][col] != 7){
            e->down = fil + 1;
        }else{
            e->down = 7;
        }
    }else{
        e->down = 7;
    }
    if(fil - 1 >= 0){
        if(laberinto[fil - 1][col] != 7){
            e->up = fil - 1;
        }else{
            e->up = 7;
        }
    }else{
        e->up = 7;
    }
    if(col + 1 < COLUMNAS){
        if(laberinto[fil][col + 1] != 7){
            e->right = col + 1;
        }else{
            e->right = 7;
        }
    }else{
        e->right = 7;
    }
    if(col - 1 >= 0){
        if(laberinto[fil][col - 1] != 7){
            e->left = col - 1;
        }else{
            e->left = 7;
        }
    }else{
        e->left = 7;
    }

    //Verifica que no se haya pasado por alguna de las coordenadas anteriormente
    buscarEnPasos(fil, col, e);
    buscarEnSinSalida(fil, col, e);

}

/*
Efecto: Busca coincidencias entre las coordenadas dadas y las coordenadas por las que ya se ha pasado.
Devuelve: -
*/
void buscarEnPasos(int fil, int col, elemento * e){
    elemento tmp;
    int tam = Size(&pasos);

    // Si encuentra coincidencias, no puede avanzar a esas coordenadas
    
    while(tam > 0){
        tmp = Element(&pasos, tam);
        if(tmp.fil == e->up && tmp.col == col){
            e->up = 7;
        }
        if(tmp.fil == e->down && tmp.col == col){
            e->down = 7;
        }
        if(tmp.col == e->left && tmp.fil == fil){
            e->left = 7;
        }
        if(tmp.col == e->right && tmp.fil == fil){
            e->right = 7;
        }
        tam--;
    }
    
}

/*
Efecto: Busca coincidencias entre las coordenadas dadas y las coordenadas por las que ya se ha pasado y no tienen salida.
Devuelve: -
*/
void buscarEnSinSalida(int fil, int col, elemento * e){
    elemento tmp;
    int tam = Size(&sinSalida);

    // Si encuentra coincidencias, no puede avanzar a esas coordenadas
    
    while(tam > 0){
        tmp = Element(&sinSalida, tam);
        if(tmp.fil == e->up && tmp.col == col){
            e->up = 7;
        }
        if(tmp.fil == e->down && tmp.col == col){
            e->down = 7;
        }
        if(tmp.col == e->left && tmp.fil == fil){
            e->left = 7;
        }
        if(tmp.col == e->right && tmp.fil == fil){
            e->right = 7;
        }
        tam--;
    }
}

/*
Efecto: Obtiene el número de direcciones que puede tomar desde las coordenadas actuales (almmacenadas en el struct).
Devuelve: Entero con el número de direcciones.
*/
int obtenerDireccionesDisponibles(elemento e){
    Initialize(&dir);
    elemento tmp;
    int numDirecciones = 0;
    int i;

    //si puede avanzar a la coordenada en cuestión, aumenta el número de direcciones disponible 

    if(e.up != 7){
        tmp.dir = 'u';
        Push(&dir,tmp);
        numDirecciones++;
    }
    if(e.down != 7){
        tmp.dir = 'd';
        Push(&dir,tmp);
        numDirecciones++;
    }
    if(e.left != 7){
        tmp.dir = 'l';
        Push(&dir,tmp);
        numDirecciones++;
    }
    if(e.right != 7){
        tmp.dir = 'r';
        Push(&dir,tmp);
        numDirecciones++;
    }
    
    return numDirecciones;
}

/*
Efecto: Crea un arreglo con las direcciones que puede tomar.
Devuelve: Puntero al arreglo con direcciones.
*/
char * crearArregloDirecciones(int numDirecciones){
    char * direcciones;
    int i;

    //Crea un arreglo con tamaño igual al número de direcciones que puede tomar

    direcciones=malloc(numDirecciones*sizeof(char));

	if(direcciones==NULL)
	{
		printf("\nError al intentar reservar memoria para %d elementos\n",numDirecciones);		
		exit(1);
	}

    //Almacena en el arreglo las direcciones que puede tomar

    for(i = 0; i<numDirecciones; i++){
        direcciones[i] = Pop(&dir).dir;
    }

    return direcciones;
}

/*
Efecto: Avanza a las coordenadas indicadas.
Retorna: Entero con el resultado del movimiento.
*/
int avanzar(int direccion, char * direcciones, int laberinto[FILAS][COLUMNAS], elemento e){
    //Si logra avanzar
    int llegada = 0;
    
    if(direccion != -1){
        //Arriba
        if(direcciones[direccion] == 'u'){
            if(laberinto[e.up][e.col] == 3){
                //Si llega a la meta
                llegada = 1;
            }
            laberinto[e.fil][e.col] = 0;
            laberinto[e.up][e.col] = 2;
            Push(&pasos, e);
        }
        //Abajo
        if(direcciones[direccion] == 'd'){
            if(laberinto[e.down][e.col] == 3){
                llegada = 1;
            }
            laberinto[e.fil][e.col] = 0;
            laberinto[e.down][e.col] = 2;
            Push(&pasos, e);
        }
        //Izquierda
        if(direcciones[direccion] == 'l'){
            if(laberinto[e.fil][e.left] == 3){
                llegada = 1;
            }
            laberinto[e.fil][e.col] = 0;
            laberinto[e.fil][e.left] = 2;
            Push(&pasos, e);
        }
        //Derecha
        if(direcciones[direccion] == 'r'){
            if(laberinto[e.fil][e.right] == 3){
                llegada = 1;
            }
            laberinto[e.fil][e.col] = 0;
            laberinto[e.fil][e.right] = 2;
            Push(&pasos, e);
        }
    }else{
        //Si no logra avanzar
        llegada = -1;
    }
    
    return llegada;
}

/*
Efecto: Retrocede a las últimas coordenadas anteriores.
Devuelve: -
*/
void retroceder(int laberinto[FILAS][COLUMNAS], elemento e){
    elemento tmp;

    //Almacena la coordenada sin salida
    Push(&sinSalida, e);

    //Retrocede a la última coordenada en la pila de pasos
    if(!Empty(&pasos)){
        tmp = Top(&pasos);
        laberinto[e.fil][e.col] = 0;
        laberinto[tmp.fil][tmp.col] = 2;
    }
}

/*
Efecto: Muestra el laberinto en consola.
Devuelve: -
*/
void mostrarMatriz(int laberinto[FILAS][COLUMNAS]){
    int i,j;

    for(i=0; i<FILAS;i++){
        MoverCursor(1,i);
        for(j=0;j<COLUMNAS;j++){
            printf("%d  ", laberinto[i][j]);
        }
        printf("\n");
    }

    //printf("\n-----------------------------------\n");
    EsperarMiliSeg(TIEMPO_ESPERA);

}