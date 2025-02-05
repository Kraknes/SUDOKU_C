#include <stdlib.h>
// #include "defs.h"
#include <stdio.h>
#include "map.h"

// OBS HAR ENDRET PÅ MAP.H MED TYPEDEF FOR MAP_T, KAN HENDE AT DET ØDELEGGER TING FRAMOVER 

// Hashmap opplegg: Key kan være ordet/string -->Sendes gjennom hasher--> får ut en minne til en verdi/count

#define SIZE_CAPACITY 100000;

struct node{
    void *key;
    void *value;
    void *next;
};
typedef struct node h_node;

struct map_t{
    size_t length;
    size_t capacity;
    h_node *head;
    struct node **hashtables;
};

map_t *map_create() {
    // Allokere minne til hashmap
    struct map_t *map = malloc(sizeof(struct map_t));

    if (map == NULL){
        printf("ERROR: Failed to malloc map_t in *map_create");
        return 0;
    }
    map->length = 0;    
    map->capacity = SIZE_CAPACITY;

    // allokere minne til hash table * capacity (antatt antall på tilførsel)
    map->hashtables =(struct node**) malloc(sizeof(h_node) * map->capacity);

    if (map->hashtables == NULL){
        printf("ERROR: Failed to malloc map->hashtable in *map_create");
        return 0;
    }

    // setter alt av innhold til null for mer effetiv sjekk om index er tom
    for (size_t i = 0; i < map->capacity; i++)
    {
        // printf("\n%llu", map->hashtables[i]);
        map->hashtables[i] = NULL;
        // printf("\n%llu", map->hashtables[i]);
    }
    return map;
}

void map_destroy(struct map_t *map) {
    
    for (size_t i = 0; i < map->length; i++)
    {   
        h_node *tmp = map->head;
        map->head = map->head->next;
        free(tmp);
        tmp = NULL;
    }
    free(map);
    map = NULL;
}

size_t map_length(struct map_t *map) {
    return map->length;
}


uint64_t hasher(const void *str) {
    /* note that these values are NOT chosen randomly. Modifying them will break the function. */
    static const uint64_t FNV_offset_basis = 0xcbf29ce484222325;
    static const uint64_t FNV_prime = 0x100000001b3;

    uint64_t hash = FNV_offset_basis;
    const uint8_t *p = (const uint8_t *) str;

    while (*p) {
        /* FNV-1a hash differs from the FNV-1 hash only by the
         * order in which the multiply and XOR is performed */
        hash ^= (uint64_t) *p;
        hash *= FNV_prime;
        p++;
    }

    return hash;
}


void *map_insert(struct map_t *map, void *key, size_t key_size, void *value) {
    /* TODO LIST:
    1. Lage node av key og value
    x. Må returnere NULL hvis alt gikk bra, eller returnere pointer til gamle key hvis det har blitt kollisjon
    x. Finne ut av key_size, ka e funskjonen    
    */

    // lager node for entry i hash table
    h_node *node = malloc(sizeof(h_node));

    if (node == NULL){
        printf("ERROR: Failed to malloc h_node in *map_insert");
        return NULL;
    }

    node->key = key;
    node->value = value;
    node->next = key_size;
    printf("\nKey is: %s", node->key);

    // lager en hashed key av nøkkelen
    uint64_t hashed_key = hasher(key);
    printf("\n Hashed key is: %llu", hashed_key);

    // modolu av array størrelse for å få unik index til array
    long long unsigned hashed_index = hashed_key % map->capacity;
    printf("\n Hashed index is: %llu", hashed_index);

    if (map->hashtables[hashed_index] != NULL)
    {
        printf("\n Position is already taken");
        return map->hashtables[hashed_index];
    }
    
    map->hashtables[hashed_index] = node;
    printf("\nValue at inserted position is: %d", map->hashtables[hashed_index]->value);
    // øker "lengden"/antall medlemmer av array
    map->length++;
    printf("\n-------------------------");
    return NULL;
}

void *map_remove(struct map_t *map, void *key) {
    /* TODO:
    - finner fram til hashed key i array, returner verdien i keyen
    
    */
       // lager en hashed key av nøkkelen
    uint64_t hashed_key = hasher(key);

    // modolu av array størrelse for å få unik index til array
    long long unsigned hashed_index = hashed_key % map->capacity;
    
    // Hvis keyen ikke eksistere i hash tablen
    if (map->hashtables[hashed_index] == NULL){
        printf("\nERROR: No entry in this hash key in *map_remove");
        return 0;
    }
    // henter ut verdien i hashtable, frigjør noden og returnere verdien
    void *rt_value = map->hashtables[hashed_index]->value;
    free(map->hashtables[hashed_index]);
    map->hashtables[hashed_index] = NULL;
    fflush(stdout);
    return rt_value;
}

void *map_get(struct map_t *map, void *key) {
    // lager en hashed key av nøkkelen
    uint64_t hashed_key = hasher(key);

    // modolu av array størrelse for å få unik index til array
    long long unsigned hashed_index = hashed_key % map->capacity;

    if (map->hashtables[hashed_index] == NULL){
        printf("\nERROR: No entry in this hash key in *map_get");
        return 0;
    }

    void *rt_value = map->hashtables[hashed_index]->value;
    free(map->hashtables[hashed_index]);
    printf("\nReturned value is: %d", rt_value);
    return rt_value;
}

int compare(const char *a, const char *b) {
    return (int) (*a - *b);
}

int main(){
    fflush(stdout);
    struct map_t *hashmap = map_create();
    map_insert(hashmap, "hey", 6, 10);
    map_insert(hashmap, "b", 6, 15);
    map_insert(hashmap, "a", 6, 30);

    map_get(hashmap, "hey");
    map_get(hashmap, "b");
    map_get(hashmap, "a");
    map_get(hashmap, "c");

    map_insert(hashmap, "hey", 6, 40);
    void *test2 = map_remove(hashmap, "hey");
    void *test = map_get(hashmap, "hey");
    printf("\n %s", test2);

    //problemer med test2, får ikke printet
}


