#include <stdio.h>
#include <stdlib.h>
#define GNUPLOT "gnuplot -persist"
  
int main(int argc, char **argv)
{
    FILE *gp;
    gp = popen(GNUPLOT, "w");

    printf("Será aberto 3 graficos, O grafico do DFS, grafico do Khan, e os dois juntos\n");
    if (gp == NULL) {
        printf("Erro ao abrir pipe para o GNU plot.\n"
            "Instale com 'sudo apt-get install gnuplot'\n");
        exit(0);
    }
    fprintf(gp, "plot 'data_khan.txt'\n");
    fprintf(gp, "rep 'data_dfs.txt'\n");
    fclose(gp);

    gp = popen(GNUPLOT, "w");
    if (gp == NULL) {
        printf("Erro ao abrir pipe para o GNU plot.\n"
            "Instale com 'sudo apt-get install gnuplot'\n");
        exit(0);
    }
    fprintf(gp, "plot 'data_khan.txt'\n");
    fclose(gp);

    gp = popen(GNUPLOT, "w");
    if (gp == NULL) {
        printf("Erro ao abrir pipe para o GNU plot.\n"
            "Instale com 'sudo apt-get install gnuplot'\n");
        exit(0);
    }
    fprintf(gp, "plot 'data_dfs.txt'\n");
    fclose(gp);
}
