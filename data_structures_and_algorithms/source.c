#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 2415
typedef struct node{
	int parent;
	int child;
}NODE;

typedef struct que{
	int array[1200];
	int p;
	int r;
}QUE;

void isLinked(char wordList[SIZE][6], short **matrix, char word1[6], char word2[6]);
void enque(int value, QUE *q);
int deque(QUE *q);
short isQueEmpty(QUE *q);
int breadthFirstSearch(char wordList[SIZE][6], short **matrix, int indexWord1, int indexWord2);
void displayPath(char wordList[SIZE][6], NODE *node, int child);


//void displayPath(char transition[][6], )

int main(int argc, char *argv[]) {
	
	int i; // loop variable
	int j; // loop variable
	int k; // loop variable
	int matchCount; // counts the matches for 2 word - used for creating adjacencyMatrix 
	int indexWord1; // index of entered word1 in word list
	int indexWord2; // index of entered word2 in word list
	int transitionCount; // holder for return of breadthFirstSearch function which returns distance of shortest path
	short choose; // switch - case variable which used for creating menu screen
	short **adjacencyMatrix; // adjacency matrix of all words
	char word1[6]; // entered word1
	char word2[6]; // entered word2
	char word[SIZE][6]; // word list
	FILE *f; // text file
	
	adjacencyMatrix = malloc(sizeof(short*)*SIZE);
	for(i = 0; i < SIZE; i++)
		adjacencyMatrix[i] = malloc(sizeof(short)*SIZE);	
	
	f = fopen("words.txt", "r");
	i = 0;
	while(!feof(f)) // dosyadan kelime okuma
		fscanf(f, "%s", word[i++]);	
			
	for(i = 0; i < SIZE; i++)
		for(j = 0; j < SIZE; j++){
			matchCount = 0;
			for(k = 0; k < 5; k++)
				if(word[i][k] == word[j][k])
					matchCount++;
			if(matchCount == 4){
				adjacencyMatrix[i][j] = 1;
			}else{
				adjacencyMatrix[i][j] = 0;
			}			
		}
	fclose(f);
	choose = 1;
	while(choose){
		printf("ENTER A OPERATION NUMBER : ");
		printf("\nShow all words                    : 1");
		printf("\nIs linked                         : 2");
		printf("\nFind a transition between 2 words : 3");
		printf("\nQuit                              : 0\n");
		scanf("%d",&choose); 
		switch(choose){
			case 1 : {
				printf("ALL WORDS");
				for(i = 0; i < SIZE; i++)
					printf("\n%s",word[i]);
				printf("\n");
				break;
			}case 2 : {
				printf("Enter 2 words : \n");
				scanf("%s%s", word1, word2);
				isLinked(word, adjacencyMatrix, word1, word2);	
				break;
			}case 3 : {
				printf("Enter 2 words : \n");
				scanf("%s%s", word1, word2);
				indexWord1 = 0;
				indexWord2 = 0;
				while( strcmp(word1, word[indexWord1]) && indexWord1 < SIZE)
					indexWord1++;
				while( strcmp(word2, word[indexWord2]) && indexWord2 < SIZE)
					indexWord2++;
				if(indexWord1 >= SIZE || indexWord2 >= SIZE){
					printf("Words not found in the file.\n");
					break;
				}
				transitionCount = breadthFirstSearch(word, adjacencyMatrix, indexWord1, indexWord2);
				if(transitionCount != -1){	
					printf("\n-----NUM OF STEPS-----\nThere is transition. Number of steps = %d\n", transitionCount);	
				}
				else
					printf("\n-----NUM OF STEP-----\nThere is no transition from one word to another.\n");
				break;
			}case 0 : {
				printf("Quitting...");
				break;
			}default : printf("Wrong operation number.\n");
		}
	}
	
	/*
	for(i = 0; i < SIZE; i++)
		printf("%s\n",word[i]);*/
	
	//isLinked(word, adjacencyMatrix);

	
	return 0;		
}

void isLinked(char wordList[SIZE][6], short **matrix, char word1[6], char word2[6]){

	int i; // loop variable
	int j; // loop variable
	for(i = 0; i < SIZE; i++)
		if( !strcmp(wordList[i], word1) )
			for(j = 0; j < SIZE; j++)
				if( !strcmp(wordList[j], word2) ){
					if(matrix[i][j] == 1)
						printf("Words are linked.\n");
					else
						printf("Words are not linked.\n");
					return;
				}		
	printf("Words not found in the file.\n");
}

int  breadthFirstSearch(char wordList[SIZE][6], short **matrix, int indexWord1, int indexWord2){
	
	QUE *que = (QUE*) malloc (sizeof(QUE)); // queue for bfs
	que->p = 0;
	que->r = 0;
	NODE *node = (NODE*) malloc(sizeof(NODE)); // child - parent relation for printing the path of shortest bfs
	node->child = indexWord1;
	node->parent = indexWord1;
	int *distance = (int*) calloc(1, sizeof(int) * SIZE); // distance array for each word
	int x; // holder of enqueued value
	int i; // loop variable
	int j; // loop variable
	short visited[SIZE]; // array for control of that particular word has been used or not.
	
	for(i = 0; i < SIZE; i++)
		visited[i] = 0;
	enque(indexWord1, que);
	visited[indexWord1] = 1;
	j = 0;
	printf("-----DEQUEUED WORDS-----");
	while( (que->p < que->r) && (x != indexWord2) ){		
		x = deque(que);	
		printf("\nDequeued word : %s", wordList[x]);
		if(x != indexWord2)
			for(i = 0; i < SIZE; i++)
				if( (visited[i] == 0) && (matrix[x][i] == 1) ){	
					j++;
					node = (NODE*)realloc (node, (j+1) * sizeof(NODE) );
					node[j].parent = x;
					node[j].child = i;
					visited[i] = 1;
					distance[i] = distance[x] + 1;
					enque(i, que);				
				}									
	}	
	if(x == indexWord2){
		printf("\n-----SHORTEST PATH-----\n%s", wordList[node[0].child]);
		displayPath(wordList, node, x);
		return distance[x];
	}	
	return -1;	// it means there is no connection.
}

void enque(int value, QUE *q){
	q->array[q->r ++] = value;
}

int deque(QUE *q){
	if(q->r == q->p){
		printf("\nQueue is empty.");
		return -1; // que is empty
	}
	return q->array[q->p ++];
}

short isQueEmpty(QUE *q){
	if(q->r == q->p)
		return 1;
	return 0;
}

void displayPath(char wordList[SIZE][6], NODE *node, int child){
	if(child != node[0].child){
		int j = 0;
		while(node[j].child != child )	
			j++;
		displayPath(wordList, node, node[j].parent);
		printf("->%s", wordList[node[j].child]);
	}
}
