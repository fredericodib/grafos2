/*
Trabalho 2 de Grafos 1/2018
Alunos: 
Frederico Pinheiro Dib	15/0125925
Amanda Oliveira Alves   15/0116276

Como compilar:
$ gcc -ansi -Wall -o main main.c -lm
$ ./main

O resultado das ordenações estará registrado no arquivo ordenacao.txt
O resultado de tempo de execução de cada ordenação estará disponível no arquivo time.txt

Os dois arquivos já foram gerados!
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "grafo.h"
#include "ordenacao_kahn.c"
#include "ordenacao_dfs.c"


/* Essa função constrói um grafo a partir da leitura doarquivo texto */
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

/*Função que imprime nos arquivos*/
void print_text(FILE *time_report, FILE *ordenacao_file, GRAFO grafo, char* name_arq) {
	clock_t start_t, end_t, total_t;

	fprintf(ordenacao_file, "Maior ordenação do grafo construido a partir do arquivo %s.\nA ordenação utilizada foi a de Kahn\n\n", name_arq);
	
	start_t = clock();
	ordenacao_kahn(grafo, ordenacao_file);
	end_t = clock();
	total_t = (end_t - start_t);
   	fprintf(time_report,"Algoritmo de Kahn, para %d vertices, levou %ld Clocks\n", grafo.nvertices, total_t);
   	
	fprintf(ordenacao_file, "\n");
	fprintf(ordenacao_file, "Maior ordenação do grafo construido a partir do arquivo %s.\nA ordenação utilizada foi a baseada no DFS\n\n", name_arq);

	start_t = clock();
	ordenacao_dfs(grafo, ordenacao_file);
	end_t = clock();
	total_t = (end_t - start_t);
   	fprintf(time_report,"Algoritmo de DFS, para %d vertices, levou %ld Clocks\n", grafo.nvertices, total_t);

	fprintf(ordenacao_file, "\n");
}

/* Main */
int main() {
	
	FILE *time_report;
	time_report = fopen("time.txt", "w"); /* Abre arquivo time.txt */

	FILE *ordenacao_file;
	ordenacao_file = fopen("ordenacao.txt", "w"); /* Abre arquivo ordenacao.txt */

	GRAFO small_g;
	GRAFO med_g;
	GRAFO large_g;
	GRAFO huge_g;

	/* Para cada grafo gerado ocorrem dois tipos de ordenação topológica, uma feita com o algoritmo de Kahn e a outra 
	usando DFS. E também é medido o tempo de execução em clocks para cada uma das ordenações executadas. */
	/* A fonte dos algoritmos utilizados para fazer esse trabalho foram os slides disponibilizados pelo professor na 
	plataforma Aprender, e alguns links no google, como wikipedia */
	printf("ordenações iniciadas\n");

	constroi_grafo(&small_g, "top_small.txt");
	print_text(time_report, ordenacao_file, small_g, "top_smal.txt");

	printf("ordenações Kahn e DFS para o top_small.txt terminadas\n");

	constroi_grafo(&med_g, "top_med.txt");
	print_text(time_report, ordenacao_file, med_g, "top_med.txt");

	printf("ordenações Kahn e DFS para o top_med.txt terminadas\n");
	
	constroi_grafo(&large_g, "top_large.txt");
	print_text(time_report, ordenacao_file, large_g, "top_large.txt");

	printf("ordenações Kahn e DFS para o top_large.txt terminadas\n");

	constroi_grafo(&huge_g, "top_huge.txt");
	print_text(time_report, ordenacao_file, huge_g, "top_huge.txt");

	printf("ordenações Kahn e DFS para o top_huge.txt terminadas\n");
	printf("ordenações terminadas com sucesso\n");
	printf("As maiores ordenações topologicas encontradas foram gravadas no arquivo ordenacao.txt\n");
	printf("O relatorio do tempo está no arquivo time.txt\n");

   	fprintf(time_report,"Como é possivel perceber, o algoritmo de ordenação topológica por DFS possui um desempenho muito melhor do que o algoritmo de Kahn, no grafo com 100 vértices já é possível perceber uma grande diferença no tempo de execução entre os dois. Portanto o algoritmo de Kahn talvez só seja recomendado para o caso que o grafo possui 10 vértices.\n");
   	fprintf(time_report,"Quando o grafo é pequeno a diferença é desprezível, porém a medida que o número de vértices aumenta, percebemos a mudança no desempenho das ordenações.\n");
   	fprintf(time_report,"Portanto para grafos com muitos vértices é recomendado que utilize a ordenação com DFS.\n");
   	fprintf(time_report,"A fonte dos algoritmos utilizados para fazer esse trabalho foram os slides disponibilizados pelo professor na plataforma Aprender.\n");
	printf("\n");

	return 0;
}