#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct node_s{
    void *data;
    struct node_s *prev;
    struct node_s *next;
}node_t;

typedef struct list_s{
    node_t *head;
    node_t *tail;
    size_t size;
}list_t;

list_t *list_alloc(void);
void list_free(list_t *list, void (*free_data)(void *data));
int list_prepend(list_t *list, void *val);
int list_append(list_t *list, void *val);
int list_insert(list_t *list, void *val, size_t pos);
int list_rm(list_t *list, void **val, size_t pos);
int list_set(list_t *list, void *val, size_t pos);
int list_get(list_t *list, void **val, size_t pos);
void printNodes(list_t *list);

int main(){
    list_t *list = list_alloc();
    printf("TESTING LINKED LIST\n");
    
    printNodes();
        
    return 0;
}

list_t *list_alloc(void){
    list_t *list = (list_t*)malloc(sizeof(list_t));
    if(!list){
        return NULL;
    }
    list -> head = NULL;
    list -> tail = NULL;
    list -> size = 0;
    return list;
}

void list_free(list_t *list, void (*free_data)(void *data)){

}

int list_get(list_t *list, void **val, size_t pos){
    node_t *temp_pos = list -> head;
    for(int i = 0; i < pos; i++){
        temp_pos = temp_pos -> next;
    }
    **val = temp_pos -> data;
    return temp_pos -> data;
}

void printNodes(list_t *list){
    int* data;
    for(size_t i = 0; i < list->size; i++)
    {
        list_get(list, &&data, i);
        printf("data at %ldth index: %d\n", i, data);
    }
}
