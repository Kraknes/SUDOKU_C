#include <stdio.h>

void main(){
    int a = 5;
    int b = 6;
    int * c = &a;
    int * ptr;
    ptr = &b; 

    printf("\n%d", a);
    printf("\n%d", b);
    printf("\n%p", c);
    printf("\n%p", &a);
    printf("\n%p", ptr);
    printf("\n%p", &b);
    printf("\n%d", *ptr);

    *ptr += 10;
    printf("\n%d", *ptr);
    printf("\n");

    // int* c = (int* 10);
    // printf("\n%d", a);

}