/*
IMPLEMENTACIONES DE LA LIBRERIA DEL TAD PILA DINÁMICA (TADPilaDin.h)
AUTOR: Edgardo Adrián Franco Martínez (C) Septiembre 2012
		Ericka Ruiz López 26 - Marzo - 2021
VERSIÓN: 1.4

DESCRIPCIÓN: TAD pila o stack.
Estructura de datos en la que se cumple:
Los elementos se añaden y se remueven por un solo extremo.
Este extremo es llamado “tope” de la pila.

OBSERVACIONES: Hablamos de una Estructura de datos dinámica 
cuando se le asigna memoria a medida que es necesitada, 
durante la ejecución del programa. En este caso la memoria 
no queda fija durante la compilación.

COMPILACIÓN PARA GENERAR EL CÓDIGO OBJETO: gcc TADPila.c -c
*/

//LIBRERAS
#include <stdio.h>
#include <stdlib.h>
#include "TADPila.h"

//DEFINICIÓN DE FUNCIONES

/*
void Initialize(pila *s);
Descripción: Inicializar pila (Iniciar una pila para su uso)
Recibe: int *s (Referencia a la pila "s" a operar)
Devuelve:
Observaciones: El usuario a creado una pila y s tiene la referencia a ella, 
si esto no ha pasado se ocasionara un error.
*/
void Initialize(pila *s)
{
	s->tope=NULL; //(*s).tope=NULL;
	return;
}

/*
void Push(pila *s, elemento e);
Descripción: Empilar (Introducir un elemento a la pila)
Recibe: int *s (Referencia a la pila "s" a operar), elemento e (Elemento a introducir en la pila)
Devuelve:
Observaciones: El usuario a creado una pila y s tiene la referencia a ella, s ya ha sido inicializada.
Ademas no se valida si el malloc() pudo o no apartar memoria, se idealiza que siempre funciona bien 
y no se acaba la memoria
*/
void Push(pila *s, elemento e)
{
	nodo *aux;
	aux=malloc(sizeof(nodo));
	
	//Si no hay más memoria dinámica por alguna razón
	if(aux==NULL)
	{
		printf("\nERROR-Push(&s,e): Desbordamiento de la pila, no hay más memoria disponible");
		exit(1);
	}
	
	//Si se creo el nuevo nodo insertar al elemento
	(*aux).e=e;  //aux->e=e;
	aux->abajo=s->tope;
	s->tope=aux;
	return;
}


/*
void Pop(pila *s);
Descripción: Desempilar (Extraer un elemento de la pila)
Recibe: int *s (Referencia a la pila "s" a operar)
Devuelve: elemento (Elemento e extraido de la pila)
Observaciones: El usuario a creado una pila y s tiene la referencia a ella, s ya ha sido inicializada.
Ademas no se valida si la pila esta vacia antes de desempilar (causa error desempilar si esta esta vacía), 
tampoco se valida si free() pudo o no liberar la memoria, se idealiza que siempre funciona bien 
*/
elemento Pop (pila *s)
{
	elemento r;
	nodo *aux;
	
	//Si el tope es NULL, se intenta Pop de pila vacia 
	if(s->tope==NULL)
	{
		printf("\nERROR-e=Pop(&s): Subdesbordamiento de la pila, no hay elementos en la pila");
		exit(1);
	}
	
	r=s->tope->e;
	aux=s->tope;
	s->tope=s->tope->abajo;
	free(aux);
	return r;	
}

/*
boolean Empty(pila *s);
Descripción: //Vacia (Preguntar si la pila esta vacia)
Recibe: int *s (Referencia a la pila "s" a operar)
Devuelve: boolean (TRUE o FALSE según sea el caso)
Observaciones: El usuario a creado una pila y s tiene la referencia a ella, s ya ha sido inicializada.
*/
boolean Empty(pila *s)
{
	boolean r;
	if(s->tope==NULL)
	{
		r=TRUE;
	}	
	else
	{
		r=FALSE;
	}
	return r;	
}

/*
elemento Top(pila *s);
Descripción: Tope (Obtener el "elemento" del tope de la pila si extraerlo de la pila)
Recibe: int *s (Referencia a la pila "s" a operar)
Devuelve: elemento (Elemento del tope de la pila)
Observaciones: El usuario a creado una pila y s tiene la referencia a ella, s ya ha sido inicializada.
Ademas no se valida si la pila esta vacia antes de consultar al elemnto del tope (causa error si esta esta vacía).
*/
elemento Top(pila *s)
{
	//Si el tope es NULL, se intenta Top de pila vacia 
	if(s->tope==NULL)
	{
		printf("\nERROR-e=Top(&s): Subdesbordamiento de la pila, no hay elementos en la pila");
		exit(1);
	}
	
	return s->tope->e;
}

/*
int Size(pila *s);
Descripción: Tamaño de la pila (Obtener el número de elementos en la pila)
Recibe: int *s (Referencia a la pila "s" a operar)
Devuelve: int (Tamaño de la pila 0->Vacia, 1->1 elemento, 2->2 elementos, ...)
Observaciones: El usuario a creado una pila y s tiene la referencia a ella, s ya ha sido inicializada.
*/
int Size(pila *s)
{
	nodo *aux;
	int tam_pila=0;
	aux=s->tope;
	if(aux!=NULL)
	{
		tam_pila++;
		while(aux->abajo!=NULL)
		{
			tam_pila++;
			aux=aux->abajo;
		}
	}	
	return tam_pila;
}

/*
void Destroy(pila *s);
Descripción: Elimina pila (Borra a todos los elementos en a la pila de memoria)
Recibe: int *s (Referencia a la pila "s" a operar)
Devuelve: 
Observaciones: El usuario a creado una pila y s tiene la referencia a ella, s ya ha sido inicializada.
*/
void Destroy(pila *s)
{
	nodo *aux;
	if(s->tope!=NULL)
	{
		while(s->tope!=NULL)
		{				
			aux=s->tope->abajo;
			free(s->tope);
			s->tope=aux;
		}		
	}
	return;
}

/*
elemento Element(pila *s, int n);
Descripción: Consultar Elemento (Obtener el "elemento" de una posición de la pila sin extraerlo de la pila)
Recibe: pila *s (Referencia a la pila "s" a operar), int n (Posición del elemento a obtener)
Devuelve: elemento (Elemento e en la posición n de la pila)
Observaciones: El usuario ha creado una pila y s tiene la referencia a ella, s ya ha sido inicializada.
Además no se valida si la pila está vacía antes de consultar al elemento en la posición ni si la posición es inválida o inexistente (causa error si está vacía o si la posición no está contenida en la pila).
*/
elemento Element(pila *s, int n){
	//variable r de tipo elemento a retornar
	elemento r;
	//contador auxiliar para iniciar búsqueda del elemento desde arriba (a partir de la última posición de la pila)
	int i = Size(s) - n;
	//nodo auxiliar que contiene el tope actual de la pila 
	nodo *aux = s->tope;
	//Si el tope es NULL, intenta buscar un elemento en pila vacía
	if(s->tope==NULL)
	{
		printf("\nERROR-e=Element(&s, n): Subdesbordamiento de la pila, no hay elementos en la pila");
		exit(1);
	}
	//Si la posición buscada es menor a 0, se intenta buscar un elemento en una posición que no existe
	if(n<1){
		printf("\nERROR-e=Element(&s, n): Subdesbordamiento de la pila, posicion invalida");
		exit(1);
	}
	//Si la posición buscada es mayor al tamaño de la pila, se intenta buscar un elemento en una posición que no existe
	if(n>Size(s)){
		printf("\nERROR-e=Element(&s, n): Desbordamiento de la pila, posicion inexistente");
		exit(1);
	}
	//Si no hubo error, comienza a recorrer el contador i auxiliar que va en desaumento. Se recorre el tope de la pila al nodo inmediato anterior en cada iteración
	while(i>0)
	{	
		s->tope=s->tope->abajo;
		i--;
	}
	//El tope se ha recorrido hasta la posición deseada; se copia el elemento en r en esta posición para su retorno	
	r = s->tope->e;
	//Regresa el tope a su posición original
	s->tope = aux;
	//Retorna el elemento r
	return r;
}

/*
void Copy(pila *s, pila *t);
Descripción: Copiar (Copiar los elementos de una pila en otra)
Recibe: pila *s (Referencia a la pila "s" a copiar), pila *t (Referencia a la pila destinataria "t" a la que se copiará la pila "s")
Devuelve:
Observaciones: El usuario ha creado dos pilas y s y t tienen las referencias a ellas respectivamente, s y t ya han sido inicializadas.
Además no se valida si la pila a copiar está vacía antes de copiarla a la pila destinataria (causa error si está vacía)
Precauciones: Si la pila destinataria tiene elementos, éstos serán reemplazados por los elementos a copiar. 
*/
void Copy(pila *s, pila *t){
	elemento e;
	int i=1;
	//Si el tope de s es NULL, intenta copiar una pila vacía
	if(s->tope == NULL){
		printf("\nERROR-Copy(&s, &t): Subdesbordamiento de la pila, no hay elementos en la pila");
		exit(1);
	}
	//Si t tiene elementos, inicializa la pila para insertar los elementos a copiar
	if(t->tope != NULL){
		Initialize(t);
	}
	//Copia los elementos de s en t
	while (i<=Size(s))
	{
		e = Element(s, i);
		Push(t, e);
		i++;
	}
	return;
}

/*
void Flip(pila *s);
Descripción: Voltear (Invertir los elementos de la pila)
Recibe: pila *s (Referencia a la pila "s" a operar)
Devuelve:
Observaciones: El usuario ha creado una pila y s tiene la referencia a ella, s ya ha sido inicializada.
Además no se valida si la pila está vacía antes de invertirla (causa error si está vacía).
*/
void Flip(pila *s){
	pila t;
	elemento e;
	Initialize(&t);
	//Si el tope de s es NULL, intenta voltear una pila vacía
	if(s->tope==NULL)
	{
		printf("\nERROR-Flip(&s): No hay elementos en la pila");
		exit(1);
	}
	//Si no hay problema, copia los elementos de s en una pila auxiliar t
	Copy(s, &t);
	//Inicializa s para insertar nuevos elementos
	Initialize(s);
	//Obtiene los elementos de t y los almacena en s
	while(!Empty(&t)){
		e = Pop(&t);
		Push(s, e);
	}
	return;
}