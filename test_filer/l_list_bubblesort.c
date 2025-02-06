/**
 * @authors
 * Steffen Viken Valvaag
 * Odin Bjerke <odin.bjerke@uit.no>
 */

#include "list.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct lnode lnode_t;
struct lnode {
    lnode_t *next;
    lnode_t *prev;
    void *item;
};

struct list {
    lnode_t *head;
    lnode_t *tail;
    size_t length;
    int cmpfn;
};

struct list_iter {
    list_t *list;
    lnode_t *node;
};


// Lager og returner en dobbellenket liste. Inneholder peker til head og tail, og en sammenligning funksjon for elementer. Har variabel for lengde. 
list_t *list_create() {
    list_t *list = malloc(sizeof(list_t));
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    return list;
}

// Ødelegger listen ved å frigi minnet til listen og en item
void list_destroy(list_t *list) {
    free(list);
}

// returnere lengden av listen
size_t list_length(list_t *list) {
    if (list->length == 0) {
        return 0;
    }
    return list->length;

}

// Lager en node og lagre pekeren til noden, setter den til head av listen. To forksjellige scenarier: En der listen er tom og en der listen inneholder noder fra før.
int list_addfirst(list_t *list, void *item) {
    lnode_t *first_node = malloc(sizeof(lnode_t));
    if (first_node == NULL)
    
    {
        printf("\nERROR: Failed to allocate memory to new node to head");
        return -1;
    }
    
    first_node->item = item;
    if (list->length == 0) {
        list->tail = first_node;
        list->head = first_node;
    }
    else {
        list->head->prev = first_node;
        first_node->next = list->head;
        list->head = first_node;
    }
    list->length++;
    return 0;
}

// Samme som funksjonen over bare legger til node i tail. Har også to scenarier ved en tom eller ikke liste. 
int list_addlast(list_t *list, void *item) {
    lnode_t *last_node = malloc(sizeof(lnode_t)); 
    if (last_node == NULL)
    {
        printf("\nERROR: Failed to allocate memory to new node to tail");
        return -1;
    }
    last_node->item = item;
    if (list->length == 0){
        list->head = last_node;
        list->tail = last_node;
        list->length++;
    }
    else{ 
        last_node->prev = list->tail;
        list->tail->next = last_node;
        list->tail = last_node;
        list->length++;
    }
    return 0;
}

// Fjerner første node i listen og returnere item av node
void *list_popfirst(list_t *list) {
    if (list->head == NULL){
        printf("\nERROR: List has no head");
        exit(EXIT_FAILURE);
    }
    lnode_t *tmp_node = list->head;
    if (tmp_node == NULL){
        printf("\nERROR: Failed to allocate memory to temporary item");
        exit(EXIT_FAILURE);
    }
    void *tmp_item = tmp_node->item;
    list->head = list->head->next;
    free(tmp_node);
    list->length--;
    return tmp_item;
} 

// Fjerner siste node i listen og returnere item av node
void *list_poplast(list_t *list) {
    if (list->tail == NULL)
    {
        printf("\nERROR: List has no tail");
        return NULL;
    }
    lnode_t *tmp_node = list->tail;
    void *tmp_item = list->tail->item;
    list->tail = list->tail->prev;
    free(tmp_node);
    tmp_node = NULL;
    list->length--;
    return tmp_item;    
}

// Funksjon som finner item i listen. Bruker cmpfn funksjon for å sammenligne items i listen, iterer gjennom listen til noden er funnet eller ikke (returnere 1 eller 0 henholdsvis)


/* ---- list iterator ---- */


// Lager en liste iterator for å gå gjennom listen. Returnere peker på iterator. Iterator har en node som fungerer brukes til å itereres gjennom listen. 
list_iter_t *list_createiter(list_t *list) {
    list_iter_t *iter = malloc(sizeof(list_iter_t));
    iter->node = list->head;
    iter->list = list;
    if (iter == NULL){
        printf("\nERROR: No iter created");
        return NULL;
    }
    else {
        return iter;
    }

}

// Ødelegger iterator
void list_destroyiter(list_iter_t *iter) {
    if (iter == NULL){
        printf("\nERROR: No iter to destroy");
    }
    free(iter);
    iter = NULL;
}

// Hvis iterator er utenfor listen (gått ut av listens lengde), så returnere den 0.
int list_hasnext(list_iter_t *iter) {
    if (iter->node == NULL)
    {
        return 0;
    }
    else {
        return 1;
    }
}


// Returnere item for noden som iteratoren er på. Går videre til neste node i listen. 
void *list_next(list_iter_t *iter) {
    void *tmp = iter->node->item;
    iter->node = iter->node->next;
    return tmp;
}

// Setter iterator tilbake til start
void list_resetiter(list_iter_t *iter) {
    if (iter->list->head == NULL)
    {
        printf("\nERROR: List has no head to restart");
    }
    
    iter->node = iter->list->head;
}



/* ---- mergesort: Steffen Viken Valvaag ---- */

/*
 * Merges two sorted lists a and b using the given comparison function.
 * Only assigns the next pointers; the prev pointers will have to be
 * fixed by the caller.  Returns the head of the merged list.
 */


// void list_sort(list_t *list) {
//     /* Recursively sort the list */
//     list->head = mergesort_(list->head, list->cmpfn);

//     /* Fix the tail and prev links */
//     lnode_t *prev = NULL;
//     for (lnode_t *n = list->head; n != NULL; n = n->next) {
//         n->prev = prev;
//         prev = n;
//     }
//     list->tail = prev;
// }

 // test fra oblig 1

int compare(const char *a, const char *b) {
    return (int) (*a - *b);
}
 
void swap(lnode_t *a, lnode_t *b)  
{  
    void *temp = a->item;  
    a->item = b->item;  
    b->item = temp;  
}  

void list_sort(list_t *list) {
    printf("\n Start av sort:");
    int swapped;
    lnode_t *start;
    lnode_t *node_ptr = NULL;
    if (list->head == NULL)
    {
        printf("Head is  null");
       return;
    }
    do {
        swapped = 0;
        start = list->head;
        while (start->next != list->tail->next)
        {
            printf("\n%s", start->item);
            printf("\n%s", start->next->item);
            if (compare(start->item,start->next->item) > 0){
        
                swap(start, start->next);
                swapped = 1;
                printf("\nStart item is now: %s", start->item);
                printf("\nStart->next item is now: %s", start->next->item);
                printf("\nHead item is now: %s", list->head->item);
                printf("\nHead->next item is now: %s", list->head->next->item);
            }
            printf("\n%s", start->item);
            start = start->next;
            printf("\n%s", start->item);
        }
        node_ptr = start;
    }
    while(swapped);
    }



int main(){
    list_t *list = list_create();
    list_addfirst(list, "hey");
    list_addfirst(list, "test");
    list_addfirst(list, "a");
    list_addfirst(list, "b");
    lnode_t *tmp = list->head;
    for (size_t i = 0; i < list->length; i++)
    {
        printf("\n%s", tmp->item);
        fflush(stdout);
        tmp = tmp->next;
    }

        list_sort(list);
    tmp = list->head;
    for (size_t i = 0; i < list->length; i++)
    {
        printf("\n%s", tmp->item);
        tmp = tmp->next;
    }
    
    printf("\n");
    return 0;

}