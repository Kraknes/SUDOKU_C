#include <stdio.h>
#include <stdlib.h>
// test

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


int main(){
    int a = 5;
    int b = 6;
    int * c = &a;
    int * ptr;
    ptr = &b; 



    printf("\n%d verdi av node->a", a);
    printf("\n%d verdi av node->b", b);
    printf("\n%p verdi av pointer c til a", c);
    printf("\n%p verdi av pointer node->a", &a );
    printf("\n%p verdi av pointer ptr til b", ptr);
    printf("\n%p verdi av pointer node->b", &b);
    printf("\n%d verdi av verdien til *ptr som pointer til b", *ptr);

    *ptr += 10;
    printf("\n%d verdien til *ptr som er lagt til 10 som er lagt til b", *ptr);

    int * ptr_2;
    ptr_2 = &b;

    printf("\n%d verdien til ptr_2 som pointer til b (et resultat av at *ptr ble endret på fra sist linje)", *ptr_2);
    


    struct node * test = create_node();
    printf("\n%d er verdien til node->a",test->a);
    
    node_test hey;
    hey.a = 6;
    hey.b = 11;

    printf("\n%d verdien til typedef node struct hey.a", hey.a);
    printf( "\n%i verdien til typedef node struct hey.b", hey.b);




    printf("\n");
    return 0;

}