#include <stdio.h>
#include <stdlib.h>
#include "queue_dynamic.h"

typedef struct _empleado empleado;

#define NTREE_ELEM int

typedef struct _ntree{
    NTREE_ELEM data;
    struct _ntree** child;
    int cant;
    int max_size;
}ntree;

ntree* tnode_new(NTREE_ELEM value,int max_size);
void free_ntree(ntree* root,void free_node(NTREE_ELEM));
int add_child(ntree* t,ntree* node);
void print_int(int val);
void print_tree(ntree* root,void print_data(NTREE_ELEM));

void print_int2(int val,int level);
void print_tree2(ntree* root,void print_data(NTREE_ELEM,int),int level);

void print_int_with_level(int val);
void print_tree_bfs(ntree* root, void print_data(NTREE_ELEM));
int cantidad_nodos(ntree* root);
int grado(ntree* root);

int path(ntree* root,NTREE_ELEM node_val,int cmp(NTREE_ELEM,NTREE_ELEM),void print_node(NTREE_ELEM,int));
int cmp_int(int a,int b);
void print_path(int val,int first);
ntree* remove_ntree_node(NTREE_ELEM to_remove,ntree* root,ntree* father,int cmp(NTREE_ELEM,NTREE_ELEM));