#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int* grau;
int* pai;

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
    grau = malloc(numVertices*sizeof(int));
    pai = malloc(numVertices*sizeof(int));
    
    for(k = 0; k < numVertices; k++){
      scanf("%d",&grau[k]);
      int i;
      for(i = 0; i < grau[k]; i++){
	int x;
	scanf("%d",&x);
	insertEdge(G,k,x);
      }
    }
    //////////////////////////////////////////////
    dfs(0);
    for(k = 0; k < numVertices; k++) printf(" o pai de %d é %d\n",k,pai[k]);
  }
  return 0;
}


void dfs_visit(int u){
  link aux = malloc(sizeof(link));
  for(aux = G->adj[u]; aux != NULL; aux = aux->next){
    if(pai[aux->x] == -1){
      pai[aux->x] = u;
      dfs_visit(aux->x);
    }
  }
}


void dfs(int r){
  int i;
  for(i = 0; i < numVertices; i++){
    pai[i] = -1;
  }
  pai[r] = r;
  dfs_visit(r);
}

