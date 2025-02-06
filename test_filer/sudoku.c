#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SUDOKU_BOARD (int[]){0,0,4,3,0,0,2,0,9,0,0,5,0,0,9,0,0,1,0,7,0,0,6,0,0,4,3,0,0,6,0,0,2,0,8,7,1,9,0,0,0,7,4,0,0,0,5,0,0,8,3,0,0,0,6,0,0,0,0,0,1,0,5,0,0,3,5,0,8,6,9,0,0,4,2,9,1,0,3,0,0}

// LINKED LIST STRUCT OG FUNKSJONER
typedef struct node
{ 
    int item; 
    int been_used;
    struct node* next; 
} l_node;

typedef struct list{
    l_node *head;
    l_node *tail;
    int length; 
    
} l_list;

l_node *create_node(){
    l_node *n_node = malloc(sizeof(l_node));
    n_node->item = 0;
    n_node->next = NULL;
    n_node->been_used = 0;
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
        return;
    }
    struct node *tmp = list->head;
    if (tmp == NULL){
        return;
    }
    // Hivs item(nummer) er første instans i linkedlist (list->head), så fjernes den der. 
    if (item == tmp->item){
        list->head = tmp->next;
        free(tmp);
        list->length--;
        if (list->length == 1){
            list->tail = list->head;
        }
        return;
    }
    // Hvis ikke i head, så iteres den gjennom hele listen til den finner item(nummeret)
    for (int i = 0; i <= list->length; i++){
        if (tmp->next != NULL && tmp->next->item == item){
            struct node *rmv = tmp->next;
            tmp->next = tmp->next->next;
            if (tmp->next != NULL && tmp->next->item == list->tail->item){
                list->tail = tmp->next;
            }
            free(rmv);
            list->length--;
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
    l_node *a_node = create_node(); 
    a_node->next = NULL;
    a_node->been_used = 0;
    a_node->item = item;
    // Hvis listen er tom, legger noden til som head og tail
    if (a_list->length == 0){
        a_list->head = a_node;
        a_list->tail = a_node;
        a_list->length++;
    }
    // En iterator for å unngå dobbelt av samme verdi i listen - OBS bør kanskje ikke være her?
    else {
        l_node *tmp = a_list->head;
        for (int i = 0; i < a_list->length; i++)
        {
            // Hvis temp har ingen node
            if (tmp == NULL){
                break;
            }
            // hvis Item eksistere i listen fra før vil den ikke legge til listen(Skal bare være en tilfelle per tall)
            else if (tmp->item == a_node->item)
            {
                return;
            }
            else{
                tmp = tmp->next;
            }
        } 
        // Hvis det er et nytt tall skjer dette
        a_node->next = a_list->head;
        a_list->head = a_node;
        a_list->length++;
        }
}

void node_add_tail(l_list *list, l_node *node){
    if (list->tail == NULL){
        list->head = node;
        list->tail = node;
        list->length++;
    }
    else{
        list->tail->next = node;
        list->tail = node;
        list->length++;
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

void list_append_tail(s_list *list, struct Square *s){
    list->tail->next = s;
    list->tail = s;
}

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
    }
}

// En del av create_Square, lager en lenket liste av 1-9 lovlige tall (skal bli brukt som grunnlag for legal numbers)// Blir brukt til backtrack() også. 
void creating_legal_l_list(Square *s){
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
        s->next = NULL;
        s->legal_list = create_list();
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
            }
        }        
    }
}

// En del av creating legal numbers. Bruker Elementene til en Square for å fjerne tall som ikke kan brukes
void making_illegal_l_list(Element *el, Square *s){
    if (s->legal_list->head == NULL){
        return;
    }
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

// legger tilbake den gamle tallet i listen sin på tail, slik at head node blir neste tall i listen
void oldnum_back_in_list(Square *s){
    l_node *old_num = create_node();
    old_num->item = s->number;
    remove_node(s->legal_list, s->number);
    node_add_tail(s->legal_list, old_num);
}

// Iterator funksjon som i python, går bare gjennom alle tallene i legal list og endrer rekkefølgen om de hra blitt brukt tidligere eller ikke
 void next_in_legal_list(Square *s){
    if (s->legal_list->length == 1 || s->legal_list->length == 0) // enten en backtracked square eller en som kan ikke endre på rekkefølge av legal_list
    {
        next_in_legal_list(s->next);
    }
    else
    {   
        l_node *h = s->legal_list->head;
        for (int i = 0; i < s->legal_list->length; i++)
        {
            if (h == NULL){
                next_in_legal_list(s->next);
            }
            else if (h->been_used == 1){
                h = h->next;
            }
            else
            {
                oldnum_back_in_list(s);
                return;
            }
        }
    }
 }

void backtrack(Square *s){
    // legger til square i used_squares listen for board
    append_s_list(s->board->used_squares, s);
    // itererer gjennom alle tidligere squares og endrer rekkefølge i sin legal_list
    Square *used_s = s->board->used_squares->head;
    for (int i = 0; i < s->board->used_squares->length; i++)
    {
        if (used_s->legal_list->head == NULL){
            // oldnum_back_in_list(used_s); // Setter tilbake sitt tall i listen over lovlige tall;
            next_in_legal_list(used_s); // endrer rekkefølgen på andre sine lovlige liste for å kunne finne en løsning som passer
            creating_legal_l_list(used_s);
            used_s = used_s ->next;
        }
        else{
            remove_node(used_s->row->used_list, used_s->number);
            remove_node(used_s->column->used_list, used_s->number);
            remove_node(used_s->box->used_list, used_s->number);
            used_s->number = 0;
            creating_legal_l_list(used_s);
            used_s = used_s ->next;
        }
    }
    // Fjerner alle nodene i used_square list til Board
}

// En del av solver funksjonen for å inserte nummer
void insert_number(Square *s){
    // Lager en liste over lovlige tall å bruke
    creating_legal_numbers(s);
    if (s->legal_list->head == NULL){
        backtrack(s);
    }
    else {
        // Legger til sitt tall (Square) fra første i lenket liste (Head) over lovlige tall i Squaren, deretter fjernes tallet fra den lovlige tall listen til Squaren
        s->number = s->legal_list->head->item;
        s->legal_list->head->been_used = 1;
        // Legger til squaren i en liste over brukte Squares i Board.
        append_s_list(s->board->used_squares, s);
        // Oppdatere alle elementene sine lister over ulovlige tall, siden en Square har lagt et nummer på brettet som nå ikke er lovlig lengre
        creating_used_numbers_solve(s->row);
        creating_used_numbers_solve(s->column);
        creating_used_numbers_solve(s->box);
    }
}

// Solver funskjonen
void solve(Board *myboard){
    // Hvis my->board forblir 1, så er brettet ferdig løst
    myboard->solved = 1;

    // Her vil alle squares bli gått igjennom og få sitt tall på brettet
    for (int i = 0; i < myboard->length; i++)
    {
        Square *s =myboard->square_list[i];
        if (s->number != 0){
            continue;
        }
        else{
            insert_number(s);
            myboard->array[i] = s->number;
            // Hvis brettet er tomt, så må man starte på nytt
            if (s->number == 0)
            {
                myboard->solved = 0;
                // restarter brettet i array og fjerner alle used_squares i listen
                for (int j = 0; j < myboard->used_squares->length; j++)
                {
                    myboard->array[i] = SUDOKU_BOARD[i];
                    myboard->used_squares->head = myboard->used_squares->head->next;
                    
                }
                myboard->used_squares->length = 0;
                break;
            }
            else{
                continue;
            }
        }
    }
    
}

// en del av free_Struct, fjerner alle nodenen i used_list for elementer
void free_el_lists(l_list *list){
    for (int k = 0; k < list->length; k++)
        {
            l_node *tmp = list->head->next;
            free(list->head);
            list->head = tmp;
        }
}

// Free alle strukturer OBS Funker ikke helt enda
void free_structs(Board *myboard){

    for (int i = 0; i < 81; i++) {
        Square *s = myboard->square_list[i];
        for (int j = 0; j < s->legal_list->length; j++)
        {
            l_node *tmp = s->legal_list->head->next;
            free(s->legal_list->head);
            s->legal_list->head = tmp;
        }
        free(s);
    }
    for (int i = 0; i < 9; i++) {
        
        free_el_lists(myboard->rows[i]->used_list);
        free_el_lists(myboard->columns[i]->used_list);
        free_el_lists(myboard->boxes[i]->used_list);
        free(myboard->rows[i]);
        free(myboard->columns[i]);
        free(myboard->boxes[i]);
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
    clock_t t; 
    t = clock(); 
    int nr_problems = 100000;
    for (int i = 0; i < nr_problems; i++)
    {
    
    // Lager myboard
    Board *myboard = malloc(sizeof(Board));
    myboard->length = 81;
    myboard->solved = 0;
    myboard->used_squares = create_s_list();
    memcpy(myboard->array, SUDOKU_BOARD, (81 * sizeof(int)));


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
    
    // print_board(myboard);

    free_structs(myboard);
    
    }
    t = clock() - t; 
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 

    printf("Sudoku took %f seconds to execute %d boards\n", time_taken, nr_problems); 
    return 0;
}


