/*

  Author: Michael Hon
  Email: mhon2014@my.fit.edu
  Course: cse2010
  Section: E4 / 14
  Description: HW5 skiplist

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "StringParseList.h"

typedef struct{
  int time;
  char * log;
}activity;

typedef struct quadnode{
  struct quadnode *prev, *next, *above, *below;
  activity activity;
}node;


typedef struct{
    node * head, * tail;
    // struct lists *above, *below;
    int current_level;
    int size;
}list;

typedef struct{
  list * ceiling, *floor;
  int height;
}skiplist;


int getRandHeight();

node * node_constructor();
list * list_constructor();
skiplist * skiplist_constructor();
void parse_commands(StringList * arg_list);
void get(int arg_time);
void put(skiplist * arg_skiplist, activity arg_activity);
void delete(int arg_time);
list ceilingEntry(skiplist arg_list);
list floorEntry(skiplist arg_list);
list subMap(int arg_time_low, int arg_time_high);
void PrintList(list *arg_list);
void PrintSkipList(skiplist *arg_skiplist);


// return the next number in the sequence, recycle the sequence if needed
int getRandHeight()
{
  static int height[] = {0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 4, // sequence of height
                         0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0};
  
  static int count=0;  // number of times getRandHeight() has been called 

  return height[count++ % 31];
}

node * empty_node_constructor(){
  node * new_node = (node *)malloc(sizeof(node));
  if (new_node == NULL)
  {
    printf("malloc failed, memory is full\n");
    exit(-1);
  }
  new_node->activity.log = NULL;
  new_node->next = NULL;
  new_node->prev = NULL;
  new_node->below = NULL;
  new_node->above = NULL;
  return new_node;
}

node * node_constructor(activity arg_activity){
  node * new_node = (node *)malloc(sizeof(node));
  if (new_node == NULL){
    printf("malloc failed, memory is full\n");
    exit(-1);
  }
  new_node->activity = arg_activity;
  new_node->next = NULL;
  new_node->prev = NULL;
  new_node->below = NULL;
  new_node->above = NULL;
  return new_node;
}

list * empty_list_constructor(){
  list * new_list = (list *)malloc(sizeof(list));
  if(new_list == NULL){
    printf("malloc failed, memory is full\n");
    exit(-1);
  }
  new_list->head = empty_node_constructor();
  new_list->head->activity.time = -INFINITY;
  new_list->tail = empty_node_constructor();
  new_list->tail->activity.time = INFINITY;
  new_list->size = 2;
  return new_list;
}

skiplist * skiplist_constructor(){
  skiplist * new_skiplist = (skiplist *)malloc(sizeof(skiplist));
  if(new_skiplist == NULL){
    printf("malloc failed, memory is full\n");
    exit(-1);
  }
  new_skiplist->ceiling = empty_list_constructor();
  new_skiplist->floor = empty_list_constructor();
  return new_skiplist;
}

void put(skiplist *arg_skiplist, activity arg_activity){
  int height_counter = getRandHeight();
  if(arg_skiplist == NULL){
    printf("Error: Skiplist pointer is NULL");
    return;
  }
  while (height_counter >= 0){
    //insert at the level and continue on the list, start at the bottom then go up
    //while nothing found go down and add then add back up and
    //decrement counter and keep going down
    //if counter is at the bottom then just add it where it is
  }
}

void PrintList(list *arg_list){
  node * temp = arg_list->head;
  if(arg_list = NULL){
    printf("Error: List pointer is NULL.");
    return;
  }
  while (temp != NULL){
    printf("%d:%s ", temp->activity.time, temp->activity.log);
  }
}

void PrintSkipList(skiplist *arg_skiplist){
  int height_counter = getRandHeight();
  while (height_counter >= 0){
    
  }

}

void parse_commands(StringList *arg_list){
  char *string_command = delete_front(arg_list);
    if (strcmp(string_command, "AddActivity") == 0){
      printf("AddActivity\n");
          printf("%d\n", getRandHeight());
    }
    else if (strcmp(string_command, "DeleteActivity") == 0){
      printf("DeleteActivity\n");
    }
    else if (strcmp(string_command, "PrintSkipList") == 0){
      printf("PrintSkipList\n");
    }
    else if (strcmp(string_command, "DisplayActivity") == 0){
      printf("DisplayActivity\n");
    }
    else if (strcmp(string_command, "DisplayActivitiesBetweenTimes") == 0){
      printf("DisplayActivitiesBetweenTimes\n");
    }
    else if (strcmp(string_command,"DisplayActivitiesFromStartTime") == 0){
      printf("DisplayActivitiesFromStartTime\n");
    }
    else if (strcmp(string_command,"DisplayActivitiesToEndTime") == 0){
      printf("DisplayActivitiesToEndTime\n");
    }
    else if (strcmp(string_command, "DisplayAllActivities") == 0){
      printf("DisplayAllActivities\n");
    }
    else {
      printf("Error: no such command exist\n");
    }
}

/*
  Description for each function, parameter, and return value (if any)
 */
int main(int argc, char* argv[])
{
  
  FILE *fileptr; //fileptr variable
  char *line = NULL; //used to read entire line
  char *token = NULL; //tokens for seperating the words
  char *linetoken = NULL;
  size_t len_of_line = 0; //to save the length of the line for getline
  double minimum_price = 0; //set the minimum price when the update command is called
  StringList *words = StringList_constructor();

  fileptr = fopen(argv[1], "r");

  if (fileptr == NULL){
    printf("Error file not found");
    exit(0);
  }

  while(getline(&line, &len_of_line, fileptr) >= 0){
    //get the line and print it out
    strtok(line, "\r\n");
    printf("%s \n", line);

    //tokenize the line into words
    token = strtok(line, " ");

    //loop until no more words are found
    while(token != NULL) {
        //add new words to end of the list
        add_end(words, token);
        token = strtok(NULL, " ");

    }

    //the top of the list is the string command
    parse_commands(words);
    StringList_destructor(words);
  }

  /*
    description of declared variables
   */


  /*
    description for each "block" (about 5 lines of instructions)
   */
  
}


// put(skiplist, ...) 
// uses getRandHeight()

