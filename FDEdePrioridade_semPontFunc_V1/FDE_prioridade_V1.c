#include "arq.h"
#include <time.h>
long long iteracoesGlobais = 0;


/*************** CRIA ***************/
struct descF * cria(int tamInfo)
{   	
    struct descF *desc = (struct descF*) malloc(sizeof(struct descF));
    if(desc != NULL) {
        desc->cauda = NULL;
        desc->frente = NULL;
	desc->tamInfo= tamInfo;
    }
    return desc;
}

/*************** INSERE A PARTIR DA FRENTE RANCKING ***************/
int insereRancking(info *pInfo, struct descF *p)
{ int result;
  struct noFila *novoNoFila=NULL, *visitado=NULL;
  if ((novoNoFila = (struct noFila *) malloc(sizeof(struct noFila))) != NULL)
    { 
	memcpy(&(novoNoFila->dados),pInfo, p->tamInfo);
  	if(p->frente == NULL && p->cauda == NULL) /*fila vazia*/
    	 {  novoNoFila->atras = novoNoFila->defronte = NULL;
    	    p->frente = p->cauda = novoNoFila;
    	    	
    	 }
        else
    	 { // 
    	 	if(novoNoFila->dados.ranking < p->cauda->dados.ranking) /*novo elemento � o de menor prioridade */
    	 	{ 	novoNoFila->atras=NULL;
    	 		novoNoFila->defronte=p->cauda;
    	 		p->cauda->atras=novoNoFila;
    	 		p->cauda=novoNoFila;
    	 		
    	 	}
    	 	else
    	 	{    	 
		   visitado = p->frente; /*maior prioridade na frente */
       		 while (visitado->atras != NULL && (visitado->dados.ranking >= novoNoFila->dados.ranking)) {
   			 visitado = visitado->atras;
   			 iteracoesGlobais++; // <--- aqui conta a iteração
	}

           
       	   if(visitado->dados.ranking < novoNoFila->dados.ranking)   /* novo item fica a frente do visitado */
         	   {   	
					novoNoFila->atras = visitado;
      				if (visitado->defronte != NULL)
      				{       novoNoFila->defronte = visitado->defronte;
      				        visitado->defronte->atras = novoNoFila;
      				} 
      				else
      				   {  // novo item � o de maior prioridade de todos na fila, sendo a nova frente
						   novoNoFila->defronte = NULL;      
						  p->frente = novoNoFila;
				   }	   
					visitado->defronte = novoNoFila;  
		   }	
		   //else //<<- novo item � o de menor prioridade de todos na fila, sendo a nova cauda
		   	  //Essa � uma condicao ja tratada 
			//{
			//		novoNoFila->defronte = visitado;
			//		novoNoFila->atras = NULL;
			//		visitado->atras = novoNoFila;
			//		p->cauda = novoNoFila; 
			//}	
         	}   
			
	}//
	return SUCESSO;
    }
    
	return FRACASSO;

}

/*************** INSERE A PARTIR DA FRENTE MATRICULA ***************/
int insereMatricula(info *pInfo, struct descF *p)
{ int result;
  struct noFila *novoNoFila=NULL, *visitado=NULL;
  if ((novoNoFila = (struct noFila *) malloc(sizeof(struct noFila))) != NULL)
    { 
	memcpy(&(novoNoFila->dados),pInfo, p->tamInfo);
  	if(p->frente == NULL && p->cauda == NULL) /*fila vazia*/
    	 {  novoNoFila->atras = novoNoFila->defronte = NULL;
    	    p->frente = p->cauda = novoNoFila;
    	    	
    	 }
        else
    	 { // 
    	 	if(novoNoFila->dados.matricula < p->cauda->dados.matricula) /*novo elemento � o de menor prioridade */
    	 	{ 	novoNoFila->atras=NULL;
    	 		novoNoFila->defronte=p->cauda;
    	 		p->cauda->atras=novoNoFila;
    	 		p->cauda=novoNoFila;
    	 		
    	 	}
    	 	else
    	 	{    	 
		   visitado = p->frente; /*maior prioridade na frente */
       	   	while (visitado->atras != NULL && (visitado->dados.matricula >= novoNoFila->dados.matricula)) {
   			 	visitado = visitado->atras;
   			 	iteracoesGlobais++;
			}

           
       	   if(visitado->dados.matricula < novoNoFila->dados.matricula)   /* novo item fica a frente do visitado */
         	   {   	
					novoNoFila->atras = visitado;
      				if (visitado->defronte != NULL)
      				{       novoNoFila->defronte = visitado->defronte;
      				        visitado->defronte->atras = novoNoFila;
      				} 
      				else
      				   {  // novo item � o de maior prioridade de todos na fila, sendo a nova frente
						   novoNoFila->defronte = NULL;      
						  p->frente = novoNoFila;
				   }	   
					visitado->defronte = novoNoFila;  
		   }	
		   //else //<<- novo item � o de menor prioridade de todos na fila, sendo a nova cauda
		   	  //Essa � uma condicao ja tratada 
			//{
			//		novoNoFila->defronte = visitado;
			//		novoNoFila->atras = NULL;
			//		visitado->atras = novoNoFila;
			//		p->cauda = novoNoFila; 
			//}	
         	}   
			
	}//
	return SUCESSO;
    }
    
	return FRACASSO;

}



/*************** REMOVE DA FRENTE ***************/
int remove_(info *reg, struct descF  *p)
{
	int ret = FRACASSO;
	struct noFila *aux = p->cauda;

    if(p->cauda != NULL && p->frente != NULL) 
    {
       	memcpy(reg, &(p->frente->dados), p->tamInfo);

		if(aux == p->frente) 
		{ // caso tenha 1 elemento apenas
			free(p->frente);
			p->frente = p->cauda = NULL;
		}
		else 
		{	p->frente= p->frente->atras;
            free(p->frente->defronte); 
            p->frente->defronte = NULL;
        	
		}
		ret = SUCESSO;
	}

	return ret;
}

/*************** BUSCA NA FRENTE ***************/
int buscaNaFrente(info *reg, struct descF *p)
{  
    int ret = FRACASSO;

    if(p->frente != NULL && p->cauda != NULL) { 	
        memcpy(reg, &(p->frente->dados), p->tamInfo);
        ret = SUCESSO;
    }

    return ret;
}

/*************** BUSCA NA CAUDA ***************/
int buscaNaCauda(info *reg, struct descF *p)
{
    int ret = FRACASSO;

    if(p->cauda != NULL && p->frente != NULL) {
        memcpy(reg, &(p->cauda->dados), p->tamInfo);
	ret = SUCESSO;
    }

    return ret;
}

/*************** VAZIA? ***************/
int testaVazia(struct descF *p)
{
    if(p->frente == NULL && p->cauda == NULL) {
        return SIM;
    }

    return NAO;
}

/*************** TAMANHO ***************/
int tamanhoDaFila(struct descF *p)
{ 
    int tam = 0;
    struct noFila *aux = p->cauda;

    while(aux != NULL) 
    { 	
		tam++;
        aux = aux->defronte;

    }

    return tam;
}

/*************** PURGA ***************/
int reinicia(struct descF *p)
{   int ret=FRACASSO;
    struct noFila *aux=NULL;

    if(p->frente != NULL && p->cauda != NULL) 
    {  
        aux = p->cauda->defronte;
        while(aux != NULL) 
        {
            free(p->cauda);
            p->cauda = aux;
            aux = aux->defronte;
        }
        
        free(p->cauda);
        p->frente = NULL;
        p->cauda = NULL;
        ret=SUCESSO; 
    }
    return ret;	
}

/*************** DESTROI ***************/
struct descF * destroi(struct descF *p)
{
    reinicia(p);
    free(p);
    return NULL; // aterra o ponteiro externo, declarado na aplica��o
}

//======================Leitura=====================
void leitura(struct descF *p, const char *dataset_v1, int qtdCasos, int tipoPrioridade) {
    FILE *arquivo = fopen(dataset_v1, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", dataset_v1);
        return;
    }

	char linha[256];
    int totalLinhas = 0;

   
    fgets(linha, sizeof(linha), arquivo); //perguntar pq duas vezes pro chat

 
    while (fgets(linha, sizeof(linha), arquivo)) totalLinhas++;
    rewind(arquivo);


    fgets(linha, sizeof(linha), arquivo);

    if (qtdCasos > totalLinhas) qtdCasos = totalLinhas; // não entendi


    char **linhas = malloc(totalLinhas * sizeof(char *));
    for (int i = 0; i < totalLinhas; i++) {
        fgets(linha, sizeof(linha), arquivo);
        linha[strcspn(linha, "\n")] = '\0';
        linhas[i] = strdup(linha);
    }

    srand(time(NULL));
    long long totalIteracoes = 0;

    for (int i = 0; i < qtdCasos; i++) {
        int idx = rand() % totalLinhas;

        char linhaCopia[256];
        strcpy(linhaCopia, linhas[idx]);

        char *token = strtok(linhaCopia, ",");
        if (!token) continue;

        info *novoInfo = malloc(sizeof(info));

        strcpy(novoInfo->Nome, token);
        token = strtok(NULL, ",");
        novoInfo->matricula = token ? atol(token) : 0;
        token = strtok(NULL, ",");
        novoInfo->ranking = token ? atoi(token) : 0;
        token = strtok(NULL, ",");
        strcpy(novoInfo->curso, token ? token : "");

        // Contador de iterações
        extern long long iteracoesGlobais;
        iteracoesGlobais = 0;

        if (tipoPrioridade == 1)
            insereRancking(novoInfo, p);
        else
            insereMatricula(novoInfo, p);

        totalIteracoes += iteracoesGlobais;
    }

    // salvar estatísticas
    double media = (double) totalIteracoes / qtdCasos;
    FILE *out = fopen(tipoPrioridade == 1 ? "result_ranking.csv" : "result_matricula.csv", "a");
    fprintf(out, "%d,%lld,%.2f\n", qtdCasos, totalIteracoes, media);
    fclose(out);

    for (int i = 0; i < totalLinhas; i++) free(linhas[i]);
    free(linhas);
    fclose(arquivo);
}



//======================escrita=====================

void escrita(){

}


//======================Função Switch=====================
 
void prioridade() {
	int opcao;

	printf("Escolha a função para a fila:\n");
	printf("1.Insere\n");
	printf("2.Remove\n");
	printf("3. Sair\n");
	scanf("%d", &opcao);

	switch (opcao) {
		case 1:
			printf("Você escolheu a opção Rancking.\n");
			break;
		case 2:
			printf("Você escolheu a opção Matricula.\n");
			break;
		case 3:
			printf("Você escolheu a opção Sair.\n");
			break;
		default:
			printf("Opção inválida.\n");
	}

	return;
}