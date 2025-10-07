#include "arq.h"
#include <time.h>

extern void leitura(struct descF *p, const char *dataset_v1, int qtdCasos, int tipoPrioridade);
extern struct descF *cria(int tamInfo);

int main(void) {
    int opcao;
    int bases[] = {500, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000, 5500, 6000, 6500, 7000, 7500, 8000, 8500, 9000};
    int nBases = sizeof(bases) / sizeof(bases[0]);

    printf("Escolha sua prioridade:\n");
    printf("1. Ranking\n");
    printf("2. Matricula\n");
    printf("3. Sair\n");
    scanf("%d", &opcao);

    if (opcao == 3) return 0;
    if (opcao != 1 && opcao != 2) {
        printf("Opção inválida.\n");
        return 0;
    }

    struct descF *fila = cria(sizeof(info));

    for (int i = 0; i < nBases; i++) {
        reinicia(fila);
        leitura(fila, "dataset_v1.csv", bases[i], opcao);
        printf("Base com %d casos processada.\n", bases[i]);
    }

    destroi(fila);
    printf("Resultados salvos em %s\n", (opcao == 1 ? "result_ranking.csv" : "result_matricula.csv"));
    return 0;
}

