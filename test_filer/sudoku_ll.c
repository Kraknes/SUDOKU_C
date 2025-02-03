#include <stdio.h>
#include <stdlib.h>

typedef struct node
{ 
    int item; 
    struct node* next; 
} node;

struct list{
    struct node *head;
    struct node *tail;
    int length; 
};

struct iter_list{
    struct list *list;
    struct node *node;
};

struct list *create_list(){
    struct list *r_list = malloc(sizeof(struct list));
    r_list->head = NULL;
    r_list->tail = NULL;
    r_list->length = 0;
    return r_list;
}

void remove_from_list(struct list *list, int item){
    if (list->head == NULL){
        printf("List has no head");
        return;
    }
    struct node *tmp = list->head;
    if (item == tmp->item){
        list->head = tmp->next;
        free(tmp);
        list->length--;
        printf("\nRemove completed");
        return;
    }
    for (int i = 0; i <= list->length; i++){
        if (tmp->next != NULL && tmp->next->item == item){
            struct node *rmv = tmp->next;
            tmp->next = tmp->next->next;
            free(rmv);
            list->length--;
            printf("\nRemove completed");
            return;
        }
        else {
            tmp = tmp->next;
        }
    }
    
}

node *create_node(){
    node *n_node = malloc(sizeof(node));
    n_node->item = 0;
    n_node->next = NULL;
    return n_node;
}


void append_list(struct list *a_list, int item){
    node *a_node = create_node();
    a_node->item = item;
    if (a_list->length == 0){
        a_list->head = a_node;
        a_list->tail = a_node;
        a_list->length++;
    }
    else {
        a_node->next = a_list->head;
        a_list->head = a_node;
        a_list->length++;
    }
}

int list_size(struct list *list){
    return list->length;
}


int main(){
    struct list *test_list = create_list();
    for (int i = 0; i < 5; i++){
        append_list(test_list, i);
        } 
    printf("\nList length: %d", list_size(test_list));
    remove_from_list(test_list, 3);
    printf("\nList length: %d", list_size(test_list));
    struct node *tmp = test_list->head;
    for (int i = 0; i < test_list->length; i++){
        printf("\n%d", tmp->item);
        tmp = tmp->next;
        } 
    free(tmp);
    return 0;
}