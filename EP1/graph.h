#ifndef GRAPH_H
#define GRAPH_H
struct graph{
  int numV; /* numero de vertices do grafo */
  int numE; /* numero de arcos do grafo */
  link *adj; /*ponteiro para o vetor de listas de adjacencias */
};

typedef struct graph *Graph;

typedef struct node *link;

struct node{ /*elemento da lista de adjacencia */
  int x;
  link next;
};

link newNode(int,link);
Graph graphInit(int);
void insertEdge(Graph,int,int);
#endif 
