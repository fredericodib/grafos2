/* Nesse arquivo estão as funções usadas para a ordenação através do algoritmo de Kahn */
void grau_entrada(int *vetor, GRAFO grafo) {
	int i, j;

	for (i=0;i<grafo.nvertices;i++) {
		vetor[i] = 0;
	}

	for(i=0;i<grafo.nvertices;i++) {
		for(j=0;j<grafo.vertex[i].degree;j++) {
			vetor[grafo.vertex[i].edge[j]]++;
		}
	}


}

/* Checa se um vértice já foi visitado */
int checa_marcado(int *vetor, int tam, int valor) {
	int i;

	for(i=0;i<tam;i++) {
		if(vetor[i] == valor) {
			return 0;
		}
	}

	return 1;
}

/* Executa a ordenação de Kahn */
void ordenacao_kahn(GRAFO grafo) {
	int *vetor_entrada, *ordenacao, i, j, count=0, k=0;

	vetor_entrada = malloc (grafo.nvertices * sizeof (int));

	ordenacao = malloc (grafo.nvertices * sizeof (int));
	grau_entrada(vetor_entrada, grafo);

	while((count < grafo.nvertices) && (k < grafo.nvertices)) {
		for(i=0;i<grafo.nvertices;i++) {
			if ((vetor_entrada[i] == 0) && checa_marcado(ordenacao, count, i)) {
				ordenacao[count] = i;
				count++;

				for(j=0;j<grafo.vertex[i].degree;j++) {
					vetor_entrada[grafo.vertex[i].edge[j]]--;
				}
			}
		}
		k++;
	}



	for(i=0;i<grafo.nvertices;i++) {
		printf("%d ", ordenacao[i]);
	}
	printf("\n");
	
}