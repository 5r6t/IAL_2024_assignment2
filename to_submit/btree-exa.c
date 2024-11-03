/*
 * Použití binárních vyhledávacích stromů.
 *
 * S využitím Vámi implementovaného binárního vyhledávacího stromu (soubory ../iter/btree.c a ../rec/btree.c)
 * implementujte triviální funkci letter_count. Všimněte si, že výstupní strom může být značně degradovaný 
 * (až na úroveň lineárního seznamu). Jako typ hodnoty v uzlu stromu využijte 'INTEGER'.
 * 
 */

#include "../btree.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Convert alphabetic characters to lowercase
 * 
 * If the characters are not alphabetic or are already lowercase, return the same character
 * a -> a, B -> b, * -> * 
 */
char to_lower(char c) {
    if (c >= 'A' && c <= 'Z') { // between 65 and 90
        c += 'a' - 'A'; // increase value by 32
    }
    return c;
}

/**
 * Vypočítání frekvence výskytů znaků ve vstupním řetězci.
 * 
 * Funkce inicilializuje strom a následně zjistí počet výskytů znaků a-z (case insensitive), znaku 
 * mezery ' ', a ostatních znaků (ve stromu reprezentováno znakem podtržítka '_'). Výstup je 
 * uložen ve stromu (klíč vždy lowercase).
 * 
 * Například pro vstupní řetězec: "abBccc_ 123 *" bude strom po běhu funkce obsahovat:
 * 
 * key | value
 * 'a'     1
 * 'b'     2
 * 'c'     3
 * ' '     2
 * '_'     5
 * 
 * Pro implementaci si můžete v tomto souboru nadefinovat vlastní pomocné funkce.
*/
void letter_count(bst_node_t **tree, char *input) {
    bst_init(tree);

    int i = 0;
    while(input[i] != '\0') {
        char c = to_lower(input[i]);
        char key;

        if ( c >= 'a' && c <= 'z') { key = c; } // alphabetic
        else if ( c == ' ') { key = ' '; } // space
        else { key = '_'; } // other

        bst_node_content_t *cur_value;
        if (bst_search(*tree, key, &cur_value)) { 
            int *count_ptr = (int*)(cur_value->value); // cast void* to int*; so that count_ptr can access the value
            (*count_ptr)++;
        } // found; increment

        else {
            bst_node_content_t new_content = {
                .type = INTEGER,
                .value = malloc(sizeof(int))
            };

            if (new_content.value == NULL) {
                fprintf(stderr, "Memory allocation failed!\n");
                exit(1);
            }
            
            *(int*)(new_content.value) = 1; 
            bst_insert(tree, key, new_content);
        } // not found; create

        i++;
    }
}