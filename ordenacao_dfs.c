/* Nesse arquivo estão as funções utilizadas para fazer a ordenação usando DFS */
void inicia_pilha(PILHA *pilha) {
	pilha->inicio = NULL;
}

NODE *pusher(){
   NODE *new = (NODE*) malloc(sizeof(NODE));
   return new;
}

void push(PILHA *pilha, VERTEX vertice) {
	NODE *node = pusher();
	node->vertex = vertice;
	node->prox = pilha->inicio;
	pilha->inicio = node;
}

NODE *pop(PILHA *pilha) {
	NODE *node;

	if (pilha->inicio == NULL) {
		return NULL;
	}

	node = pilha->inicio;
	if (pilha->inicio->prox == NULL) {
		pilha->inicio = NULL;
	}
	else {
		pilha->inicio = pilha->inicio->prox;
	}
	

	return node;
}


/* Faz a ordenação topológica do grafo recebido */
void ordenacao_dfs(GRAFO grafo) {
	int *vetor_status, i, id_aux, count, j;
	NODE *node;
	PILHA p, resultado;

	/*0 = não visitado, 1 = empilhado*/
	vetor_status = malloc (grafo.nvertices * sizeof (int));

	for (i=0;i<grafo.nvertices;i++) {
		vetor_status[i] = 0;
	}

	inicia_pilha(&p);
	inicia_pilha(&resultado);

	for(i=0;i<grafo.nvertices;i++) {
		if (vetor_status[i] == 0) {
			push(&p, grafo.vertex[i]);
			while(p.inicio != NULL) {
				node = p.inicio;
				vetor_status[node->vertex.id] = 1;
				count = 0;
				for(j=0;j<node->vertex.degree;j++) {
					id_aux = node->vertex.edge[j];
					if(vetor_status[id_aux] == 0) {
						push(&p, grafo.vertex[id_aux]);
						count++;
						break;
					}
				}
				if (count == 0) {
					node = pop(&p);
					push(&resultado, node->vertex);
				}
			}
		}
	}

	for(i=0;i<grafo.nvertices;i++) {
		node = pop(&resultado);
		printf("%d ", node->vertex.id);
	}
	printf("\n");
	

}