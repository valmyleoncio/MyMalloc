#ifndef  MYMALLOC_H
#define  MYMALLOC_H
    
    #include <stdio.h>
    #include <sys/types.h>
    #include <unistd.h>
    #include <stdbool.h>
    #define BLOCK_SIZE (sizeof(struct METADATA) -1)
    //#define align4(x) (((((x)-1)>>2)<<2)+4)
    
    typedef struct METADATA *MD;

    struct METADATA {
        MD next;
        MD prev;
        size_t size;
        bool free;
        void* ptr;
        char data[1];
    }__attribute__((packed));

    int MyMallocInit (int size);
    void* MyMalloc (int size);
    bool MyMallocFree(void *ptr);
    
    MD find_block(MD *last, size_t size);
    void split_block (MD b, size_t s);
    MD extend_heap(MD last , size_t s);
    MD fusion(MD b);    
    MD get_block(void *p);
    bool valid_addr(void *p);
    
    void MyMallocGerency(bool isActive);
    void verificarBase(MD metadata);
    void totalMemoriaAlocada(MD metadata);
    void totalBlocos(MD metadata);

#endif  /*MYMALLOC_H*/