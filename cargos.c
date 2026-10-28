#include "cargos.h"

empleado* new_empleado(char* carg,char* name){
    if(!strcmp(carg,"GERENTE") && !strcmp(carg,"DIRECTOR")  && !strcmp(carg,"EMPLEADO")){
        return NULL;
    }

    empleado* result=malloc(sizeof(empleado));
    if(result){
        result->cargo=carg;
        result->nombre=name;
    }
    return result;
}
void free_empleado(empleado* emp){
    free(emp);
}
void print_empleado(empleado* p){
    if(p==NULL){
        printf("empleado no encontrado");
        return;
    }
    printf("cargo: [%s], ",p->cargo);
    printf("nombre: %s\n",p->nombre);
}
void print_nombre(empleado* p){
    if(p==NULL){
        printf("empleado no encontrado");
        return;
    }
    printf("%s",p->nombre);
}

// ejercicio 3 de empleados, usa los archivos, cargos.h y cargos.c
void print_path_cargos(empleado* emp,int first){
    if(first){
        printf("{");
        print_nombre(emp);
        printf("}");
    }else{
        printf("->");
        printf("{");
        print_nombre(emp);
        printf("}");
    }
}
int cmp_nombres(empleado* a,empleado* b){
    if(a==NULL || b==NULL)return 0;
    return strcmp(a->nombre,b->nombre);
}
//ejercicio 3c
char* nivel_de_cargo(int level){ // devuelve el cargo que deberia tener el empleado segun su nivel en el arbol
    if(level==1){
        return "GERENTE";
    }else if(level==2){
        return "DIRECTOR";
    }else{
        return "EMPLEADO";
    }
}

// int all_charges_same_level(ntree* root)// funcion hecha solo para el ejercicio 3c de empleados (comentado ya que no compila con otros tipos de datos)
// {
//     if(root==NULL)return 0;

//     int level=1;

//     queue* q=queue_new();
//     enqueue(q,root);

//     while(!queue_isempty(q)){

//         int cant=queue_getsize(q);
//         for(int i=0;i<cant;i++)
//         {

//             ntree* aux=dequeue(q);
//             empleado* emp=aux->data;
//             if(strcmp(emp->cargo,nivel_de_cargo(level))!=0)
//                 return 0;
            
//             for(int i=0;i<aux->cant;i++)
//                 enqueue(q,aux->child[i]);
//         }
//         level++;
//     }
//     return 1;
// }

//ejercicio 4d en recorrido en amplitud
void print_one_level(ntree* root,int level,void print_data(NTREE_ELEM)){
    if(root==NULL)return;
    int cmp_level=1;
    queue* q=queue_new();
    enqueue(q,root);
    while(!queue_isempty(q)){
        int cant=queue_getsize(q);
        for(;cant>0;cant--){

            ntree* aux=dequeue(q);
            if(cmp_level==level){
                print_data(aux->data);
            }

             for(int i=0;i<aux->cant;i++){
                 enqueue(q,aux->child[i]);
             }
        }
        cmp_level++;
    }
}
//ejercicio 4d pero en profundidad
void _print_one_level_dfs(ntree* root,int level,int actual,void print_data(NTREE_ELEM)){
    if(root==NULL)return;
    if(level==actual){
        print_data(root->data);
        return;
    }
    for(int i=0;i<root->cant;i++){
        _print_one_level_dfs(root->child[i],level,actual+1,print_data);
    }
}
void print_one_level_dfs(ntree* root,int level,void print_data(NTREE_ELEM)){
    if(level<1 || print_data==NULL)return;
    _print_one_level_dfs(root,level,1,print_data);
}