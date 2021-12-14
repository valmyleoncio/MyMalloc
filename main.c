#include <stdio.h>
#include "MyMalloc.h"
#include "teste.h"

int main() 
{
    teste_alocacao();
    teste_aloc_desaloc();
    MyMallocGerency(true);
    return 0;
}
