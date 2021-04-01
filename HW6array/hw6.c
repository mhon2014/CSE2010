/*

  Author:
  Email:
  Course:
  Section:
  Description:




 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "StringParseList.h"

/*
  Description of the function, parameter, and return value (if any)
 */

typedef struct node Node;
typedef struct vertex Vertex;
typedef struct list List;

// struct vertex{
//   char user[50];
//   // struct nodes *prev, *next;
//   List *neighbors;
// };

// struct node{
//   Vertex vertexValue;
//   Node *prev, *next;
// };

// struct list{
//   int size;
//   Node *head, *tail;
// };

// typedef struct{
//   List *vertices;
// }graph;

//node typedef
//list typedef for storage.]

typedef struct{
  int size;
  bool **AdjacencyMatrix;
}graph;

void initializeG(graph *arg_graph, int arg_size){
  arg_graph->size = arg_size;
  arg_graph->AdjacencyMatrix = (bool**)malloc(sizeof(bool)*arg_size);
  for(int i = 0; i < arg_size; i++){
    // printf("size:%d ", );
    arg_graph->AdjacencyMatrix[i] = (bool*)malloc(sizeof(bool)*(i+1));
    for(int j = 0; j < i; j++ ){
      arg_graph->AdjacencyMatrix[i][j] = false;
    }
  }
}

void printgraph(graph *arg_graph){
    for(int i = 0; i < arg_graph->size; i++){
      for(int j = 0; j < i+1; j++){
        printf("%d ", arg_graph->AdjacencyMatrix[i][j]);
      }
      printf("\n");
  }
}


int main(int argc, char* argv[])
{
  /*
    description of declared variables
   */

  FILE *fileptr;
  char *linetoken;
  char *token;
  size_t linelength = 0;
  StringList *words = StringList_constructor();
  
  graph friendlist;

  initializeG(&friendlist, 12);
  printgraph(&friendlist);

  fileptr = fopen(argv[1], "r");

  if (fileptr == NULL){
    printf("Error file not found.");
    exit(0);
  }

  while(getline(&linetoken, &linelength, fileptr) >= 0){
    strtok(linetoken, "\r\n");
    printf("%s ", linetoken);
    printf("\n");
    
    token = strtok(linetoken, " ");

    while(token != NULL){
      add_end(words, token);
      token = strtok(NULL, " "); 
    }
    // print_list(words);
    StringList_destructor(words);
    //parse the string
  }

  
  /*
    description of each "block" (about 5 lines of instructions)
   */
  return 0;
}

