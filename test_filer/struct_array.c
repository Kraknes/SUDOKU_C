#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sudoku_board{
    int array[81];
    int length;
} Board;


int main(){
    Board myboard;
    myboard.array[0] = 1;

    Board *myboard_pt = malloc(sizeof(Board));
    myboard_pt->array[0] = 1;

    int sudoku_board[] = {0,0,4,3,0,0,2,0,9,0,0,5,0,0,9,0,0,1,0,7,0,0,6,0,0,4,3,0,0,6,0,0,2,0,8,7,1,9,0,0,0,7,4,0,0,0,5,0,0,8,3,0,0,0,6,0,0,0,0,0,1,0,5,0,0,3,5,0,8,6,9,0,0,4,2,9,1,0,3,0,0
    };

    memcpy(myboard_pt->array, sudoku_board, (81 * sizeof(int)));
    for (size_t i = 0; i < 81; i++)
    {
        printf("\nmyboard er: %d, og sudokuboard er: %d", myboard_pt->array[i], sudoku_board[i]);
    }

    
    

}