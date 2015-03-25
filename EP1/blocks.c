#include <stdio.h>
#include <stdlib.h>
#include <graph.h>

int* grau;
int* pai;

Graph G;

int numVertices;

//////////////////////
void dfs(int);
/////////////////////

int main(int argc, char* argv){
  
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

  }
  return 0;
}


void dfs(int r){
  int i;
  for(i = 0; i < numVertices; i++){
    pai[i] = NULL;
  }
  pai[r] = r;
  dfs-visit(r);
}

void dfs-visit(int u){
  link aux;

  for(aux = G->adj[u]; aux != NULL; aux = aux->prox){
    if(pai[u] == NULL){
      pai[aux->x] = u;
      dfs-visit(aux->x);
    }
  }
  

}
