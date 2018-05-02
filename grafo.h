#include <stdio.h>
#include <string.h>

typedef struct {
  int degree;        /*/ Degree of vertex (out-degree for directed nets)*/
  int *edge;        /*/ Array of EDGE structs, one for each neighbor*/
  int count;
  int id;
} VERTEX;

typedef struct {
	int nvertices;
	VERTEX *vertex;
} GRAFO;

struct Node {
	VERTEX vertex;
	struct Node *prox;
};
typedef struct Node NODE;

typedef struct {
	NODE *inicio;
} PILHA;