#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// LINKED LIST STRUCT OG FUNKSJONER
typedef struct node
{ 
    int item; 
    struct node* next; 
} node;

typedef struct list{
    struct node *head;
    struct node *tail;
    int length; 
} l_list;

node *create_node(){
    node *n_node = malloc(sizeof(node));
    n_node->item = 0;
    n_node->next = NULL;
    return n_node;
}

typedef struct iter_list{
    struct list *list;
    struct node *node;
} iter_list;

struct list *create_list(){
    struct list *r_list = malloc(sizeof(struct list));
    r_list->head = NULL;
    r_list->tail = NULL;
    r_list->length = 0;
    return r_list;
}

void remove_from_list(struct list *list, int item){
    if (list->head == NULL){
        printf("List has no head");
        return;
    }
    struct node *tmp = list->head;
    if (item == tmp->item){
        list->head = tmp->next;
        free(tmp);
        list->length--;
        printf("\nRemove completed");
        return;
    }
    for (int i = 0; i <= list->length; i++){
        if (tmp->next != NULL && tmp->next->item == item){
            struct node *rmv = tmp->next;
            tmp->next = tmp->next->next;
            free(rmv);
            list->length--;
            printf("\nRemove completed");
            return;
        }
        else {
            tmp = tmp->next;
        }
    }
}



void append_list(struct list *a_list, int item){
    node *a_node = create_node();
    a_node->item = item;
    if (a_list->length == 0){
        a_list->head = a_node;
        a_list->tail = a_node;
        a_list->length++;
    }
    else {
        a_node->next = a_list->head;
        a_list->head = a_node;
        a_list->length++;
    }
}

int list_size(struct list *list){
    return list->length;
}

// HER BEGYNNER SUDOKU

typedef struct Square {
    struct Board *board;
    struct Element *row;
    struct Element *column;
    struct Element *box;
    struct l_list *forbidden_list; 
    int number;
    int legal_values[9];
    int iterator;
} Square;

typedef struct Element {
    Square *square_lists[9];
    int used_values[9];
    struct l_list *used_list;
} Element;

typedef struct sudoku_board{
    int array[81];
    int length;
    struct Element *rows[9];
    struct Element *columns[9];
    struct Element *boxes[9];
    struct Square *square_list[81]; 
    int used_squares[81];
} Board;

// lager elementer og legger dem til board
void create_elements(Board *board){
    for (size_t i = 0; i < 9; i++)
    {
        Element *row = malloc(sizeof(Element));
        Element *column = malloc(sizeof(Element));
        Element *box = malloc(sizeof(Element));
        memset(row->square_lists, 0, sizeof(row->square_lists));
        memset(column->square_lists, 0, sizeof(column->square_lists));
        memset(box->square_lists, 0, sizeof(box->square_lists));
        board->rows[i] = row;
        board->columns[i] = column;
        board->boxes[i] = box;
        // printf("\nChecking row element:%d", board->rows[i]->item);
    }
}

// Lager alle Squares og legger dem til board
void create_squares(Board *board){
    for (int i = 0; i < board->length; i++)
    {
        Square *s = malloc(sizeof(Square));
        memcpy(s->legal_values, (int[]){1,2,3,4,5,6,7,8,9}, sizeof(s->legal_values));
        board->square_list[i] = s;
    }
}

// Legger alle squares til sitt element
int squares_to_element(Board *board){
    for (int i = 0; i < 81; i++)
    {
        Square *s = board->square_list[i];
        s->row = board->rows[((int)i/9)];
        s->column = board->columns[(i%9)];
        s->box = board->boxes[(int)((i%9)/3)+((int)((i/9)/3)*3)];
        square_to_element_list(s, s->row);
        square_to_element_list(s, s->column);
        square_to_element_list(s, s->box);
    }
    return 0;
}

// Hjelpe funksjon til squares_to_element, legger alle squares i en egen liste for hvert element
void square_to_element_list(Square *s, Element list[]){
    for (int i = 0; i < 9; i++)
        {
            if (list->square_lists[i] == 0){
                list->square_lists[i] = s;
                break;
            }
            else{
                continue;
            }
        }
}

// Legger verdien fra sudokubrettet til hver Square
void value_to_square(Board *board){
    for (int i = 0; i < board->length; i++)
    {
        board->square_list[i]->number = board->array[i];
    }   
}

// Lager en liste for hvert element med brukte tall fra sine squares(illegal numbers)
void creating_used_numbers_2(Element *element_lists[]){
    for (int i = 0; i < 9; i++){
        int count = 0;
        Element *e = element_lists[i];
        memset(e->used_values, 0, sizeof(int)*9);
        for (int j = 0; j < 9; j++)
        {
            if (e->square_lists[j]->number != 0){
                e->used_values[count] = e->square_lists[j]->number;
                count++;
            }
        }        
    }
}

void creating_u_num_3(Element *element_l[]){
    
}

// Lager en liste over gyldige tall
void creating_legal_numbers(Board *board){
    for (int i = 0; i < board->length; i++)
    {
        Square *s = board->square_list[i];
        making_illegal_list(s->row, s);
        making_illegal_list(s->column, s);
        making_illegal_list(s->box, s);
    } 
}

// Hjelpe funksjon for creating legal numbers
void making_illegal_list(Element *used_list, Square *s){
    for (int i = 0; i < 9; i++)
    {
        if (used_list->used_values[i] == 0){
            break;
        }
        else{
            for (int j = 0; j < 9; j++)
            {
                if (used_list->used_values[i] == s->legal_values[j]){
                    s->legal_values[j] = 0;
                    break;
                }
                else{
                    continue;
                }
            }
            
        }
    }
}


// Free alle strukturer
void free_structs(Board *myboard){
    for (int i = 0; i < 9; i++) {
        free(myboard->rows[i]);
        free(myboard->columns[i]);
        free(myboard->boxes[i]);
    }
    for (int i = 0; i < 81; i++) {
        free(myboard->square_list[i]);
    }
    free(myboard); 
}


void solve(Board *Board){

}

int main(){
    // Lager myboard
    Board *myboard = malloc(sizeof(Board));
    myboard->length = 81;
    int sudoku_board[] = {0,0,4,3,0,0,2,0,9,0,0,5,0,0,9,0,0,1,0,7,0,0,6,0,0,4,3,0,0,6,0,0,2,0,8,7,1,9,0,0,0,7,4,0,0,0,5,0,0,8,3,0,0,0,6,0,0,0,0,0,1,0,5,0,0,3,5,0,8,6,9,0,0,4,2,9,1,0,3,0,0
    };
    memcpy(myboard->array, sudoku_board, (81 * sizeof(int)));
    for (int i = 0; i < 81; i++)
    {
        // printf("\nmyboard er: %d, og sudokuboard er: %d", myboard->array[i], sudoku_board[i]);
    }
    
    // Test for element og node, funker
    struct Element *row = malloc(sizeof(Element));
    Square *node = malloc(sizeof(Square));
    node->row = row;

    // Lager elementer til myboard
    create_elements(myboard);

    // Må legge 81 squares til en array til sudokuboard
    create_squares(myboard);

    // Må legge squares inn i sine elementer
    squares_to_element(myboard);

    // Ordne tall til Square
    value_to_square(myboard);

    // Legge til brukte tall i element liste
    creating_used_numbers_2(myboard->rows);
    creating_used_numbers_2(myboard->columns);
    creating_used_numbers_2(myboard->boxes);

    // Må lage funskjon for at hver square har sin egen liste over lovlige tall
    creating_legal_numbers(myboard);

    // FUnksjon solve 
    solve(myboard);

    // Funksjon for å free plass
    free_structs(myboard);

    printf("No segmentation fault - Complete success\n");


    struct list *test_list = create_list();
    for (int i = 0; i < 5; i++){
        append_list(test_list, i);
        } 
    printf("\nList length: %d", list_size(test_list));
    remove_from_list(test_list, 3);
    printf("\nList length: %d", list_size(test_list));
    struct node *tmp = test_list->head;
    for (int i = 0; i < test_list->length; i++){
        printf("\n%d", tmp->item);
        tmp = tmp->next;
        } 
    free(tmp);


    return 0;
}


