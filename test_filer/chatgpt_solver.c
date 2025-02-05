#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 9

// Forward declaration
struct Square;

// Element structure (for rows, columns, and boxes)
typedef struct Element {
    struct Square* squares[SIZE];
    int illegal_numbers[SIZE];
    int count;
} Element;

// Square structure
typedef struct Square {
    int number;
    Element *row, *column, *box;
    int legal_numbers[SIZE];
    int legal_count;
    struct Sudokuboard *sudoku;
    int iterator;
} Square;

// Board structure
typedef struct Board {
    int n_rows;
    int n_cols;
    int nums[SIZE][SIZE];
} Board;

// Sudokuboard structure
typedef struct Sudokuboard {
    Board base;
    int solved;
    Square *squares[SIZE * SIZE];
    Element row_list[SIZE], column_list[SIZE], box_list[SIZE];
} Sudokuboard;

void set_up_nums(Sudokuboard *board);
void set_up_elems(Sudokuboard *board);
void solve(Sudokuboard *board);
void checking_legal_nr(Square *square);
void insert_number(Square *square);
void add_illegal_nr(Square *square);
void backtrack(Square *square);
void iterator_reset(Square *square);

void set_up_nums(Sudokuboard *board) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            Square *s = (Square *)malloc(sizeof(Square));
            s->number = board->base.nums[i][j];
            s->sudoku = board;
            board->squares[i * SIZE + j] = s;
        }
    }
}

void set_up_elems(Sudokuboard *board) {
    for (int i = 0; i < SIZE; i++) {
        board->row_list[i].count = 0;
        board->column_list[i].count = 0;
        board->box_list[i].count = 0;
    }
    
    for (int i = 0; i < SIZE * SIZE; i++) {
        Square *s = board->squares[i];
        int row_idx = i / SIZE;
        int col_idx = i % SIZE;
        int box_idx = (col_idx / 3) + (row_idx / 3) * 3;
        
        s->row = &board->row_list[row_idx];
        s->column = &board->column_list[col_idx];
        s->box = &board->box_list[box_idx];
        
        s->row->squares[s->row->count++] = s;
        s->column->squares[s->column->count++] = s;
        s->box->squares[s->box->count++] = s;
    }
}

void solve(Sudokuboard *board) {
    board->solved = 1;
    for (int i = 0; i < SIZE * SIZE; i++) {
        Square *s = board->squares[i];
        if (s->number != 0) continue;
        checking_legal_nr(s);
        if (s->number == 0) {
            board->solved = 0;
            break;
        }
    }
}

void checking_legal_nr(Square *square) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < square->row->count; j++) {
            if (square->row->squares[j]->number == i + 1) square->legal_numbers[i] = 0;
        }
    }
    if (square->legal_count == 0) {
        backtrack(square);
    } else {
        insert_number(square);
    }
}

void insert_number(Square *square) {
    square->number = square->legal_numbers[square->iterator];
    add_illegal_nr(square);
}

void add_illegal_nr(Square *square) {
    square->row->illegal_numbers[square->row->count++] = square->number;
    square->column->illegal_numbers[square->column->count++] = square->number;
    square->box->illegal_numbers[square->box->count++] = square->number;
}

void backtrack(Square *square) {
    for (int i = SIZE * SIZE - 1; i >= 0; i--) {
        Square *s = square->sudoku->squares[i];
        s->number = 0;
        s->iterator = 0;
    }
}

void iterator_reset(Square *square) {
    if (square->iterator >= square->legal_count) {
        square->iterator = 0;
        backtrack(square);
    }
}

void print_board(Sudokuboard *board) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", board->squares[i * SIZE + j]->number);
        }
        printf("\n");
    }
}

int main() {
    int example_board[SIZE][SIZE] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    Sudokuboard board;
    board.base.n_rows = SIZE;
    board.base.n_cols = SIZE;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board.base.nums[i][j] = example_board[i][j];
        }
    }
    
    set_up_nums(&board);
    set_up_elems(&board);
    solve(&board);
    print_board(&board);
    
    return 0;
}
