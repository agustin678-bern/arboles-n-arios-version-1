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
void reducir_grado(ntree* root,int N){
    if(root==NULL)return;
    if(root->cant>N){
        int M=0;
        for(int i=N;i<root->cant;i++){

            if(M>=N)M=0;
            printf("agregando nodo %d a padre %d",root->child[i]->data,root->child[M]->data);
            add_child(root->child[M],root->child[i]);
            M++;
        }
        root->cant=N;
    }
    for(int i=0;i<root->cant;i++){
        reducir_grado(root->child[i],N);
    }
}
// ejercicio 5
int arboles_identicos(ntree* r1,ntree* r2, int cmp(NTREE_ELEM,NTREE_ELEM)){
    if(r1==NULL && r2==NULL)return 1;
    if(r1==NULL || r2==NULL)return 0;
    int result=1;
    if(r1->cant!=r2->cant || cmp(r1->data,r2->data)!=0){
        result=0;
    }else{
        for(int i=0;i<r1->cant;i++){
            result=arboles_identicos(r1->child[i],r2->child[i],cmp);
            if(result==0){
                return result;
            }
        }
    }
    return result;
}
// ejercicio 6
int cantidad_caminos(ntree* root,int k){

    if(root==NULL)return 0;
    if(root->cant==0 && k==root->data) return 1;
    else if(root->cant==0 && k!=0)return 0;

    int result=0;
    for(int i=0;i<root->cant;i++){
        result+=cantidad_caminos(root->child[i],k-root->data);
    }
    return result;
}

int almacenar_camino(ntree* root,ntree* n,queue* q){
    if(root==NULL)return 0;
    if(root==n){
        enqueue(q,root);
        return 1;
    }
    for(int i=0;i<root->cant;i++){
        int result=almacenar_camino(root->child[i],n,q);
        if(result==1){
            enqueue(q,root);
            return result;
        }
    }
    return 0;
}
// ejercicio 7 hecho con dos colas y una pila, un quilombo, mejor haber almacenado el camino en dos arrays
void print_camino_entre_nodos(ntree* A,ntree* B,ntree* root, void print(NTREE_ELEM)){

    if(root==NULL || A==NULL || B==NULL ) return;

    queue* qA=queue_new();
    almacenar_camino(root,A,qA);
    queue* qB=queue_new();
    almacenar_camino(root,B,qB);
    stack* aux=stack_new();
    int found=0;
    while(!queue_isempty(qA) && !found){

        ntree* nodeA=dequeue(qA);
        ntree* nodeB=NULL;

        print(nodeA->data);

        int cantB=queue_getsize(qB);

        for(int i=0;i<cantB;i++){
            nodeB=dequeue(qB);
            if(nodeA==nodeB){
                found=1;
            }
            enqueue(qB,nodeB);
        }   
        
        if(found){
            nodeB=dequeue(qB);
            while(!queue_isempty(qB) && nodeB!=nodeA){
                push(aux,nodeB);
                nodeB=dequeue(qB);
            }
            while(!stack_isempty(aux)){
                print(pop(aux)->data);
            }
        }
    }
    stack_free(aux);
    queue_free(qA);
    queue_free(qB);
}
//ejercicio 8
int height(ntree* root){
    if(root==NULL)return 0;
    if(root->cant==0)return 0;
    int max_h=height(root->child[0]);
    for(int i=1;i<root->cant;i++){
        int h=height(root->child[i]);
        if(h>max_h){
            max_h=h;
        }
    }
    return 1+max_h;
}
//ejercicio 8
int is_balanced(ntree* root){

    if(root==NULL)return 1;
    if(root->cant==0)return 1;

    int max_h=height(root->child[0]);
    int min_h=max_h;
    int result=1;

    for(int i=1;i<root->cant;i++){
        int h=height(root->child[i]);
        if(h>max_h){
            max_h=h;
        }if(h<min_h){
            min_h=h;
        }
    }
    if(max_h-min_h>1){
        return 0;
    }
    for(int i=0;i<root->cant;i++){
        result=is_balanced(root->child[i]);
        if(result==0){
            return result;
        }
    }
    return result;
}
//ejercicio 9