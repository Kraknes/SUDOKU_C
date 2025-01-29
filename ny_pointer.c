struct node{
    int a;
    int b;
};

struct node *create_node(){
    struct node *hey = malloc(sizeof(struct node));
    hey->a = 5;
    hey->b = 10;
    return hey;
}



typedef struct Noder{
    int a;
    int b;
} node_test;

// Funkjson som ikke returnere pointer
// Fordeler: enkel programmering, ingen pointers, ingen malloc, 
// Ulemper: kopiere ut noden istedenfor en pointer til en spesifikk node. 
// PS: Skjønner ikke helt hva det betyr
node_test create_Node(){
    node_test node;
    node.a = 11;
    node.b = 12;
    return node;
}

// FUnskjon som returnere pointer
// Fordeler: 
// Ulemper: Det er pointers. Æsj.
node_test create_Node(){
    node_test *node;
    node->a = 11;
    node->b = 12;
    return *node;
}