#include <stdio.h>
#include <stdlib.h>

// struct node{
//     int a;
//     int b;
// };

// struct node *create_node(){
//     struct node *hey = malloc(sizeof(struct node));
//     hey->a = 5;
//     hey->b = 10;
//     return hey;
// }

typedef struct Noder{
    int a;
    int b;
} node_test;


/*
Funksjon som lager node uten pointers 
Fordeler: 
* Simple to use – No need for pointers, malloc, or free().
* Automatic memory management – Memory is allocated on the stack, and automatically freed when the function ends.
* Safe from memory leaks – Since no malloc is used, you don’t have to worry about free(). 
Ulemper: 
* Lages bare i funksjonen. Må kopiere noden for å returnere. Bruker ekstra tid og memory. Men funker for små struct.
* Copies the struct – Every time you return the struct, it creates a copy, which can be inefficient if the struct is large.
* Lifetime is limited to scope – If you need the struct to persist beyond a function call, you must manually copy it elsewhere.
*/
node_test create_Node(){
    node_test node;
    node.a = 11;
    node.b = 12;
    return node;
}

/* 
Funksjon som lager node med pointers
Fordeler:
* Avoids copying – Since it returns a pointer, no extra copy is created. This is useful for large structs.
* Persists beyond function scope – Memory is allocated on the heap, so the struct exists even after the function returns.
* Can be shared – Since it returns a pointer, multiple functions can modify the same memory.
Ulemper:
* Requires manual memory management – You must call free(pnode) to avoid memory leaks.
* More complex – You need to handle pointer-related issues, like NULL checks and free().
* Potential memory leaks – If you forget to free(), your program can consume excess memory over time. 
*/
node_test *create_pNode(){
    node_test *node = malloc(sizeof(node_test));
    if (node == NULL){
        return NULL;
    }
    node->a = 11;
    node->b = 12;
    return node;
}

int main(){
    // Dannelse av vanlig node uten pekere
    node_test node = create_Node();
    printf("Node values: a = %d, b = %d\n", node.a, node.b);
    node.a = 100;
    node.b = 200;
    printf("Node values: a = %d, b = %d\n", node.a, node.b);
    
    // Dannelse av node med pekere
    node_test *pnode = create_pNode();
    printf("Pointer Node values: a = %d, b = %d\n", pnode->a, pnode->b);
    pnode->a = 500;
    pnode->b = 1000;
    printf("Pointer Node values: a = %d, b = %d\n", pnode->a, pnode->b);
    free(pnode);  // ✅ Free memory when done

}