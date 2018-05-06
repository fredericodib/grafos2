/* Nesse arquivo estão as funções usadas para a ordenação através do algoritmo de Kahn */


/*Estrutura da fila*/
void inicia_fila(FILA *fila) {
	fila->inicio = NULL;
	fila->fim = NULL;
}

NODE *pusher_fila(){
   NODE *new = (NODE*) malloc(sizeof(NODE));
   return new;
}

void enfilera(FILA *fila, VERTEX vertice) {
	NODE *node = pusher_fila();
	NODE *aux_node;

	node->vertex = vertice;
	if (fila->inicio != NULL) {
		aux_node = fila->inicio;
		while(aux_node->prox != NULL) {
			aux_node = aux_node->prox;
		}
		aux_node->prox = node;
	}
	else {
		fila->inicio = node;
	}
	
	node->prox = NULL;
	fila->fim = node;
}

NODE *desenfilera(FILA *fila) {
	NODE *node;

	if (fila->inicio == NULL) {
		return NULL;
	}

	node = fila->inicio;
	if (fila->inicio->prox == NULL) {
		fila->inicio = NULL;
		fila->fim = NULL;
	}
	else {
		fila->inicio = fila->inicio->prox;
	}
	

	return node;
}

/*Função que cria um vetor em que cada indice representa o vertice, e o valor é o grau de entrada*/
void grau_entrada(int *vetor, GRAFO grafo, FILA *S) {
	int i, j;

	for (i=0;i<grafo.nvertices;i++) {
		vetor[i] = 0;
	}

	for(i=0;i<grafo.nvertices;i++) {
		for(j=0;j<grafo.vertex[i].degree;j++) {
			vetor[grafo.vertex[i].edge[j]]++;
		}
	}

	for(i=0;i<grafo.nvertices;i++) {
		if (vetor[i] == 0) {
			enfilera(S, grafo.vertex[i]);
		}
	}
}


/* Executa a ordenação de Kahn */
void ordenacao_kahn(GRAFO grafo, FILE *ordenacao_file) {
	int *vetor_entrada, i, j, id, count=0;
	clock_t start_t, end_t, total_t;
	FILA S;
	NODE *node;
	FILE *arq;

	arq = fopen("data_khan.txt", "w");

	inicia_fila(&S);

	vetor_entrada = malloc (grafo.nvertices * sizeof (int));

	grau_entrada(vetor_entrada, grafo, &S);

	start_t = clock(); /*inicia a contagem*/

	while(S.inicio != NULL) {
		node = desenfilera(&S);
		fprintf(ordenacao_file, "%d ", node->vertex.id);

		/*Bloco para gravar o tempo em um arquivo*/
		count++;
		end_t = clock();
		total_t = (end_t - start_t);
   		fprintf(arq,"%d\t%ld\n", count, total_t);

		id = node->vertex.id;
		for(i=0;i<grafo.vertex[id].degree;i++) {
			j = grafo.vertex[id].edge[i];
			vetor_entrada[j]--;
			if (vetor_entrada[j] == 0) {
				enfilera(&S, grafo.vertex[j]);
			}
		}
	}
	fprintf(ordenacao_file, "\n");

	fclose(arq);
}