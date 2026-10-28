#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ntree.h"
typedef struct _empleado{
    char* cargo;
    char* nombre;
}empleado;

empleado* new_empleado(char* carg,char* name);
void free_empleado(empleado* emp);
void print_empleado(empleado* p);
void print_nombre(empleado* p);
void print_path_cargos(empleado* emp,int first);
int cmp_nombres(empleado* a,empleado* b);
int all_charges_same_level(ntree* root);
void print_one_level(ntree* root,int level,void print_data(NTREE_ELEM));
void print_one_level_dfs(ntree* root,int level,void print_data(NTREE_ELEM));