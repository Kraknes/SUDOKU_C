// #include "common.h"
// #include "futil.h"
// #include "printing.h"
// #include "list.h"

// #include <stdio.h>
// #include <stdlib.h>
// #include <stdint.h>

// #include <string.h>
// #include <errno.h>
// #include <ctype.h>




// typedef struct lnode lnode_t;
// struct lnode {
//     lnode_t *next;
//     lnode_t *prev;
//     void *item;
// };

// struct list {
//     lnode_t *head;
//     lnode_t *tail;
//     size_t length;
//     cmp_fn cmpfn;
// };

// struct list_iter {
//     list_t *list;
//     lnode_t *node;
// };


// // funker
// list_t *list_create(cmp_fn cmpfn) {
//     list_t *list = malloc(sizeof(list_t));
//     list->head = NULL;
//     list->tail = NULL;
//     list->length = 0;
//     list->cmpfn = cmpfn;
//     return list;
// }
// // funker, men bør ha en itererings funksjon for hver node istedenfor list->length
// size_t list_length(list_t *list) {
//     if (list->length == 0) {
//         return 0;
//     }
//     return list->length;
// }

// // funker kanskje? 
// void list_destroy(list_t *list, free_fn item_free) {

//     free(list);
//     free(item_free);
//     printf("list destroyed \n");

// }

// // FUNKER
// int list_addfirst(list_t *list, void *item) {
//     lnode_t *first_node = malloc(sizeof(lnode_t));
//     first_node->item = item;

//     if (list->length == 0) {
//         list->tail = first_node;
//         list->head = first_node;
//     }
//     else {
//         list->head->prev = first_node;
//         first_node->next = list->head;
//         list->head = first_node;
//     }

//     list->length++;
//     return 0;
// }

// // FUNKER
// int list_addlast(list_t *list, void *item) {
//     lnode_t *last_node = malloc(sizeof(lnode_t));
//     last_node->item = item;
//     last_node->prev = list->tail;
//     list->tail->next = last_node;
//     list->tail = last_node;
    
//     list->length++;
//     return 0;
// }

// // FUNKER
// void *list_popfirst(list_t *list) {

//     printf("\n~~~ LISTPOP_FIRST TEST ~~~\n");

//     if (list->head == NULL){
//         printf("No head available");
//         return NULL;
//     }
//     lnode_t *tmp_node = list->head;
//     if (list->head == tmp_node){
//         printf("GODKJENT: head og temp er lik\n");
//     }
//     if (list->head->item == tmp_node->item) {
//         printf("GODKJENT: items i head og tmp er lik\n");
//     }

//     void *tmp_item = tmp_node->item;
//     if (tmp_item == NULL){
//         printf("Head has no item");
//         return NULL;
//     }

//     list->head = list->head->next;
//     free(tmp_node);
//     tmp_node = NULL;
//     if (tmp_node == NULL)
//     {
//         printf("GODKJENT: HEAD har blitt slettet\n");
//     }
    
//     list->length--;
//     printf("Test av temp item: %s\n", (char *)tmp_item);
//     return tmp_item;
// }
// // funker OK, men har ikke implementert node->prev som kunne gjort ting enklere
// void *list_poplast(list_t *list) {
//     printf("\n~~~ LISTPOP_LAST TEST ~~~\n");
//     if (!list->tail)
//     {
//         printf("FAILURE: Listen har ikke tail \n");
//         return NULL;
//     }
    
//     lnode_t *tmp_node = list->tail;
//     void *tmp_item = list->tail->item;
//     list->length--;
//     printf("Dette er TAIL før sletting:\t %s\n", (char *)list->tail->item);
//     list->tail = list->tail->prev;
//     free(tmp_node);
//     tmp_node = NULL;
    
//     if (tmp_node == NULL)
//     {
//         printf("GODKJENT: TAIL har blitt slettet\n");
//     }
//     printf("Dette er TAIL etter sletting:\t %s\n", (char *)list->tail->item);
//     return tmp_item;    
// }

// int list_contains(list_t *list, void *item) {
//     printf("\n~~~ LIST_CONTAINS TEST ~~~\n");
//     if (!list) {
//         printf("FAILURE: Liste eksistere ikke\n");
//         return 0;
//     }
//     lnode_t *node_cmp = list->head;
//     for (size_t i=1; i <= list->length; i++)
//     {
//         if (list->cmpfn(item, node_cmp->item) == 0)
//         {
//             printf("SUCCESS: Funnet likhet\n");
//             return 1;
//         }
//         else {
//             printf("Likhet ikke funnet, fortsetter videre\n");
//             printf("i = %li\n", i);
//             node_cmp = node_cmp->next;
//         }
        
//     }
    
//     // for (lnode_t *n = list->head; n != NULL; n = n->next) {
//     //     if (list->cmpfn(n->item, item) == 0) {
//     //         return 1;
//     //     }
//     printf("FAILURE: Ingen likheter funnet");
//     return 0;
//     // }
// }

// list_iter_t *list_createiter(list_t *list) {
//     printf("\n ~~~~ LIST ITER TEST ~~~~ \n");
//     list_iter_t *iter = malloc(sizeof(list_iter_t));
//     iter->node = list->head;
//     iter->list = list;
//     if (!iter){
//         printf("FAILURE: No iter created\n");
//         return NULL;
//     }
//     else {
//         printf("SUCCESS, Iter created if memory adresses are alike: %p ", iter);
//         return iter;
//     }

// }

// void list_destroyiter(list_iter_t *iter) {
//     printf("\n ~~~~ ITER DESTROY TEST ~~~~\n");
//     if (!iter){
//         printf("FAILURE: No iter to destroy");
//         return NULL;
//     }
//     free(iter);
//     iter = NULL;
//     printf("SUCCESS: Iter destroyed\n");
// }

// int list_hasnext(list_iter_t *iter) {
//     if (!iter->node)
//     {
//         return 0;
//     }
//     else {
//         return 1;
//     }
// }

// void *list_next(list_iter_t *iter) {
//     char *tmp = iter->node->item;
//     iter->node = iter->node->next;
//     return tmp;
// }

// void list_resetiter(list_iter_t *iter) {
//     if (!iter->list->head)
//     {
//         printf("FAILURE: List has no head to restart\n");
//         return NULL;
//     }
    
//     iter->node = iter->list->head;
//     printf("SUCCESS: Iter has been reseted\n");
// }


// int main(){
//     printf("yo \n");

//     printf("~~~~ LIST CREATION TEST ~~~~\n");
//     list_t *list = list_create((cmp_fn) strcmp);
//     printf("List length before nodes is: %lu \n", list->length);
//     list_addfirst(list, "dette er første node lagt til head");
//     list_addfirst(list, "dette er andre node lagt til head");
//     printf("List length after two head nodes added is: %lu \n", list->length);

//     printf("\n~~~~ HEADNODES TEST ~~~~\n");
//     printf("Memory adress for head is: %p \n", list->head);
//     printf("Item for head is: %s \n", (char *)list->head->item);
//     printf("Memory adress for node nr.2 is: %p \n", list->head->next);
//     printf("Item for tail is: %s \n", (char *)list->head->next->item);

//     printf("\n~~~~ TAILNODES TEST ~~~~\n");
//     list_addlast(list, "tredje node lagt til listen til tail");
//     printf("Memory adress for tail is: %p \n", list->tail);
//     printf("Item for tail si: %s \n", (char *)list->tail->item);
//     printf("List length after two head nodes and one tail added is: %lu \n", list->length);

//     int test = list_contains(list, list->tail->item);
//     printf("Hvis tallet er 1, virker list_contains: %d\n", test);

//     list_iter_t *iter = list_createiter(list);
//     printf("%p\n", iter);

//     printf("\n ~~~~ TEST AV ITERATOR ~~~~\n");
//     printf("LISTLENGTH: %lu\n", list->length);
//     int testiter = 9;
//     int reset = 0;
//     for (size_t i = 1; i <= list->length; i++)
//     {   
//         if (!list_hasnext(iter) == 0){
//             char *node_str = list_next(iter);
//             printf("Tekst av node nr.%ld: %s\n", i, (char *)node_str);
//             reset++;
//         }
//         if (list_hasnext(iter) == 0){
//             printf("Listen er exhausted, må resetes!\n");
//             list_resetiter(iter);
//             i = 0;
            
//         }
 
//     if (reset == testiter){
//         printf("SUCCESS: Reset test av iter fullført\n");
//         i = 4;
//     }
//     }
    
    

//     list_destroyiter(iter);
    

//     printf("\n~~~~ HEADNODES DELETE TEST ~~~~\n");
//     printf("Head item før sletting: %s \n", (char *)list->head->item);
//     list_popfirst(list);
//     printf("Head tail item etter sletting: %s\n", (char *)list->head->item);
//     printf("List length after two head nodes and one tail added is: %lu \n", list->length);

//     list_poplast(list);

//     printf("\n~~~~ LIST DELETION TEST ~~~~\n");
//     printf("Size of list before destruction: %lu \n", sizeof(list));
//     list_destroy(list, NULL);
//     printf("size of list after destruction: %lu \n", sizeof(list));
//     // printf("Does list exist? Testing head item: %s", (char *)list->head->item);
//     printf("Does list exist?: %p \n", list);
//     printf("Does list tail item exist?: %s \n", (char *)list->tail->item);

    
//     return 0;
// }