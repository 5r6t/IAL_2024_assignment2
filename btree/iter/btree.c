/*
 * Binární vyhledávací strom — iterativní varianta
 *
 * S využitím datových typů ze souboru btree.h, zásobníku ze souboru stack.h
 * a připravených koster funkcí implementujte binární vyhledávací
 * strom bez použití rekurze.
 */

#include "../btree.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Inicializace stromu.
 *
 * Uživatel musí zajistit, že inicializace se nebude opakovaně volat nad
 * inicializovaným stromem. V opačném případě může dojít k úniku paměti (memory
 * leak). Protože neinicializovaný ukazatel má nedefinovanou hodnotu, není
 * možné toto detekovat ve funkci.
 */
void bst_init(bst_node_t **tree)
{
  *tree = NULL;
}

/*
 * Vyhledání uzlu v stromu.
 *
 * V případě úspěchu vrátí funkce hodnotu true a do proměnné value zapíše
 * ukazatel na obsah daného uzlu. V opačném případě funkce vrátí hodnotu false a proměnná
 * value zůstává nezměněná.
 *
 * Funkci implementujte iterativně bez použité vlastních pomocných funkcí.
 */
bool bst_search(bst_node_t *tree, char key, bst_node_content_t **value)
{
  if (tree == NULL) return false;

  while (tree != NULL) {
    if (key < tree->key) {
      tree = tree->left;
    }
    else if (key > tree->key) { 
      tree = tree->right;
    }
    else { // (key = tree->key)
      *value = &(tree->content);
      return true;
    }
  }
  return false;
}

/*
 * Vložení uzlu do stromu.
 *
 * Pokud uzel se zadaným klíče už ve stromu existuje, nahraďte jeho hodnotu.
 * Jinak vložte nový listový uzel.
 *
 * Výsledný strom musí splňovat podmínku vyhledávacího stromu — levý podstrom
 * uzlu obsahuje jenom menší klíče, pravý větší.
 *
 * Funkci implementujte iterativně bez použití vlastních pomocných funkcí.
 */
void bst_insert(bst_node_t **tree, char key, bst_node_content_t value)
{
  if (*tree == NULL) { // Tree is completely empty, insert at root
    *tree = (bst_node_t *)malloc(sizeof(bst_node_t));
    if (*tree == NULL) {
      fprintf(stderr, "Memory allocation failed.");
      exit(1);
    }
    (*tree)->content = value;
    (*tree)->key = key;
    (*tree)->left = NULL;
    (*tree)->right = NULL;
    return;
  }

  bst_node_t *parent = *tree; // Start at the root

  while (true) {
    if (key == parent->key) { // Key already exists, update content
      free(parent->content.value);
      parent->content = value;
      return;
    }
    else if (key < parent->key) { // Go left
      if (parent->left == NULL) { // Insert new node as left child
        parent->left = (bst_node_t *)malloc(sizeof(bst_node_t));
        if (parent->left == NULL) {
          fprintf(stderr, "Memory allocation failed.");
          exit(1);
        }
        parent->left->content = value;
        parent->left->key = key;
        parent->left->left = NULL;
        parent->left->right = NULL;
        return;
      }
      parent = parent->left;
    }
    else { // Go right
      if (parent->right == NULL) { // Insert new node as right child
        parent->right = (bst_node_t *)malloc(sizeof(bst_node_t));
        if (parent->right == NULL) {
          fprintf(stderr, "Memory allocation failed.");
          exit(1);
        }
        parent->right->content = value;
        parent->right->key = key;
        parent->right->left = NULL;
        parent->right->right = NULL;
        return;
      }
      parent = parent->right;
    }
  }
}

/*
 * Pomocná funkce která nahradí uzel nejpravějším potomkem.
 *
 * Klíč a hodnota uzlu target budou nahrazené klíčem a hodnotou nejpravějšího
 * uzlu podstromu tree. Nejpravější potomek bude odstraněný. Funkce korektně
 * uvolní všechny alokované zdroje odstraněného uzlu.
 *
 * Funkce předpokládá, že hodnota tree není NULL.
 *
 * Tato pomocná funkce bude využita při implementaci funkce bst_delete.
 *
 * Funkci implementujte iterativně bez použití vlastních pomocných funkcí.
 */
void bst_replace_by_rightmost(bst_node_t *target, bst_node_t **tree)
{
  bst_node_t *parent = NULL;
  bst_node_t *tmp = *tree;

  while(tmp->right != NULL) {
    parent = tmp;
    tmp = tmp->right;
  } // until tmp pointing to rightmost

  free(target->content.value);

  target->key = tmp->key;
  target->content = tmp->content;

  if (parent != NULL) {
    parent->right = tmp->left;
  } 
  else { 
    *tree = tmp->left; 
  }
  free(tmp);
  tmp = NULL;
}

/*
 * Odstranění uzlu ze stromu.
 *
 * Pokud uzel se zadaným klíčem neexistuje, funkce nic nedělá.
 * Pokud má odstraněný uzel jeden podstrom, zdědí ho rodič odstraněného uzlu.
 * Pokud má odstraněný uzel oba podstromy, je nahrazený nejpravějším uzlem
 * levého podstromu. Nejpravější uzel nemusí být listem.
 *
 * Funkce korektně uvolní všechny alokované zdroje odstraněného uzlu.
 *
 * Funkci implementujte iterativně pomocí bst_replace_by_rightmost a bez
 * použití vlastních pomocných funkcí.
 */
void bst_delete(bst_node_t **tree, char key)
{
  if (*tree == NULL) return;

  bst_node_t *current = *tree;
  bst_node_t *parent = NULL;
    
  while (current != NULL && current->key != key) {
    parent = current;
    current = (key < current->key) ? current->left : current->right;
   }
  if (current == NULL) return;

  if (current->left == NULL && current->right == NULL) {
    if (parent == NULL) { 
      *tree = NULL; 
    } else if (parent->left == current) { 
        parent->left = NULL; 
    } else { 
      parent->right = NULL; 
    }
    free(current->content.value);
    free(current);
    current = NULL;
  } // zero sons

  else if (current->left == NULL || current->right == NULL) {
    bst_node_t *tmp = (current->left != NULL) ? current->left : current->right;

    if (parent == NULL) { *tree = tmp; }
    else if (parent->left == current) { parent->left = tmp; }
    else { parent->right = tmp; }

    free(current->content.value);
    free(current);
    current = NULL;
  } // one son

  else {
    bst_replace_by_rightmost(current, &(current->left));
  } // two sons
}

/*
 * Zrušení celého stromu.
 *
 * Po zrušení se celý strom bude nacházet ve stejném stavu jako po
 * inicializaci. Funkce korektně uvolní všechny alokované zdroje rušených
 * uzlů.
 *
 * Funkci implementujte iterativně s pomocí zásobníku a bez použití
 * vlastních pomocných funkcí.
 */
void bst_dispose(bst_node_t **tree)
{
  if (*tree == NULL) return;

  stack_bst_t stack;
  stack_bst_init(&stack);

  stack_bst_push(&stack, *tree);

  while (!stack_bst_empty(&stack)) {
    bst_node_t *node = stack_bst_pop(&stack);
    if (node->left != NULL) {
      stack_bst_push(&stack, node->left);
    }
    if (node->right != NULL ) {
      stack_bst_push(&stack, node->right);
    }
    free(node->content.value);
    free(node);
    node = NULL;
  }
  *tree = NULL;
}

/*
 * Pomocná funkce pro iterativní preorder.
 *
 * Prochází po levé větvi k nejlevějšímu uzlu podstromu.
 * Nad zpracovanými uzly zavolá bst_add_node_to_items a uloží je do zásobníku uzlů.
 *
 * Funkci implementujte iterativně s pomocí zásobníku a bez použití
 * vlastních pomocných funkcí.
 */
void bst_leftmost_preorder(bst_node_t *tree, stack_bst_t *to_visit, bst_items_t *items)
{
  if (tree == NULL) return;

  while (tree != NULL) {
    bst_add_node_to_items(tree, items);
    stack_bst_push(to_visit, tree);
    tree = tree->left;
  }
}

/*
 * Preorder průchod stromem.
 *
 * Pro aktuálně zpracovávaný uzel zavolejte funkci bst_add_node_to_items.
 *
 * Funkci implementujte iterativně pomocí funkce bst_leftmost_preorder a
 * zásobníku uzlů a bez použití vlastních pomocných funkcí.
 */
void bst_preorder(bst_node_t *tree, bst_items_t *items)
{
  if (tree == NULL) return;
  stack_bst_t stack;
  stack_bst_init(&stack);

  bst_leftmost_preorder(tree, &stack, items);

  while (!stack_bst_empty(&stack)) {
    bst_node_t *node = stack_bst_top(&stack);
    stack_bst_pop(&stack);

    if (node->right != NULL) {
      bst_leftmost_preorder(node->right, &stack, items);
    }
  }
}

/*
 * Pomocná funkce pro iterativní inorder.
 *
 * Prochází po levé větvi k nejlevějšímu uzlu podstromu a ukládá uzly do
 * zásobníku uzlů.
 *
 * Funkci implementujte iterativně s pomocí zásobníku a bez použití
 * vlastních pomocných funkcí.
 */
void bst_leftmost_inorder(bst_node_t *tree, stack_bst_t *to_visit)
{
  if (tree == NULL) return;

  while (tree != NULL) {
    stack_bst_push(to_visit, tree);
    tree = tree->left;
  }
}

/*
 * Inorder průchod stromem.
 *
 * Pro aktuálně zpracovávaný uzel zavolejte funkci bst_add_node_to_items.
 *
 * Funkci implementujte iterativně pomocí funkce bst_leftmost_inorder a
 * zásobníku uzlů a bez použití vlastních pomocných funkcí.
 */
void bst_inorder(bst_node_t *tree, bst_items_t *items)
{
  if (tree == NULL) return;
  stack_bst_t stack;
  stack_bst_init(&stack);

  bst_leftmost_inorder(tree, &stack);

  while (!stack_bst_empty(&stack)) {
    bst_node_t *node = stack_bst_top(&stack);
    stack_bst_pop(&stack);
    bst_add_node_to_items (node, items);
    if (node->right != NULL) 
    bst_leftmost_inorder(node->right, &stack);
  }
}

/*
 * Pomocná funkce pro iterativní postorder.
 *
 * Prochází po levé větvi k nejlevějšímu uzlu podstromu a ukládá uzly do
 * zásobníku uzlů. Do zásobníku bool hodnot ukládá informaci, že uzel
 * byl navštíven poprvé.
 *
 * Funkci implementujte iterativně pomocí zásobníku uzlů a bool hodnot a bez použití
 * vlastních pomocných funkcí.
 */
void bst_leftmost_postorder(bst_node_t *tree, stack_bst_t *to_visit,
                            stack_bool_t *first_visit)
{
  if (tree == NULL) return;

  while (tree != NULL) {
    stack_bst_push(to_visit, tree);
    stack_bool_push(first_visit, true);
    tree = tree->left;
  }
}

/*
 * Postorder průchod stromem.
 *
 * Pro aktuálně zpracovávaný uzel zavolejte funkci bst_add_node_to_items.
 *
 * Funkci implementujte iterativně pomocí funkce bst_leftmost_postorder a
 * zásobníku uzlů a bool hodnot a bez použití vlastních pomocných funkcí.
 */
void bst_postorder(bst_node_t *tree, bst_items_t *items)
{
  bool fromLeft;
  stack_bst_t to_visit;
  stack_bool_t first_visit;
  stack_bst_init(&to_visit);
  stack_bool_init(&first_visit);

  bst_leftmost_postorder(tree, &to_visit, &first_visit);

  while (! stack_bst_empty(&to_visit)) {
    bst_node_t *node = stack_bst_top(&to_visit);
    fromLeft = stack_bool_top(&first_visit);
    stack_bool_pop(&first_visit);
    if (fromLeft) { // from L; goes to R
      stack_bool_push(&first_visit, false);
      bst_leftmost_postorder(node->right, &to_visit, &first_visit);
    }
    else { // from R; remove and process
      stack_bst_pop(&to_visit);
      bst_add_node_to_items(node, items);
    }
  }
}
