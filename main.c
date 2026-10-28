#include"ntree.h"
int main(void) {

       // Raíz
    ntree* root = tnode_new(10, 5);

    // Nivel 1
    ntree* n20 = tnode_new(20, 3);
    ntree* n21 = tnode_new(21, 1);
    ntree* n22 = tnode_new(22, 1);
    ntree* n23 = tnode_new(23, 0);
    ntree* n24 = tnode_new(24, 1);

    add_child(root, n20);
    add_child(root, n21);
    add_child(root, n22);
    add_child(root, n23);
    add_child(root, n24);

    // Nivel 2
    ntree* n30 = tnode_new(30, 0);
    ntree* n31 = tnode_new(31, 0);
    ntree* n32 = tnode_new(32, 0);
    ntree* n33 = tnode_new(33, 7);
    ntree* n34 = tnode_new(34, 0);
    ntree* n35 = tnode_new(35, 0);

    add_child(n20, n30);
    add_child(n20, n31);
    add_child(n20, n32);

    add_child(n21, n33);
    add_child(n22, n34);
    add_child(n24, n35);

    // Nivel 3
    for (int i = 40; i <= 46; i++) {
        ntree* nuevo = tnode_new(i, 0);
        add_child(n34, nuevo);
    }

    // Imprimo el árbol en preorden
    printf("Recorrido en preorden:\n");
    print_tree(root, print_int);
    printf("Recorrido en amplitud:\n");
    print_tree_bfs(root,print_int_with_level);
    printf("impresion identada\n");
    print_tree2(root,print_int2,0);
    printf("la cantidad de nodos del arbol es: %d\n",cantidad_nodos(root));
    printf("el grado del arbol es: %d",grado(root));
    printf("camino desde 50 a la raiz:");
    path(root,50,cmp_int,print_path);

    // Libero todo el árbol
    free_ntree(root,NULL);

    return 0;
}

