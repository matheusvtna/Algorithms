/*-----------------------GRAFO------------------------*/

#include <bits/stdc++.h>
#define UNVISITED 0
#define VISITED 1

using namespace std;


stack<int> pilha;

//ADT 
typedef struct{
	int** matrix; 	//Matriz de adjacências
	int numEdges; 	//Número de arestas
	int numNodes; 	//Número de vértices
	int* mark;	  	//Array auxiliar de marcação
} Graph;


//Inicializando a estrutura com 'n' vértices 
Graph* createGraph(int n){
	Graph* g = (Graph *) malloc(sizeof(Graph));
	int i;

	//Aloca-se o vetor de marcados
	g->mark = (int *) calloc(n, sizeof(int));

	//Aloca-se a matriz de adjacências
	g->matrix = (int **) calloc(n, sizeof(int *));

	for(i=0 ; i<n ; i++){
		g->matrix[i] = (int*) calloc(n, sizeof(int));
	}

	//Seta o número de vértices para 'n'
	g->numNodes = n;

	//Seta o número de arestas para 0
	g->numEdges = 0;

	return g;
}

//Retorna o número de vértices de um grafo
int n(Graph* g){
	return g->numNodes;
}

void destructyGraph(Graph* g){
	int i;

	for(i=0 ; i<n(g) ; i++){
		free(g->matrix[i]);
	}
	free(g->matrix);
	free(g->mark);
	free(g);
}

//Retorna o número de arestas de um grafo
int e(Graph* g){
	return g->numEdges;
}

//Retorna o primeiro vértice ligado ao vértice de índice 'v' seguindo a ordem da matriz de adjacências
int first(Graph* g, int v){
	int i;

	for(i=0 ; i<n(g) ; i++){
		if(g->matrix[v][i] != 0) return i;
	}

	return n(g);
}

//Retorna o próximo vértice ligado ao vértice de indice 'v' após o vértice de índice 'w'
int next(Graph* g, int v, int w){
	int i;

	for(i=w+1 ; i<n(g) ; i++){
		if(g->matrix[v][i] != 0) return i;
	}

	return n(g);
}

//Cria uma aresta entre os vértices de índices 'i' e 'j' com peso 'wt'
void setEdge(Graph* g, int i, int j, int wt){
	if(wt == 0){
		return;
	}

	if(g->matrix[i][j] == 0){
		g->numEdges++;
	}
	
	g->matrix[i][j] = wt;	//Caso queira um grafo não-dirigido seria necessário
							//setar outra aresta entre os vértices, saindo de 'j'
							//e chegando em 'i'

}

//Retorna um valor verdade que verifica a existência de aresta entre os vértices de índices 'i' e 'j'
int isEdge(Graph* g, int i, int j){
	return g->matrix[i][j];
}

//Deleta a aresta entre os vértices de índices 'i' e 'j'
void delEdge(Graph* g, int i, int j){

	//Caso exista a aresta, o grafo terá uma 
	//aresta a menos após a remoção desta
	if(isEdge(g, i, j)){
		g->numEdges--;
	}
	
	//A posição matrix[i][j] será setada para 0
	//(A função se comporta bem caso a aresta não exista)
	g->matrix[i][j] = 0;
}


//Retorna o peso da aresta entre os vértices de índices 'i' e 'j'
int weight(Graph* g, int i, int j){
	return g->matrix[i][j]; //Caso não haja aresta, o peso é zero e
							//a função se comporta bem nessa ocasião
}

//Seta um valor 'val' na posição de índice 'v' do array auxilar com alguma flag
void setMark(Graph* g, int v, int val){
	g->mark[v] = val;
}

//Verifica qual a marcação na posição de índice 'v' do array auxiliar
int getMark(Graph* g, int v){
	return g->mark[v];
}

//Busca o primeiro filho não-visitado do vértice atual
void DFS(Graph* g, int v){
	int w;

	//É comum haver uma função de pré-visite, em que seu conteúdo varia de acordo com o problema
	//Exemplo de chamada: preVisit(g, v);


	//Seta o vértice de origem com visitado
	setMark(g, v, VISITED);

	w = first(g, v);	//Atribui a 'w' o valor do primeiro 
						//vértice ligado ao vértice de índice 'v'

	//Enquanto houver vértices ligados ao vértice em questão
	while(w < n(g)){

		if(getMark(g, w) == UNVISITED){ 
			DFS(g, w);	//Se o vértice encontrado ainda não foi visitado, 
		 				//deve-se chamar a travessia nesse vértice
		}

		//'w' assume o índice do próximo vértice ligado ao   
		//vértice de índice 'v após o último velor de 'w'
		w = next(g, v, w);
	}

	//Assim como a pré-visita, é comum haver uma pós-visita, em que seu conteúdo também varia de acordo com o problema
	//Exemplo de chamada: posVisit(g, v);

}

//Busca todos os filhos não-visitados do vértice atual em fila
void BFS(Graph* g, int start){

	int v, w;

	//Fila dos vértices a serem processados 
	queue<int> fila;

	//Insere o vértice de origem na fila
	fila.push(start);

	setMark(g, start, VISITED); //Vértice de origem visitado

	while(!fila.empty()){

		//'v' assume o índice do vértice a ser visitado
		v = fila.front();

		//É comum haver uma função de pré-visite, em que seu conteúdo varia de acordo com o problema
		//Exemplo de chamada: preVisit(g, v);

		//Retira o primeiro vértice da fila ('v'), pois este já foi visitado
		fila.pop();

		//'w' assume o índice do primeiro vértice ligado a 'v'
		w = first(g, v);

		while(w < n(g)){

			if(getMark(g, w) == UNVISITED){ //Caso o vértice encontrado não tenha
				setMark(g, w, VISITED);		//sido visitado ainda, ele é marcado como 
				fila.push(w);			//visitado e colocado na fila de processamento
			}

			// 'w' assume o índice do próximo vértice ligado a 'v' apoś o último valor de 'w'
			w = next(g, v, w); 
		}

		//Assim como a pré-visita, é comum haver uma pós-visita, em que seu conteúdo também varia de acordo com o problema
		//Exemplo de chamada: posVisit(g, v);
	}
}

//Define qual tipo de travessia será feita no grafo
void traverse(Graph* g, int v){
	int op;

	puts("Digite o tipo de travessia desejada:");
	puts("1. DFS");
	puts("2. BFS");

	//Leitura da operação
	scanf("%d", &op);

	//Caso a travessia escolhida seja a DFS
	if(op==1){
		DFS(g, v);
	}
	//Caso a travessia escolhida seja a BFS
	else{
		BFS(g, v);
	}

}

//Através de uma pilha, o topoSort ordena topologicamente um grafo à medida que são dados pop's na pilha resultante
void topoSort(Graph* g, int v){
	int w;

	//O vértice de origem é marcado como visitado
	setMark(g, v, VISITED);

	//'w' assume o índice do primeiro vértice ligado a 'v'
	w = first(g, v);

	//Enquanto houver vértices ligados 'v'
	while(w < n(g)){

		if(getMark(g, w) == UNVISITED){	//Caso o vértice encontrado ainda não tenha
			topoSort(g, w);				//sido visitado, ele é marcado como visitado
		}								//e o topoSort é chamado a partir dele
		
		// 'w' assume o índice do próximo vértice ligado a 'v' apoś o último valor de 'w'
		w = next(g, v, w);
	}

	pilha.push(v);

}

void graphTraverse(Graph* g){
	int v;

	for(v=0 ; v<n(g) ; v++){
		setMark(g, v, UNVISITED);
	}
	for(v=0 ; v<n(g) ; v++){
		if(getMark(g, v) == UNVISITED){

			traverse(g, v); //Traverse pode ser analisada de duas formas:
							//1. DFS (depth-first search == Busca em profundidade)
							//2. BFS (breadth-first search == Busca em largura)
		}
							
	}
}

void printMatriz(Graph* g){
	int i, j;

	for(i=0 ; i<n(g) ; i++){
		for(j=0 ; j<n(g) ; j++){
			printf("%d ", g->matrix[i][j]);
		}
		puts("");
	}
}


void printPilha(){

	while(!pilha.empty()){
		printf("%d ", pilha.top() + 1);
		pilha.pop();
	}
}

/*void shortestRoute(Graph* g, int begin, int end){
	int* predecessores = (int *) malloc(n(g)*sizeof(int));
	int hasFound = 0;


}	*/

int main(){
	int k;
	int m;

	while(scanf("%d %d", &k, &m), k+m){
		Graph* g;

		g = createGraph(k);

		while(m--){
			int i, j;
			scanf("%d %d", &i, &j);
			setEdge(g, i-1, j-1, 1);
		}

		for(int i=0 ; i<n(g) ; i++){
			if(getMark(g, i) == UNVISITED) topoSort(g, i);
		}
		printPilha();
		puts("");
		destructyGraph(g);
	}


	return 0;
}
