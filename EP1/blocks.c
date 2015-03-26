#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

#define INFINITE 200000

int* degree;
int* father;
int* discovery;
int* closure;
int* articulation;
int* low;
int time;

Graph G;

int numVertices;

//////////////////////
void dfs(int);
/////////////////////

int main(int argc, char** argv){
  
  while(scanf("%d",&numVertices) != EOF){
    ////////////////////Inicializacao/////////////
    int k;
    G = graphInit(numVertices);
    degree = malloc(numVertices*sizeof(int));
    father = malloc(numVertices*sizeof(int));
    discovery = malloc(numVertices*sizeof(int));
    closure = malloc(numVertices*sizeof(int));
    articulation = malloc(numVertices*sizeof(int));
    low = malloc(numVertices*sizeof(int));
    
    for(k = 0; k < numVertices; k++){
      scanf("%d",&degree[k]);
      int i;
      for(i = 0; i < degree[k]; i++){
	int x;
	scanf("%d",&x);
	insertEdge(G,k,x);
      }
    }
    //////////////////////////////////////////////
    link aux = malloc(sizeof(link));
    for(aux = G->adj[2]; aux != NULL; aux = aux->next) printf(">%d<\n",aux->x);
    dfs(0);
    for(k = 0; k < numVertices; k++) printf(" o pai de %d é %d\n",k,father[k]);
    for(k = 0; k < numVertices; k++) if(articulation[k]) printf("O vértice %d é de corte\n",k);
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


void dfs_visit(int u){
  discovery[u] = time++;
  int children = 0;
  low[u] = discovery[u];
  int maxlow = -1 * INFINITE;
  
  link aux = malloc(sizeof(link));
  
  for(aux = G->adj[u]; aux != NULL; aux = aux->next){
    if(father[aux->x] == -1){
      father[aux->x] = u;
      dfs_visit(aux->x);
      children++;
      low[u] = min(low[u],low[aux->x]);
      
      if(low[aux->x] == discovery[aux->x])
	printf("%d -> %d é ponte\n",u,aux->x);
      //else
	//printf("%d -> %d não é ponte\n",u,aux->x);
      
      maxlow = max(maxlow,low[aux->x]);
    }
    else if(closure[aux->x] == INFINITE){
      if(aux->x != father[u]){
	//printf("%d -> %d não é ponte\n",u,aux->x);
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

