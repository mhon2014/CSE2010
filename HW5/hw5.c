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
#include "fakeRandHeight.c"
#include "StringParseList.h"

#define Max 2399 // max time
#define Min -1  //min time

typedef struct quadnode{ //quad node implementation
    struct quadnode *prev, *next, *above, *below;
    int time;
    char activity[50];
}node;

typedef struct{ //skiplist implementation
    node *ceiling;
    int height;
}skiplist;


// int getRandHeight(void);

node *empty_node_constructor(); //make an empty node with no values and return it
node *node_constructor(int arg_time, char *arg_activity); //parameterized constructor - make node with assgined values and return it
node * empty_list_constructor(); //just make the head and tail and just return the head since we only use the head for traversal
skiplist *skiplist_constructor(); //make the skiplist and returne the pointer
void parse_commands(StringList * arg_wordlist, skiplist *arg_skiplist); //function to do the commands
node *get(skiplist *arg_skiplist, int time); //get the first occurence of the node with the list if not return null
node *SkipSearch(skiplist *arg_skiplist, int time);//find the node and drop down to the bottom level
void addLevel(skiplist *arg_skiplist); //add level to the skiplist
node *insertAfterAbove(node* arg_prev, node* arg_below, int arg_time, char *arg_activity); //function to insert a new node above and relink them
void put(skiplist * arg_skiplist, int arg_time, char * arg_activity); //insert in the skiplist, if it exist just update the activity value
void delete(skiplist *arg_skiplist, int arg_time); //delete from the skiplist and all levels
node *ceilingEntry(skiplist *arg_list, int arg_time); //return the ceiling of the desired value
node *floorEntry(skiplist *arg_list, int arg_time); //return the floor of the desired value
void displayActivity(skiplist *arg_skiplist, int arg_time); //find the activity and print it, if not then print not found
void DisplayActivitiesBetweenTimes(skiplist *arg_skiplist, int arg_timeStart, int arg_timeEnd); //basically the submap function
void DisplayActivitiesFromStartTime(skiplist *arg_skiplist, int arg_timeStart);//print everything till the end from the start
void DisplayActivitiesToEndTime(skiplist *arg_skiplist, int arg_timeEnd); //print everything until an end point
void DisplayAllActivities(skiplist *arg_skiplist); //display all activity in the bottom level
void PrintList(node * arg_list); //function to just print list given a head node
void PrintSkipList(skiplist *arg_skiplist); //print the entire skiplist


// return the next number in the sequence, recycle the sequence if needed
// int getRandHeight()
// {
//     static int height[] = {0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 4, // sequence of height
//         0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0};
    
//     static int count=0;  // number of times getRandHeight() has been called
    
//     return height[count++ % 31];
// }

node *empty_node_constructor(){ //create empty node
    node *new_node = (node *)malloc(sizeof(node));
    if (new_node == NULL)
    {
        printf("malloc failed, memory is full\n");
        exit(-1);
    }
    //do pointer magic
    new_node->next = NULL;
    new_node->prev = NULL;
    new_node->below = NULL;
    new_node->above = NULL;
    return new_node;
}

node *node_constructor(int time, char * arg_activity){ //create node with values
    node *new_node = (node *)malloc(sizeof(node));
    if (new_node == NULL){
        printf("malloc failed, memory is full\n");
        exit(-1);
    }
    //assign values
    new_node->time = time;
    strcpy(new_node->activity, arg_activity);
    new_node->next = NULL;
    new_node->prev = NULL;
    new_node->below = NULL;
    new_node->above = NULL;
    return new_node;
}

node * empty_list_constructor(){ //create list -> head and tail
    node *listHead = empty_node_constructor();
    node *listTail = empty_node_constructor();
    
    //assign values for the min and max nodes
    listHead->time = Min;
    listTail->time = Max;
    listHead->next = listTail;
    listTail->prev = listHead;
    
    return listHead;
}

skiplist *skiplist_constructor(){ //initialize the skiplist and return the pointer
    skiplist *new_skiplist = (skiplist *)malloc(sizeof(skiplist));
    if(new_skiplist == NULL){
        printf("malloc failed, memory is full\n");
        exit(-1);
    }
    new_skiplist->ceiling = empty_list_constructor();
    new_skiplist->height = 0;
    return new_skiplist;
}

node *get(skiplist *arg_skiplist, int arg_time){
    if (arg_skiplist == NULL){
        printf("Error: Skiplist pointer is NULL\n");
        return NULL;
    }
    node * temp = arg_skiplist->ceiling;
    while(temp->below != NULL){ //go below
        temp = temp->below;
        while (arg_time >= temp->next->time){ //keep getting next
            temp = temp->next;
            if(temp->time == arg_time){
                return temp;// if found return it
            }
        }
    }
    return NULL; //not found thus return null
}

node *SkipSearch(skiplist *arg_skiplist, int arg_time){ //return the node at the bottom level for insertions
    if (arg_skiplist == NULL){
        printf("Error: Skiplist pointer is NULL\n");
        return NULL;
    }
    node * temp = arg_skiplist->ceiling;
    while(temp->below != NULL){
        temp = temp->below;
        while (arg_time >= temp->next->time){
            temp = temp->next;
        }
    }
    return temp;
}


void addLevel(skiplist *arg_skiplist){ //do some pointer magic
    arg_skiplist->ceiling->above = empty_list_constructor(); //make new level above
    arg_skiplist->ceiling->above->below = arg_skiplist->ceiling;//relink the head and tails
    arg_skiplist->ceiling->above->next->below = arg_skiplist->ceiling->next;
    arg_skiplist->ceiling = arg_skiplist->ceiling->above;
    arg_skiplist->height++; //increment height
}


node *insertAfterAbove(node* arg_prev, node* arg_below, int arg_time, char *arg_activity){
    node *new_node = node_constructor(arg_time, arg_activity);
    
    //make new node in the upper levels and link the nodes
    
    //do some pointer magic
    new_node->prev = arg_prev;
    if (arg_below != NULL){ //link the below and above
        arg_below->above = new_node;
        new_node->below = arg_below;
    }
    //do more pointer magic
    new_node->above = NULL;
    if (arg_prev != NULL){ //link the nodes prev and next in the upper level
        new_node->next = arg_prev->next;
        new_node->next->prev = new_node;
        arg_prev->next = new_node;
    }
    
    return new_node;
}

void put(skiplist *arg_skiplist, int arg_time, char * arg_activity){
    int height_counter = getRandHeight(); //get the heigh form the "random" height function
    if(arg_skiplist == NULL){
        printf("Error: Skiplist pointer is NULL\n");
        return;
    }
    node *temp = SkipSearch(arg_skiplist, arg_time); //find the node before the desired time so that we can insert
    if (temp->time == arg_time){ //if it already exist then just update it
        while(temp != NULL){
            strcpy(temp->activity, arg_activity);
            temp = temp->above;
        }
    }
    else { //do the crazy stuff
    node *current = NULL;
    int current_height = -1;
    while(current_height < height_counter){
        current_height++;
        if(current_height >= arg_skiplist->height){ //make new list if height counter is bigger then
            //add new level to skiplist
            addLevel(arg_skiplist);
        }
        //insert above and do some crazy pointer reassignments
        current = insertAfterAbove(temp, current, arg_time, arg_activity);
        //set to current to keep track so that we can relink the pointer below

        //backtrack to get the to list above
        while (temp->above == NULL){
          temp = temp->prev;
        }
        temp = temp->above;
    }
  }
}
void delete(skiplist *arg_skiplist, int arg_time){
    node *temp = get(arg_skiplist, arg_time);
    node *delete_node;
    if (temp == NULL){ //if not found
        printf("No time error");
    }
    while (temp != NULL){ //find the node, relink nodes and delete
        delete_node = temp;
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        temp = temp->below;
        if(delete_node->prev->time == Min && delete_node->next->time == Max){ // if the level is empty then delete it
          arg_skiplist->ceiling = delete_node->prev->below; //set the new starter node
          free(delete_node->prev); //free the min and max to get rid of the list
          free(delete_node->next);
          arg_skiplist->height--; //decrement the height
        }
        free(delete_node);
    }
}

node *ceilingEntry(skiplist *arg_list, int arg_time){
    return SkipSearch(arg_list, arg_time)->next; //get ceiling
}
node *floorEntry(skiplist *arg_list, int arg_time){
    return SkipSearch(arg_list, arg_time)->prev; //get floor

}

void displayActivity(skiplist *arg_skiplist, int arg_time){
    node *temp = get(arg_skiplist, arg_time); //find the activity and print
    if (temp == NULL){
        printf("No Activity Found\n");
    }
    else {
        printf("%s", temp->activity);
    }
}

void DisplayActivitiesBetweenTimes(skiplist *arg_skiplist, int arg_timeStart, int arg_timeEnd){
    node *start = ceilingEntry(arg_skiplist, arg_timeStart);
    node *end = ceilingEntry(arg_skiplist, arg_timeEnd);

    if (arg_timeStart > arg_timeEnd){//error checking
        printf("Start time cannot be bigger than end time\n");
        return;
    }
    if(start == end){ //if they both return the same thing then it doesn't exist
        printf("none");
        return;
    }
    while(start != end){ //just print
        printf("%d:%s ", start->time, start->activity);
        start = start->next;
    }
}
void DisplayActivitiesFromStartTime(skiplist *arg_skiplist, int arg_timeStart){
    node *start = ceilingEntry(arg_skiplist, arg_timeStart);
    while(start->time != Max) { //just print until the max value
        printf("%d:%s ", start->time, start->activity);
        start = start->next;
    }
}
void DisplayActivitiesToEndTime(skiplist *arg_skiplist, int arg_timeEnd){
    node *start = ceilingEntry(arg_skiplist, Min);
    while(start->time <= arg_timeEnd) { //print until the end time
        printf("%d:%s ", start->time, start->activity);
        start = start->next;
    }
}


void DisplayAllActivities(skiplist *arg_skiplist){
    node *temp = SkipSearch(arg_skiplist, Min);
    PrintList(temp); //print everything in the bottom level
}



void PrintList(node * arg_head){
    if(arg_head == NULL){
        printf("Error: List pointer is NULL.\n");
        return;
    }
    node * temp = arg_head->next;
    if (temp->time <= Min || temp->time >= Max) { //print nothing if there isn't anything between the min and max
        printf("empty");
    }
    while (temp->next != NULL){ //print everything in between
        printf("%d:%s ", temp->time, temp->activity);
        temp = temp->next;
    }
}

void PrintSkipList(skiplist *arg_skiplist){
    int height_counter = arg_skiplist->height;
    node *temp = arg_skiplist->ceiling;
    if(height_counter == 0){ //if list height is 0 then it's empty
      printf("List is empty\n");
      return;
    }
    while (height_counter >= 0){ //print the levels until you didn't reach bottom
        printf("\n(S%d) ", height_counter);
        PrintList(temp);
        temp = temp->below;
        height_counter--;
    }
    
}

void parse_commands(StringList *arg_wordlist, skiplist *arg_skiplist){
    int time = 0, start = 0, end = 0; //some variable for time
    char *string_command = delete_front(arg_wordlist); //first one is always the command

    //compare the commands and do the commands
    if (strcmp(string_command, "AddActivity") == 0){
        time = atoi(delete_front(arg_wordlist));
        char *name = (delete_front(arg_wordlist));
        put(arg_skiplist, time, name);
    }
    else if (strcmp(string_command, "DeleteActivity") == 0){
        time = atoi(delete_front(arg_wordlist));
        delete(arg_skiplist, time);
    }
    else if (strcmp(string_command, "PrintSkipList") == 0){
        PrintSkipList(arg_skiplist);
    }
    else if (strcmp(string_command, "DisplayActivity") == 0){
        time = atoi(delete_front(arg_wordlist));
        displayActivity(arg_skiplist, time);
    }
    else if (strcmp(string_command, "DisplayActivitiesBetweenTimes") == 0){
        start = atoi(delete_front(arg_wordlist));
        end = atoi(delete_front(arg_wordlist));
        DisplayActivitiesBetweenTimes(arg_skiplist, start, end);
    }
    else if (strcmp(string_command,"DisplayActivitiesFromStartTime") == 0){
        start = atoi(delete_front(arg_wordlist));
        DisplayActivitiesFromStartTime(arg_skiplist, start);
    }
    else if (strcmp(string_command,"DisplayActivitiesToEndTime") == 0){
        end = atoi(delete_front(arg_wordlist));
        DisplayActivitiesToEndTime(arg_skiplist, end);
    }
    else if (strcmp(string_command, "DisplayAllActivities") == 0){
        DisplayAllActivities(arg_skiplist);
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
    StringList *words = StringList_constructor(); //linked list of words
    skiplist *SkipList = skiplist_constructor(); //skiplist
    
    fileptr = fopen(argv[1], "r");
    
    if (fileptr == NULL){
        printf("Error file not found");
        exit(0);
    }
    
    while(getline(&line, &len_of_line, fileptr) >= 0){
        //get the line and print it out
        strtok(line, "\r\n");
        printf("%s ", line);
        //tokenize the line into words
        token = strtok(line, " ");
        
        //loop until no more words are found
        while(token != NULL) {
            //add new words to end of the list
            add_end(words, token);
            token = strtok(NULL, " ");
        }
        
        parse_commands(words, SkipList);
        printf("\n");
        StringList_destructor(words);
    }
    //didn't make destructor for skiplist because I don't like it.
    fclose(fileptr);
    
}

