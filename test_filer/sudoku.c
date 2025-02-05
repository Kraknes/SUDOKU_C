#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// LINKED LIST STRUCT OG FUNKSJONER
typedef struct node
{ 
    int item; 
    struct node* next; 
} l_node;

typedef struct list{
    struct node *head;
    struct node *tail;
    int length; 
} l_list;

l_node *create_node(){
    l_node *n_node = malloc(sizeof(l_node));
    n_node->item = 0;
    n_node->next = NULL;
    return n_node;
}

typedef struct iter_list{
    struct list *list;
    struct node *node;
} iter_list;

l_list *create_list(){
    l_list *r_list = malloc(sizeof(l_list));
    r_list->head = NULL;
    r_list->tail = NULL;
    r_list->length = 0;
    return r_list;
}


void remove_node(l_list *list, int item){
    if (list->head == NULL){
        printf("List has no head");
        return;
    }
    struct node *tmp = list->head;
    if (tmp == NULL){
        printf("\n List exhausted - Returns");
        return;
    }
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
            if (tmp->next != NULL){
                tmp = tmp->next;
            }
            else{
                return;
            }
            
        }
    }
}

// Fjernen en node fra en lenket liste GENERELL
void remove_from_list(l_list *list, l_node *node){
    if (node == NULL){
        return;
    }
    else{
        remove_node(list, node->item);
    }
}
// Legger til en ulovlige tall (item) til en element sin lenket liste 
void append_list(l_list *a_list, int item){
    l_node *a_node = create_node(); // ~~~~~~~~~~~~~~~~~~NOE RART SKJER HER, DEN ENDRER TALL PÅ ALLEREDE EKSISTERENDE NODER
    a_node->item = item;
    // Hvis listen er tom, legger noden til som head og tail
    if (a_list->length == 0){
        a_list->head = a_node;
        a_list->tail = a_node;
        a_list->length++;
    }
    // en iterator for å finne om item er der i listen allerede
    else {
        l_node *tmp = a_list->head;
        for (int i = 0; i < 9; i++)
        {
            // Hvis temp har ingen node
            if (tmp == NULL){
                break;
            }
            // hvis Item eksistere i listen fra før vil den ikke legge til listen(Skal bare være en tilfelle per tall)
            else if (tmp->item == a_node->item)
            {
                free(tmp);
                return;
            }
            else{
                tmp = tmp->next;
            }
        } 
        // Hvis det er et nytt tall skjer dette
        free(tmp);
        a_node->next = a_list->head;
        a_list->head = a_node;
        a_list->length++;
        }
}


int list_size(l_list *list){
    return list->length;
}

// HER BEGYNNER SUDOKU

typedef struct Square {
    struct sudoku_board *board;
    struct Element *row;
    struct Element *column;
    struct Element *box;
    struct list *legal_list; 
    int number;
    struct Square *next;
} Square;

typedef struct Element {
    Square *square_lists[9];
    int used_values[9];
    l_list *used_list;
} Element;

typedef struct sudoku_board{
    int array[81];
    int length;
    struct Element *rows[9];
    struct Element *columns[9];
    struct Element *boxes[9];
    struct Square *square_list[81]; 
    struct s_list *used_squares;
    int solved;
} Board;

// EGEN SQUARE LINKED LIST

typedef struct s_list{
    struct Square *head;
    struct Square *tail;
    int length; 
} s_list;

s_list *create_s_list(){
    s_list *r_list = malloc(sizeof(s_list));
    r_list->head = NULL;
    r_list->tail = NULL;
    r_list->length = 0;
    return r_list;
}

void append_s_list(s_list *a_list, struct Square *s){
    if (a_list->length == 0){
        a_list->head = s;
        a_list->tail = s;
        a_list->length++;
    }
    else {
        s->next = a_list->head;
        a_list->head = s;
        a_list->length++;
    }
}

void free_s_list(s_list *list){
    for (int i = 0; i < 81; i++)
    {
        struct Square *s = list->head;
        if (s == NULL){
            break;
        }
        else{
            list->head = s->next;
        }
    }
}

// FUNKSJONER FOR SUDOKU

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

// En del av create_Square, lager en lenket liste av 1-9 lovlige tall (skal bli brukt som grunnlag for legal numbers)
void creating_legal_l_list(Square *s){
    s->legal_list = create_list();
    for (int i = 0; i < 9; i++)
    {
        append_list(s->legal_list, i+1);
    }
}

// Lager alle 81 Squares og legger dem til i en liste til Board struktur
void create_squares(Board *board){
    for (int i = 0; i < board->length; i++)
    {
        Square *s = malloc(sizeof(Square));
        s->board = board;
        creating_legal_l_list(s);
        board->square_list[i] = s;
    }
}

// Hjelpe funksjon til squares_to_element, legger alle squares i en egen liste for hvert element
void square_to_el_list(Square *s, Element list[]){
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

// Legger alle squares til sitt element og referanse til elementene i square
int squares_to_element(Board *board){
    for (int i = 0; i < 81; i++)
    {
        Square *s = board->square_list[i];
        s->row = board->rows[((int)i/9)];
        s->column = board->columns[(i%9)];
        s->box = board->boxes[(int)((i%9)/3)+((int)((i/9)/3)*3)];
        square_to_el_list(s, s->row);
        square_to_el_list(s, s->column);
        square_to_el_list(s, s->box);
    }
    return 0;
}

// Legger verdien fra sudokubrettet til hver Square
void value_to_square(Board *board){
    for (int i = 0; i < board->length; i++)
    {
        board->square_list[i]->number = board->array[i];
    }   
}

// I bruk til solver funksjonen. Oppdaterer element used numbers liste etter en annen square har valgt sitt tall.
void creating_used_numbers_solve(Element *element){
    for (int j = 0; j < 9; j++)
        {
            if (element->square_lists[j]->number != 0){
                append_list(element->used_list, element->square_lists[j]->number);
            }
        }        
}

// Lager en liste for hvert element med brukte tall fra sine squares(illegal numbers)
void creating_used_numbers(Element *element_l[]){
    for (int i = 0; i < 9; i++){
        Element *e = element_l[i];
        l_list *l = create_list();
        e->used_list = l;
        for (int j = 0; j < 9; j++)
        {
            if (e->square_lists[j]->number != 0){
                append_list(l, e->square_lists[j]->number);
                continue;
            }
        }        
    }
}

// En del av creating legal numbers, ignorer denne i solver()
void making_illegal_l_list(Element *el, Square *s){
    if (s->number != 0){
        return;
    }
    l_node *node = el->used_list->head;
    for (int i = 0; i < 9; i++)
    {   
        if (node == NULL)
        {
            break;
        }
        else{
            remove_from_list(s->legal_list, node);
            node = node->next;
        }
    }
}

// Lager en lenket liste med gyldige tall for Square med å bruke elementene sine
void creating_legal_numbers(Square *s){
        making_illegal_l_list(s->row, s);
        making_illegal_l_list(s->column, s);
        making_illegal_l_list(s->box, s);
}

// En del av solver funksjonen for å inserte nummer
void insert_number(Square *s){
    // Lager en liste over lovlige tall å bruke
    creating_legal_numbers(s);
    if (s->legal_list->head == NULL){
        // backtrack();
    }
    else {
        // Legger til sitt tall (Square) fra første i lenket liste (Head) over lovlige tall i Squaren, deretter fjernes tallet fra den lovlige tall listen til Squaren
        s->number = s->legal_list->head->item;
        remove_from_list(s->legal_list, s->legal_list->head);
        append_s_list(s->board->used_squares, s);
        creating_used_numbers_solve(s->row);
        creating_used_numbers_solve(s->column);
        creating_used_numbers_solve(s->box);
    }
}

// Solver funskjonen
void solve(Board *myboard){
    myboard->solved = 1;
    for (int i = 0; i < myboard->length; i++)
    {
        Square *s =myboard->square_list[i];
        if (s->number != 0){
            continue;
        }
        else{
            insert_number(s);
            myboard->array[i] = s->number;
            print_board(myboard);
            if (s->number == 0)
            {
                myboard->solved = 0;
                break;
            }
            else{
                continue;
            }
        }
    }
}

// Free alle strukturer OBS Funker ikke helt enda
void free_structs(Board *myboard){
    for (int i = 0; i < 9; i++) {
        free(myboard->rows[i]);
        free(myboard->columns[i]);
        free(myboard->boxes[i]);
    }
    for (int i = 0; i < 81; i++) {
        Square *s = myboard->square_list[i];
        for (int j= 0; j < 9; j++)
        {
            l_node *tmp = s->legal_list->head->next;
            free(s->legal_list->head);
            s->legal_list->head = tmp;
        }
        
        free(s);
    }
    free(myboard); 
}

// Printer bordet
int print_board(Board *myboard){
    int count = -1;
    printf("\n[ ");
    for (int i = 0; i < myboard->length; i++)
    {
        if (count%9 == 8){
            printf("]\n[ ");
        }
        printf("%d, ", myboard->array[i]);
        count++;
    }
    printf("]\n");
    return 0;
}

int main(){
    // Lager myboard
    Board *myboard = malloc(sizeof(Board));
    myboard->length = 81;
    myboard->solved = 0;
    myboard->used_squares = create_s_list();
    int sudoku_board[] = {0,0,4,3,0,0,2,0,9,0,0,5,0,0,9,0,0,1,0,7,0,0,6,0,0,4,3,0,0,6,0,0,2,0,8,7,1,9,0,0,0,7,4,0,0,0,5,0,0,8,3,0,0,0,6,0,0,0,0,0,1,0,5,0,0,3,5,0,8,6,9,0,0,4,2,9,1,0,3,0,0
    };
    memcpy(myboard->array, sudoku_board, (81 * sizeof(int)));


    // Lager elementer til myboard
    create_elements(myboard);

    // Må legge 81 squares til en array til sudokuboard
    create_squares(myboard);

    // Må legge squares inn i sine elementer
    squares_to_element(myboard);

    // Ordne tall til Square
    value_to_square(myboard);

    // Legge til brukte tall i element liste
    creating_used_numbers(myboard->rows);
    creating_used_numbers(myboard->columns);
    creating_used_numbers(myboard->boxes);

    // Må lage funskjon for at hver square har sin egen liste over lovlige tall
    for (int i = 0; i < myboard->length; i++){
        Square *s = myboard->square_list[i];
        creating_legal_numbers(s);
    }

    // FUnksjon solve 
    while (myboard->solved == 0){
        solve(myboard);
    }

    printf("\nNo segmentation fault - Complete success");
    
    print_board(myboard);

    
    return 0;
}


