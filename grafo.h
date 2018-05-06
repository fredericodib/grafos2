#include <stdio.h>
#include <string.h>

/* Struct que define a estrutura de um vértice */
typedef struct {
  int degree;        /*Grau do vértice*/
  int *edge;        /* Array de arestas*/
  int count;		/* Contador */
  int id;			/* Id do vértice */
} VERTEX;

/* Struct que define a estrutura de um grafo */
typedef struct {
	int nvertices; /* Número de vértices */
	VERTEX *vertex;
} GRAFO;

/* Struct que define a estrutura de um nó */
struct Node {
	VERTEX vertex;
	struct Node *prox;
};
typedef struct Node NODE;

/* Struct que define a estrutura de uma pilha */
typedef struct {
	NODE *inicio;
} PILHA;

typedef struct {
	NODE *inicio;
	NODE *fim;
} FILA;