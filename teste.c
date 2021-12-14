#include "teste.h"
#include <stdlib.h>

void teste_alocacao(){
    
    tabela = fopen("TabelaAlocacao.csv", "w");
    fprintf(tabela, "Alocacao, TempoMyMalloc, TempoMalloc\n");
    
    int x = 1;
    int size = 1024;
    while(x < 10000){
        
        clock_t myMallocBegin = clock();
        int *A = (int*) MyMalloc(size*x);
        clock_t myMallocEnd = clock();
        double time_mymalloc = (double)(myMallocEnd - myMallocBegin) / CLOCKS_PER_SEC;
        
        MyMallocFree(A);
        
        clock_t mallocBegin = clock();
        int *B = (int*) malloc(size*x);
        clock_t mallocEnd = clock();
        double time_malloc = (double)(mallocEnd - mallocBegin) / CLOCKS_PER_SEC;
        
        free(B);
        
        fprintf(tabela, "%i,%lf,%lf\n", (size*x), time_mymalloc, time_malloc);
        x++;
    }
    
    fclose(tabela);
}

void teste_aloc_desaloc(){
    
    tabela1 = fopen("TabelaAlocacaoDesaloc.csv", "w");
    fprintf(tabela, "Alocacao, TempoMyMalloc, TempoMalloc\n");
    
    int x = 3;
    int size = 1024;
    while(x < 10000){
        
        clock_t myMallocBegin = clock();
        int *A = (int*) MyMalloc(size*x*3);
        int *B = (int*) MyMalloc(size*x*40);
        int *C = (int*) MyMalloc(size*x*15);
        int *D = (int*) MyMalloc(size*x*30);
        MyMallocFree(B);
        MyMallocFree(C);
        clock_t myMallocEnd = clock();
        
        double time_mymalloc = (double)(myMallocEnd - myMallocBegin) / CLOCKS_PER_SEC;
        
        clock_t mallocBegin = clock();
        int *E = (int*) malloc(size*x*3);
        int *F = (int*) malloc(size*x*40);
        int *G = (int*) malloc(size*x*15);
        int *H = (int*) malloc(size*x*30);
        free(F);
        free(G);
        clock_t mallocEnd = clock();
        
        double time_malloc = (double)(mallocEnd - mallocBegin) / CLOCKS_PER_SEC;
        
        fprintf(tabela, "%i,%lf,%lf\n", (size*x), time_mymalloc, time_malloc);
        x++;
    }
    
    fclose(tabela);
}




