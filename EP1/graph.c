#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

link newNode(int x, link next){ /*cria um novo node na lista de adjacencia */
  link a = malloc(sizeof(struct node));
  a->x = x;
  a->next = next;
  a->block = -1;
  return a;
}

Graph graphInit(int V){ /*inicializa o grafo com V vertices */
  int v;
  Graph G = malloc(sizeof *G);
  G->numV = V;
  G->numE = 0;
  G->adj = malloc(V*sizeof(link));
  for(v = 0; v < V; v++)
    G->adj[v] = NULL;
  return G;
}

void insertEdge(Graph G,int u, int v){ /*adiciona uma aresta ao grafo */
  link a;
  for(a = G->adj[u]; a != NULL; a = a->next) //Checa repetições
    if(a->x == v) return;

  /*Esse pedaço insere cada vertice no final das listas de adjacencia para ficar em ordem crescente na saida*/
  /////////////////////////////////////
  if(G->adj[u] == NULL){
    G->adj[u] = newNode(v,NULL);
  }else{
    a = G->adj[u];
    while(a->next) a = a->next;
    a->next = newNode(v,NULL);
  }

  if(G->adj[v] == NULL){
    G->adj[v] = newNode(u,NULL);
  }else{
    a = G->adj[v];
    while(a->next) a = a->next;
    a->next = newNode(u,NULL);
  }
  /////////////////////////////////////////
  G->numE++;
}
    
void removeVertex(Graph G,int v){
  link aux;
  link aux2;
  link nextnode;
  link prev = NULL;
  
  for(aux = G->adj[v]; aux != NULL; aux = aux->next){
    prev = NULL;
    for(aux2 = G->adj[aux->x]; aux2 != NULL; aux2 = nextnode){
      nextnode = aux2->next;
      if(aux2->x == v){
	if(prev != NULL){
	  prev->next = nextnode;
	  free(aux2);
	}
	else{
	  if(nextnode != NULL){
	    G->adj[aux->x]->x = nextnode->x;
	    G->adj[aux->x]->next = nextnode->next;
	    free(nextnode);
	  }
	  else{
	    G->adj[aux->x] = NULL;
	    free(aux2);
	  }
	}
      }
      prev = aux2;
    }
  }
}		     
