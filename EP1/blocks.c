#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "graph.h"

#define INFINITE 200000

//int* deleted;
//int* block;
int* father;
int* discovery;
int* degree;
//int* closure;
int* articulation;
int* low;
int* visited;

int time;
int numBlocks;

Graph G;

int numVertices;

//////////////////////
void dfs(int,int);
void biconnectedComponents();
/////////////////////

int main(int argc, char** argv){
  
  while(scanf("%d",&numVertices) != EOF){
    ////////////////////Inicializacao/////////////
    int k;
    G = graphInit(numVertices);
    //deleted = malloc(numVertices*sizeof(int));
    //block = malloc(numVertices*sizeof(int));
    father = malloc(numVertices*sizeof(int));
    discovery = malloc(numVertices*sizeof(int));
    //closure = malloc(numVertices*sizeof(int));
    articulation = malloc(numVertices*sizeof(int));
    low = malloc(numVertices*sizeof(int));
    visited = malloc(numVertices*sizeof(int));
    degree = malloc(numVertices*sizeof(int));
    
    for(k = 0; k < numVertices; k++){
      scanf("%d",&degree[k]);
      int i;
      for(i = 0; i < degree[k]; i++){
	int x;
	scanf("%d",&x);
	insertEdge(G,k,x);
      }
    }
    biconnectedComponents();

    link aux;
    /*
    for(k = 0; k < numVertices; k++){
      for(aux = G->adj[k]; aux != NULL; aux=aux->next){
	printf("%d ",aux->x);
      }
      puts("");
    }
    */
    printf("%d\n",numVertices);
    for(k = 0; k < numVertices; k++){
      printf("%d ",degree[k]);
      for(aux = G->adj[k]; aux != NULL; aux=aux->next){
	printf("%d ",aux->block);
      }
      puts("");
    }

    puts("\n\n");
  }
  return 0;
}

int min(int a,int b){
  if(a < b) return a;
  return b;
}

int max(int a,int b){
  if(a > b) return a;
  return b;
}

void outputComp(int u, int v){
  linkE aux;

  link a;
  
  aux = pop();
  
  printf("BLOCO %d> \n",numBlocks);
  while(!(u == aux->u && v == aux->v) && !(u == aux->v && v == aux->u)){
    printf("%d -> %d |",aux->u,aux->v);
    
    for(a = G->adj[aux->u]; a != NULL; a = a->next)
      if(a->x == aux->v)
	a->block = numBlocks;
    
    for(a = G->adj[aux->v]; a != NULL; a = a->next)
      if(a->x == aux->u)
	a->block = numBlocks;
      
    
    aux = pop();
  }
  printf("%d -> %d\n",aux->u,aux->v);
  
  for(a = G->adj[aux->u]; a != NULL; a = a->next)
    if(a->x == aux->v)
      a->block = numBlocks;
    
  for(a = G->adj[aux->v]; a != NULL; a = a->next)
    if(a->x == aux->u)
      a->block = numBlocks;
  puts("");
}

void dfs_visit(int u){
  visited[u] = 1;
  time++;
  low[u] = discovery[u] = time;

  link aux;
  for(aux = G->adj[u]; aux != NULL; aux=aux->next){
    if(!visited[aux->x]){
      push(u,aux->x);
      father[aux->x] = u;
      dfs_visit(aux->x);
      if(low[aux->x] >= discovery[u]){
	outputComp(u,aux->x);
	numBlocks++;
      }
      low[u] = min(low[u],low[aux->x]);
    }
    else if(father[u] != aux->x && discovery[aux->x] < discovery[u]){
      push(u,aux->x);
      low[u] = min(low[u],discovery[aux->x]);
    }
  }

}

void biconnectedComponents(){
  time = 0;
  numBlocks = 0;
  int i;
  for(i = 0; i  < numVertices; i++){ father[i] = -1; visited[i] = 0;}
  for(i = 0; i < numVertices; i++) if(!visited[i]) dfs_visit(i);
  father[0] = 0;
}


/*
void dfs_visit(int u){
  discovery[u] = time++;
  int children = 0;
  low[u] = discovery[u];
  int maxlow = -1 * INFINITE;
  
  link aux = malloc(sizeof(link));
  
  block[u] = numBlocks;
  
  for(aux = G->adj[u]; aux != NULL; aux = aux->next){
    if(father[aux->x] == -1){
      father[aux->x] = u;
      dfs_visit(aux->x);
      children++;
      low[u] = min(low[u],low[aux->x]);
      
      if(low[aux->x] == discovery[aux->x])
	printf("%d -> %d é ponte\n",u,aux->x);
      
      maxlow = max(maxlow,low[aux->x]);
    }
    else if(closure[aux->x] == INFINITE){
      if(aux->x != father[u]){
	low[u] = min(low[u],discovery[aux->x]);
      }
    }
  }
  closure[u] = time++;
    
  if(father[u] == u){
    if(children >= 2)
      articulation[u] = 1;
    else
      articulation[u] = 0;
  }
    else{
      if(maxlow >= discovery[u])
	articulation[u] = 1;
      else
	articulation[u] = 0; 
    }
}

void dfs(int r){
  int i;
  time = 0;

  for(i = 0; i < numVertices; i++){
    father[i] = -1;
    articulation[i] = -1;
    discovery[i] = INFINITE;
    closure[i] = INFINITE;
  }
  father[r] = r;
  dfs_visit(r);
}
*/
