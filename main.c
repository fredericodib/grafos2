/*
Trabalho 2 de Grafos 1/2018
Alunos: Frederico Pinheiro Dib	15/0125925
		Amanda Oliveira Alves   15/0116276

Como compilar:
$ gcc -ansi -Wall -o main main.c -lm
$ ./main > ordenacao.txt
O resultado das ordenações estará registrado no arquivo ordenacao.txt
O resultado de tempo sairá no Arquivo time.txt

Os dois arquivos Já estão gerados!
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "grafo.h"
#include "ordenacao_kahn.c"
#include "ordenacao_dfs.c"


void constroi_grafo(GRAFO *grafo, char *name) {
	int n_vertice, vertice, target, grau, i, count;
	FILE *arq;

	arq = fopen(name, "r");
	if(arq == NULL)
	    printf("Erro, nao foi possivel abrir o arquivo\n");
	else

	fscanf(arq, "%d", &n_vertice);
	grafo->nvertices = n_vertice;
	grafo->vertex = malloc (n_vertice * sizeof (VERTEX));

	while((fscanf(arq,"%d %d", &vertice, &target))!=EOF) {
		grafo->vertex[vertice].degree++;
	}

	for(i=0;i<n_vertice;i++) {
		grau = grafo->vertex[i].degree;
		grau = grafo->vertex[i].id = i;
		grau = grafo->vertex[i].count = 0;
		grafo->vertex[i].edge = malloc (grau * sizeof (int));
	}

	fclose(arq);

	arq = fopen(name, "r");
	if(arq == NULL)
	    printf("Erro, nao foi possivel abrir o arquivo\n");
	else
	fscanf(arq, "%d", &n_vertice);

	while((fscanf(arq,"%d %d", &vertice, &target))!=EOF) {
		count = grafo->vertex[vertice].count;
		grafo->vertex[vertice].edge[count] = target;
		grafo->vertex[vertice].count++;
	}

	fclose(arq);
}



int main() {
	clock_t start_t, end_t, total_t;
	
	FILE *data;
	data = fopen("time.txt", "w");

	GRAFO small_g;
	GRAFO med_g;
	GRAFO large_g;
	GRAFO huge_g;

	constroi_grafo(&small_g, "top_small.txt");
	printf("Ordenação do grafo construido a partir do arquivo top_small.txt\nA ordenação utilizada foi a de Kahn\n\n");
	
	start_t = clock();
	ordenacao_kahn(small_g);
	end_t = clock();
	total_t = (end_t - start_t);
   	fprintf(data,"Algoritmo de Kahn, para 10 vertices, levou %ld Clocks\n", total_t);
   	
	printf("\n");
	printf("Ordenação do grafo construido a partir do arquivo top_small.txt\nA ordenação utilizada foi a baseada no DFS\n\n");
	
	start_t = clock();
	ordenacao_dfs(small_g);
	end_t = clock();
	total_t = (end_t - start_t);
   	fprintf(data,"Algoritmo de DFS, para 10 vertices, levou %ld Clocks\n", total_t);

	printf("\n");

	constroi_grafo(&med_g, "top_med.txt");
	printf("Ordenação do grafo construido a partir do arquivo top_med.txt\nA ordenação utilizada foi a de Kahn\n\n");
	
	start_t = clock();
	ordenacao_kahn(med_g);
	end_t = clock();
	total_t = (end_t - start_t);
   	fprintf(data,"Algoritmo de Kahn, para 100 vertices, levou %ld Clocks\n", total_t);

	printf("\n");
	printf("Ordenação do grafo construido a partir do arquivo top_med.txt\nA ordenação utilizada foi a baseada no DFS\n\n");
	
	start_t = clock();
	ordenacao_dfs(med_g);
	end_t = clock();
	total_t = (end_t - start_t);
   	fprintf(data,"Algoritmo de DFS, para 100 vertices, levou %ld Clocks\n", total_t);

	printf("\n");

	
	constroi_grafo(&large_g, "top_large.txt");
	printf("Ordenação do grafo construido a partir do arquivo top_large.txt\nA ordenação utilizada foi a de Kahn\n\n");
	
	start_t = clock();
	ordenacao_kahn(large_g);
	end_t = clock();
	total_t = (end_t - start_t);
   	fprintf(data,"Algoritmo de Kahn, para 10000 vertices, levou %ld Clocks\n", total_t);

	printf("\n");
	printf("Ordenação do grafo construido a partir do arquivo top_large.txt\nA ordenação utilizada foi a baseada no DFS\n\n");
	
	start_t = clock();
	ordenacao_dfs(large_g);
	end_t = clock();
	total_t = (end_t - start_t);
   	fprintf(data,"Algoritmo de DFS, para 10000 vertices, levou %ld Clocks\n", total_t);

	printf("\n");

	constroi_grafo(&huge_g, "top_huge.txt");
	printf("Ordenação do grafo construido a partir do arquivo top_huge.txt\nA ordenação utilizada foi a de Kahn\n\n");
	
	start_t = clock();
	ordenacao_kahn(huge_g);
	end_t = clock();
	total_t = (end_t - start_t);
   	fprintf(data,"Algoritmo de Kahn, para 100000 vertices, levou %ld Clocks\n", total_t);

	printf("\n");
	printf("Ordenação do grafo construido a partir do arquivo top_huge.txt\nA ordenação utilizada foi a baseada no DFS\n\n");
	
	start_t = clock();
	ordenacao_dfs(huge_g);
	end_t = clock();
	total_t = (end_t - start_t);
   	fprintf(data,"Algoritmo de DFS, para 100000 vertices, levou %ld Clocks\n", total_t);
   	fprintf(data,"Como é possivel perceber, o algoritmo de ordenação topologica por DFS possui um desempenho muito maior que o algoritmo de Kahn\n");
   	fprintf(data,"Quando o grafo é pequeno a diferença é inperceptível, mas ao analisar grafos grandes, percebemos a diferença no desempenho\n");

	printf("\n");

	return 0;
}