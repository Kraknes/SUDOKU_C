#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    for (size_t i = 0; i < 81; i++)
    {
        printf("\n%ld", (int)((i%9)/3)+((int)((i/9)/3)*3));
    }
}