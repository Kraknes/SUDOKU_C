#include <stdio.h>
#include <stdlib.h>

struct node
{ 
    int *item; 
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

struct list *append_list(node){
    
}

int list_size(struct list *list){
    return list->length;
}

struct node *create_node(){
    struct node *n_node = malloc(sizeof(struct node));
    n_node->item = 0;
    n_node->left = NULL;
    n_node->right = NULL;
}

struct node recursive_node(struct node *node){
    struct node *rec_node = node;
    if (rec_node->left != NULL){
        rec_node = rec_node->left;
        recursive_node(rec_node);
    } 
    else{
        return *rec_node;
    }
}



// void delete_node(struct list *list, int *item){
//     struct node *tmp = list->root;
//     if (item == tmp->item){
//         if ((tmp->left != NULL) && (tmp->right != NULL))
//             {
//                 tmp = tmp->right;
//                 *tmp = recursive_node(tmp);
                

//             }
//         else if ((tmp->left != NULL) || (tmp->right != NULL))
//             {
//                 int a = 5;
//                 // Noe her om at en node går opp 
//             }        
//         else ((tmp->left = NULL) && (tmp->right = NULL))
//             {
//                 printf("\nList is now empty");
//                 free(tmp);
//             }                    
//     }

// }


void insertion(struct list *list, void *item){
    if (list->length == 0){
        struct node *t_node = malloc(sizeof(struct node));
        t_node->item = item;
        list->root = t_node;
    }
    else{

    } 
}

void main(){
    struct list *test_list = create_list();
    for (int i = 0; i < 5; i++)
        {struct node *test_node = create_node();
        test_node->item = i;

        }

    
}