#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct node_s{
    int data;
    struct node_s *next;
}node_t;

typedef struct list_s{
    node_t *head;
    node_t *tail;
    size_t size;
}list_t;

list_t *list_alloc(void);
void list_free(list_t *list);
int list_prepend(list_t *list, int val);
int list_append(list_t *list, int val);
int list_insert(list_t *list, int val, size_t pos);
int list_rm(list_t *list, int *val, size_t pos);
int list_set(list_t *list, int val, size_t pos);
int list_get(list_t *list, int *val, size_t pos);
void printNodes(list_t *list);

int main(){
    list_t *list = list_alloc();
    printf("TESTING LINKED LIST\n");

    list_append(list, 1);
    list_prepend(list, 0);
    list_append(list, 2);
    printf("Current list size: %d\n", list -> size);
    printNodes(list);
    printf("\n");
 
    list_insert(list, 3, 3);
    list_insert(list, 4, 4);
    printf("Current list size: %d\n", list -> size);
    printNodes(list);
    printf("\n");

    int data;
    list_rm(list, &data, 4);
    printf("Current list size: %d\n", list -> size);
    printNodes(list);
    printf("\n");
    
    list_set(list, 3, 4);
    printf("Current list size: %d\n", list -> size);
    printNodes(list);

    list_free(list);
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

void list_free(list_t *list){
    for(size_t i = list -> size; i > 0; i--){
        node_t *temp = list -> head;
        list -> head = list -> head -> next;
	free(temp);
    }
    free(list);
}

int list_prepend(list_t *list, int val){
    node_t* node = (node_t*)malloc(sizeof(node_t));
    if(!node){
        return 1;
    }
    if(!list -> tail){
        list -> tail = node;
    }
    node -> data = val;

    node -> next = list -> head;
    list -> head = node;
    list -> size++;
    return 0;
}

int list_append(list_t *list, int val){
    if(!list -> tail){
        list_prepend(list, val);
        return 0;
    } 
    node_t* node = (node_t*)malloc(sizeof(node_t));
    if(!node){
	    return 1;
    }
    node -> data = val;
    list -> tail -> next = node;
    list -> tail = node;
    node -> next = NULL;
    list -> size++;
    return 0;
}

int list_insert(list_t *list, int val, size_t pos){
    if(!list -> tail||pos <= 0){
	    return list_prepend(list, val);
    }
    if(pos > list -> size - 1){
	    return list_append(list, val);
    }
    node_t *node = (node_t*)malloc(sizeof(node_t));
    if(!node){
	    return 1;
    }
    node -> data = val;
    node_t *temp_pos = list -> head;
    for(int i = 0; i < pos-1; i++){
        temp_pos = temp_pos -> next;
    }
    node -> next = temp_pos -> next;
    temp_pos -> next = node;
    list -> size++;
    return 0;
}

int list_rm(list_t *list, int *val, size_t pos){
    if(!list -> head || pos > list -> size - 1){
	    return 1;
    }
    node_t *temp_pos = list -> head;
    if(pos <= 0){
        list -> head = list -> head -> next;
        *val = temp_pos -> data; 
        free(temp_pos);
        list -> size--;
	return *val;
    }
    else{
        for(int i = 0; i < pos-1; i++){
            temp_pos = temp_pos -> next;
        }
        node_t *temp_node = temp_pos -> next;
        temp_pos -> next = temp_node -> next;
        *val = temp_node -> data; 
        free(temp_node);
        list -> size--;
        return *val;
    }
}

int list_set(list_t *list, int val, size_t pos){
    if(pos > list -> size - 1){
	    return 1;
    }
    if(pos == 0){
        list -> head -> data = val;
        return 0;
    }
    node_t *temp_pos = list -> head;
    for(int i = 0; i < pos; i++){
        temp_pos = temp_pos -> next;
    }
    temp_pos -> data = val;
    return 0;
}

int list_get(list_t *list, int *val, size_t pos){
    node_t *temp_pos = list -> head;
    for(int i = 0; i < pos; i++){
        temp_pos = temp_pos -> next;
    }
    *val = temp_pos -> data;
    return temp_pos -> data;
}

void printNodes(list_t *list){
    int data;
    for(size_t i = 0; i < list->size; i++)
    {
        list_get(list, &data, i);
        printf("data at %ldth index: %d\n", i, data);
    }
}
