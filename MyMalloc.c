#include "MyMalloc.h"

void *base = NULL;

int MyMallocInit (int size){
    
  return 0;
  
}

void* MyMalloc(int size){
    
    MD b, last;
    
    if (base) {
        
        last = base;
        b = find_block(&last, size);
        if (b) {
            
            if ((b->size - size) >= (BLOCK_SIZE))
                split_block(b, size);

            b->free = true;
            
        } else {
            
            b = extend_heap (last ,size);
            if (!b){
                return(NULL);
            }
        }
    } else {
      
        b = extend_heap (NULL, size);
        if (!b){
            return(NULL);
        }
        base = b;
    }
    
  return(b->data);
}

bool MyMallocFree(void *ptr){

    //true
    if(valid_addr(ptr)){
        
        MD b = (MD) get_block(ptr);
        b->free = true;
        
        if(b->prev && b->prev->free){
            b = fusion(b->prev);
        }
            
        if (b->next){
            fusion(b);
        } else {

            if(b->prev){
             b->prev->next = NULL;
            }
                    
            else{
                base = NULL;
            }

            if(brk(b) == -1){
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}


/*
*
*
*  Funcoes necessarias
*
*
*/


// Esta função está tentando encontrar algum bloco que se encaixe no tamanho.
MD find_block(MD *last, size_t size) {
        
    MD b = base;
        
    while (b && ! (b->free && b->size >= size)) {
        *last = b;
        b = b->next;
    }
    return (b);
}


// Dividindo um bloco em dois blocos, o segundo será free.
void split_block (MD b, size_t s){
    
    MD new;
    new = b->data + s;
    new->size = b->size - s - BLOCK_SIZE ;
    new->next = b->next;
    new->prev = b;
    new->free = 1;
    new->ptr = new->data;
    b->size = s;
    b->next = new;
    
}


// Esta função estenderá o heap com o tamanho fornecido
MD extend_heap(MD last , size_t s){
    
    MD b;
    b = sbrk (0);
    if (sbrk( BLOCK_SIZE + s) == (void*) -1)
        return (NULL );
    b->size = s;
    b->next = NULL;
    if (last)
        last->next = b;
    b->free = 0;
    return (b);
    
}


// Fusao de dois blocos lançados
MD fusion(MD b){
    if(b->next && b->next->free) {
        b->size += BLOCK_SIZE + b->next->size;
        b->next = b->next->next;
        if(b->next)
            b->next->prev = b;
        
        return (b);
    }
}


// Get the block from and addr
MD get_block(void *p){
    char *tmp = (char*) p;
    return (MD) (p = tmp -= BLOCK_SIZE);
}


// Valid addr for free
bool valid_addr(void *p){
    
    if (base)
    {
        if(p > base && p < sbrk(0)){
            return p == ( get_block (p)) -> ptr;
        }
    }
  return false;
}


/*
*
*
*  GERENCY
*
*
*/


void MyMallocGerency(bool isActive){
    
    if(isActive)
    {
        MD metadata = (MD) base;
    
        verificarBase(metadata);
        totalMemoriaAlocada(metadata);
        totalBlocos(metadata);
    }
}

void verificarBase(MD metadata){
    
    if(metadata == NULL)
    {
        printf("Nenhum bloco alocado\n");
        
    } else {
        printf("Blocos alocados\n");
    }
}

void totalMemoriaAlocada(MD metadata){
    
    unsigned long total = 0;
    
    for (int i = 0; metadata != NULL; i++, metadata = metadata -> next) {
        total += metadata -> size;
    }
    
    printf("Total da alocacao: %li Bytes → %li Bits \n", total, (total*8));
}

void totalBlocos(MD metadata){
    
    int cont = 0;
    int usados = 0;
    int disponiveis = 0;
    
    for (int i = 0; metadata != NULL; i++, metadata = metadata -> next) {
        cont += 1;
        
        if( metadata -> free ){
            disponiveis += 1;
        } else {
            usados += 1;
        }
    }
    
    printf("Total de Blocos: %i\n", cont);
    printf("Utilizados: %i\n", usados);
    printf("Disponiveis(free): %i\n", disponiveis);
}