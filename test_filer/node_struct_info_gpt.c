#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a large struct with more data
typedef struct LargeNode {
    int id;
    double values[1000];  // Large array inside the struct
    char name[50];
} LargeNode;

// Er lik den ovenfor, eneste forskjell er at man må skrive struct Largenode hver eneste gang den brukes.
struct Largenode{
    int id;
    double values[1000];  // Large array inside the struct
    char name[50];
};

// Function that returns a struct by value (inefficient for large structs)
LargeNode create_LargeNode() {
    LargeNode node;
    node.id = 1;
    strcpy(node.name, "Large Struct");
    
    // Fill values array
    for (int i = 0; i < 1000; i++) {
        node.values[i] = i * 1.1;
    }
    
    return node;  // ⚠ Inefficient copy of entire struct
}

// Function that returns a pointer to a dynamically allocated struct
LargeNode *create_pLargeNode() {
    LargeNode *node = malloc(sizeof(LargeNode));
    if (node == NULL) {
        return NULL;  // Memory allocation failed
    }

    node->id = 2;
    strcpy(node->name, "Pointer Large Struct");

    // Fill values array
    for (int i = 0; i < 1000; i++) {
        node->values[i] = i * 2.2;
    }

    return node;  // ✅ Returns a pointer, avoiding unnecessary copying
}

int main() {
    // Method 1: Using function that returns a struct (copying large data)
    LargeNode node1 = create_LargeNode();
    printf("Node 1: ID = %d, Name = %s, Value[0] = %.2f\n", node1.id, node1.name, node1.values[20]);

    // Method 2: Using function that returns a pointer (more efficient)
    LargeNode *node2 = create_pLargeNode();
    struct LargeNode node3;
    node3.id = 3;
    printf("%li\n", sizeof(node1));
    printf("%li\n", sizeof(node1.id));
    printf("%li\n", sizeof(node1.values));
    printf("%li\n", sizeof(node1.name));
    printf("%li\n", sizeof(node2));
    printf("%li\n", sizeof(*node2));
    printf("%li\n", sizeof(node3));
    printf("%d\n", sizeof(node3.id));
    if (node2 != NULL) {
        printf("Node 2: ID = %d, Name = %s, Value[0] = %.2f\n", node2->id, node2->name, node2->values[20]);
        free(node2);  // ✅ Free allocated memory to prevent leaks
    }

    return 0;
}
