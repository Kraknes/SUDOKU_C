/**
 * @authors
 * Steffen Viken Valvaag
 * Odin Bjerke <odin.bjerke@uit.no>
 */

#include "list.h"
#include "printing.h"

#include <stdlib.h>


/* For debug, skriv gdb --arg bin/debug/wordfreq data/oxford_dict.txt 1 1 20
*/

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
    cmp_fn cmpfn;
};

struct list_iter {
    list_t *list;
    lnode_t *node;
};



list_t *list_create(cmp_fn cmpfn) {
    list_t *list = malloc(sizeof(list_t));
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    list->cmpfn = cmpfn;
    printf("Test");
    return list;
}

void list_destroy(list_t *list, free_fn item_free) {
    free(list);
    free(item_free);
}

size_t list_length(list_t *list) {
    if (list->length == 0) {
        return 0;
    }
    return list->length;

}

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

int list_addlast(list_t *list, void *item) {
    lnode_t *last_node = malloc(sizeof(lnode_t));
    if (last_node == NULL)
    {
        printf("\nERROR: Failed to allocate memory to new node to tail");
        return -1;
    }
    if (list->length == 0){
        list->tail = last_node;
        list->head = last_node;
    }
    else {
    list->tail->next = last_node;
    last_node->item = item;
    last_node->prev = list->tail;
    list->tail = last_node;
    list->length++;
    }
    return 0;
}

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
    tmp_node = NULL;
    list->length--;
    return tmp_item;
} 

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

int list_contains(list_t *list, void *item) {
    if (list == NULL) {
        printf("\nERROR: List does not exist");
        return 0;
    }
    lnode_t *node_cmp = list->head;
    for (size_t i=1; i <= list->length; i++)
    {
        if (list->cmpfn(item, node_cmp->item) == 0)
        {
            return 1;
        }
        else {
            node_cmp = node_cmp->next;
        }
        
    }
    printf("FAILURE: Ingen likheter funnet");
    return 0;
}


/* ---- list iterator ---- */

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

void list_destroyiter(list_iter_t *iter) {
    if (iter == NULL){
        printf("\nERROR: No iter to destroy");
    }
    free(iter);
    iter = NULL;
}

int list_hasnext(list_iter_t *iter) {
    if (iter->node  == NULL)
    {
        return 0;
    }
    else {
        return 1;
    }
}

void *list_next(list_iter_t *iter) {
    char *tmp = iter->node->item;
    iter->node = iter->node->next;
    return tmp;
}

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
static lnode_t *merge(lnode_t *a, lnode_t *b, cmp_fn cmpfn) {
    lnode_t *head, *tail;

    /* Pick the smallest head node */
    if (cmpfn(a->item, b->item) < 0) {
        head = tail = a;
        a = a->next;
    } else {
        head = tail = b;
        b = b->next;
    }

    /* Now repeatedly pick the smallest head node */
    while (a && b) {
        if (cmpfn(a->item, b->item) < 0) {
            tail->next = a;
            tail = a;
            a = a->next;
        } else {
            tail->next = b;
            tail = b;
            b = b->next;
        }
    }

    /* Append the remaining non-empty list (if any) */
    if (a) {
        tail->next = a;
    } else {
        tail->next = b;
    }

    return head;
}

/**
 * Splits the given list in two halves, and returns the head of
 * the second half.
 */
static lnode_t *splitlist(lnode_t *head) {
    /* Move two pointers, a 'slow' one and a 'fast' one which moves
     * twice as fast.  When the fast one reaches the end of the list,
     * the slow one will be at the middle.
     */
    lnode_t *slow = head;
    lnode_t *fast = head->next;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    /* Now 'cut' the list and return the second half */
    lnode_t *half = slow->next;
    slow->next = NULL;

    return half;
}

/**
 * Recursive merge sort.  This function is named mergesort_ to avoid
 * collision with the mergesort function that is defined by the standard
 * library on some platforms.
 */
static lnode_t *mergesort_(lnode_t *head, cmp_fn cmpfn) {
    if (head->next == NULL) {
        return head;
    }


    lnode_t *half = splitlist(head);
    head = mergesort_(head, cmpfn);
    half = mergesort_(half, cmpfn);

    return merge(head, half, cmpfn);
}

void list_sort(list_t *list) {
    /* Recursively sort the list */
    list->head = mergesort_(list->head, list->cmpfn);

    /* Fix the tail and prev links */
    lnode_t *prev = NULL;
    for (lnode_t *n = list->head; n != NULL; n = n->next) {
        n->prev = prev;
        prev = n;
    }
    list->tail = prev;
}
