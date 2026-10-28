// main de prueba para el ejercicio de empleados, se necesita cargos.c, cargos.h, ntree.c y ntree.h, comentar main.c y probarlo

// #include "cargos.h"

// int main(void) {

//     // NIVEL 0 - GERENTE
//     ntree* gerente = tnode_new(
//         new_empleado("GERENTE", "Ariel Perez"), 2
//     );

//     // NIVEL 1 - DIRECTORES
//     ntree* administracion = tnode_new(
//         new_empleado("DIRECTOR", "Antonio Emerson"), 2
//     );

//     ntree* produccion = tnode_new(
//         new_empleado("DIRECTOR", "Josefa Lake"), 1
//     );

//     ntree* comercial = tnode_new(
//         new_empleado("DIRECTOR", "Arturo Palmer"), 2
//     );

//     // NIVEL 2 - EMPLEADOS
//     ntree* andrea = tnode_new(
//         new_empleado("EMPLEADO", "Andrea Heras"), 0
//     );

//     ntree* clotilde = tnode_new(
//         new_empleado("EMPLEADO", "Clotilde Schwarzkopf"), 0
//     );

//     ntree* raimunda = tnode_new(
//         new_empleado("EMPLEADO", "Raimunda Gates"), 0
//     );

//     ntree* estibaliz = tnode_new(
//         new_empleado("EMPLEADO", "Estibaliz Bacon"), 0
//     );

//     ntree* luis = tnode_new(
//         new_empleado("EMPLEADO", "Luis Hidalgo"), 0
//     );

//     // CONEXIONES DEL GERENTE
//     add_child(gerente, administracion);
//     add_child(gerente, produccion);
//     add_child(gerente, comercial);

//     // EMPLEADOS DE ADMINISTRACION
//     add_child(administracion, andrea);
//     add_child(administracion, clotilde);

//     // EMPLEADOS DE PRODUCCION
//     add_child(produccion, raimunda);

//     // EMPLEADOS DE COMERCIAL
//     add_child(comercial, estibaliz);
//     add_child(comercial, luis);

//     // PRUEBA DEL RESIZE
//     printf("Cantidad de hijos: %d\n", gerente->cant);
//     printf("Capacidad: %d\n", gerente->max_size);

//     //PRUEBAS
//     print_tree_bfs(gerente, print_empleado);
//     printf("\n");
//     printf("camino desde Raimunda hasta el gerente: ");
//     path(gerente,raimunda->data,cmp_nombres,print_path_cargos);
//     printf("\n");
//     if(all_charges_same_level(gerente)){
//         printf("todos los niveles tienen los mismos cargos");
//     }else printf("los niveles tienen cargos distintos");
//     printf("\nnivel 1 impreso:\n");
//     print_one_level_dfs(gerente,1,print_empleado);
    




    // LIBERACION DE MEMORIA
//     free_ntree(gerente, free_empleado);
//     return 0;
// }