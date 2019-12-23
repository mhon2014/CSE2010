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

struct vertex{
  char user[50];
  // struct nodes *prev, *next;
  List *neighbors;
};

struct node{
  Vertex vertexValue;
  Node *prev, *next;
};

struct list{
  int size;
  Node *head, *tail;
};

typedef struct{
  List *vertices;
}graph;

//node typedef
//list typedef for storage.]

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

