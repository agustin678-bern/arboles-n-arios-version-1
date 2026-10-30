#include "ntree.h"

//ejercicio 1a
ntree* tnode_new(NTREE_ELEM value,int max_size){

    if(max_size<0)return NULL;
    ntree* result=malloc(sizeof(ntree));

    if(result){

        result->data=value;
        result->child=NULL;
        result->cant=0;
        result->max_size=max_size;

        if(result->max_size>0){// si el max_size que pase es mayor a 0 lo inicializo con malloc
            result->child=malloc(result->max_size * sizeof(ntree*));
            if(result->child == NULL){
                free(result);
                return NULL;
            }
        }
    }
    return result;
}



//liberador
void free_ntree(ntree* root,void free_node(NTREE_ELEM)){
    if(root!=NULL){

        for(int i=0;i<root->cant;i++){
            free_ntree(root->child[i],free_node);
        }
        // printf("Liberando nodo: %p\n", (void*)root); //cosa rara que me recomendo chatgpt para verificar la liberacion, muestra las direcciones de memoria que se visitan
        if(free_node!=NULL){
            free_node(root->data);
        }
        free(root->child);
        free(root);
    }
}




// ejercicio 1b
int add_child(ntree* t,ntree* node){

    if(t==NULL || node==NULL) return 0;

    if(t->cant == t->max_size){ // resize con realloc

        int new_size=(t->max_size==0)? 2 : t->max_size*2;

        ntree** aux=realloc(t->child,new_size*sizeof(ntree*));
        if(aux==NULL){
            return 0;
        }
        t->child=aux;
        t->max_size=new_size;
    }

    t->child[t->cant]=node;
    t->cant++;

    return 1;
}

int add_child_front(ntree*t, ntree* node){

    if(t==NULL || node==NULL) return 0;

    if(t->cant == t->max_size){ // resize con realloc

        int new_size=(t->max_size==0)? 2 : t->max_size*2;

        ntree** aux=realloc(t->child,new_size*sizeof(ntree*));
        if(aux==NULL){
            return 0;
        }
        t->child=aux;
        t->max_size=new_size;
    }
    for(int j=t->cant;j>0;j--){
        t->child[j]=t->child[j-1];
    }
    t->child[0]=node;
    t->cant++;
    return 1;

}



void print_int(int val){
    printf("%d\n",val);
}
// ejercicio 1c
void print_tree(ntree* root,void print_data(NTREE_ELEM)){
    if(root==NULL)return;

    print_data(root->data);
    for(int i=0; i< root->cant ;i++){
        print_tree(root->child[i],print_data);
    }
}



void print_int2(int val,int level){
    for(;level>0;level--){
        printf("  ");
    }
    printf("%d\n",val);
}
// ejercicio 1c pero con un print_data que necesita nivel para imprimir identado, sigue siendo recorrido dfs, (ejercicio 4b)
void print_tree2(ntree* root,void print_data(NTREE_ELEM,int),int level){
    if(root==NULL)return;

    print_data(root->data,level);
    for(int i=0; i< root->cant ;i++){
        print_tree2(root->child[i],print_data,(level+1));
    }
}




// esta impresion ya es para bfs(recorrido en amplitud)
void print_int_with_level(int val){
    printf("%d ",val);
}
// ejercicio 1d (ejercicio 4b)
void print_tree_bfs(ntree* root, void print_data(NTREE_ELEM)){
    if(root==NULL)return;
    int level=1;
    queue* q=queue_new();
    enqueue(q,root);
    int cant=1;
    while(!queue_isempty(q)){
        printf("nivel %d: \n",level);
        cant=queue_getsize(q);
        for(;cant>0;cant--){

            ntree* aux=dequeue(q);
            print_data(aux->data);

             for(int i=0;i<aux->cant;i++){
                 enqueue(q,aux->child[i]);
             }
        }
        printf("\n");
        level++;
    }
}



//ejercicio 1e
int cantidad_nodos(ntree* root){
    if(root==NULL)return 0;
    int result=1;
    for(int i=0;i<root->cant;i++){
        result+=cantidad_nodos(root->child[i]);
    }
    return result;
}

//ejercicio 1f, recorro en profundidad comparando grados y guardandome el cant de mi estructura con mayor valor
int grado(ntree* root){

    if(root==NULL)return 0;

    int grado_max=root->cant;

    for(int i=0;i<root->cant;i++){
        int to_cmp=grado(root->child[i]);
        if(grado_max < to_cmp){
            grado_max=to_cmp;
        }   
    }

    return grado_max;
}



//ejercicio 1h
int _todos_mismo_grado(ntree* root,int grado){

    if(root->cant!=grado && root->cant!=0) return 0;
    int result=1;
    for(int i=0;i<root->cant;i++){
        result=_todos_mismo_grado(root->child[i],grado);
        if(result==0){
            return result;
        }
    }
    return result;
}
int todos_mismo_grado(ntree* root){

    if(root==NULL) return 1;

    return _todos_mismo_grado(root,root->cant);
}




//ejercicio 2a
ntree* find(ntree* root,NTREE_ELEM value,int cmp(NTREE_ELEM,NTREE_ELEM)){

    if(root==NULL)return NULL;
    if(cmp(root->data,value)==0)return root;

    for(int i=0;i<root->cant;i++){
        ntree* found=find(root->child[i],value,cmp);
        if(found!=NULL)return found;
    }
    return NULL;
}




//ejercicio 2b parte privada
int _profundidad(ntree* root,NTREE_ELEM value,int cmp(NTREE_ELEM,NTREE_ELEM),int prof){
    int result=-1;
    if(root!=NULL){

        int comp=cmp(root->data,value);

        if(comp==0){
            result=prof;
        }
        else{
            
            for(int i=0;i<root->cant;i++){

                result=_profundidad(root->child[i],value,cmp,prof+1);

                if(result!=-1){
                    return result;
                }
            }
        }
    }
    return result;
}
//ejercicio 2b funcion publica
int profundidad(ntree* root,NTREE_ELEM value,int cmp(NTREE_ELEM,NTREE_ELEM)){
    if(cmp == NULL) return -1;
    return _profundidad(root,value,cmp,0);
}





// ejercicio 2c print
void print_path(int val,int first){
    if(first){
        printf("[%d]",val);// si es el primero no pongo flechita, quedaria [a]->[b]->[c] en vez de ->[a]->[b]->[c]
    }else
    printf("-->[%d]",val);
}
int cmp_int(int a,int b){
    return a-b;
}

//ejercicio 2c
int path(ntree* root,NTREE_ELEM node_val,int cmp(NTREE_ELEM,NTREE_ELEM),void print_node(NTREE_ELEM,int)){
    if(root==NULL)return 0;
    int result=0;
    if(cmp(root->data,node_val)==0){
        print_node(root->data,1);
        result=1;
    }else{
        for(int i=0;i<root->cant;i++){
            result=path(root->child[i],node_val,cmp,print_node);
            if(result>0){
                print_node(root->data,0);
                return 1;
            }
        }
    }
    return result;
}

//ejercicio 4c
void delete_node_from_tree(ntree* to_remove,ntree* father){
    if(father!=NULL){
    for(int i=0;i<father->cant;i++){
        if(father->child[i]==to_remove){
            for(int j=i;j<father->cant-1;j++){
                father->child[j]=father->child[j+1];
            }
            father->cant--;
            return;
        }
    }
}

}
ntree* remove_ntree_node(NTREE_ELEM to_remove,ntree* root,ntree* father,int cmp(NTREE_ELEM,NTREE_ELEM)){

    if(root==NULL)return NULL;
    ntree* found=NULL;
    if(cmp(to_remove,root->data)==0){
        found=root;
        if(found->cant==0){
            delete_node_from_tree(found,father);
        }
        else{
            NTREE_ELEM aux_data=found->data;

            ntree* removed=found->child[0];
            for(int i=removed->cant-1;i>=0;i--){
                add_child_front(found,removed->child[i]);
            }
            free(removed->child); 
            removed->child=NULL;
            removed->cant=0;
            removed->max_size=0;

            found->data=removed->data;
            removed->data=aux_data;
            delete_node_from_tree(removed,found);
            found=removed;
        }
        return found;
    }
    for(int i=0;i<root->cant;i++){
        found=remove_ntree_node(to_remove,root->child[i],root,cmp);
        if(found!=NULL){
            return found;
        }
    }
    return found;
    
}
void agregar_hijo(ntree* root,ntree* node,int N){
    if(root!=NULL && node!=NULL){
        int M=0;
        if(M>=N)M=0;
        if(root->cant<N){
            add_child_front(root,node);
            M++;
        }else if({
            reducir
        }
    }
}
void reducir_grado(ntree* root,int N){
    if(root->cant>N){
        agregar_hijo(root->child[M],root->child[i],int N);
    }
}