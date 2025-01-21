#include <stdio.h>
#include <stdlib.h>

struct node
{ 
    void *item; 
    struct node* left; 
    struct node* right;
};

struct list{
    struct node *root;
    int length; 
};

struct iter_list{
    struct list;
    struct node;
};

struct list *create_list(){
    struct list *r_list = malloc(sizeof(struct list));
    r_list->root = NULL;
    r_list->length = 0;
    return r_list;
}

int list_size(struct list *list){
    return list->length;
}



void insertion(struct list *list, void *item){
    if (list->length == 0){
        struct node *t_node = malloc(sizeof(struct node));
        t_node->item = item;
        list->root = t_node;
    }
    else{

    } 
}

