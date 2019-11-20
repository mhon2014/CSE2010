/*
 
 Author: Michael Hon
 Email: mhon2014@my.fit.edu
 Course: CSE2010
 Section: E4/ 14
 Description: HW2 finding shorted path on permutation problem
 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

/*
NODE struct that has x,y coordinates, name, the next and previous nodes
and the current distance from the previous node if it is not null
*/
typedef struct node{
    int x, y;
    char name[50];
    struct node *next, *prev;
    double distance;
}position;

/*
 Doubly linked list with head, tail and total distance that is calculated as you enqueue
 */
typedef struct list{
    position *head, *tail;
    int size;
    double total_distance;
}linkedlist;

void print_list(linkedlist *arg_list);
position *position_constructor(char* arg_name, int arg_x, int arg_y);
void enqueue(linkedlist *arg_list, char* arg_name, int arg_x, int arg_y);


/*
 Function to print the elements in the list that is passed as parameter
 */
void print_list(linkedlist *arg_list){
    position *temp = arg_list->head;
    while(temp != NULL){
        printf("%s %d %d %.2f\n", temp->name, temp->x, temp->y, temp->distance);
        temp = temp->next;
    }
}

/*
 Helper function to create position node and return a pointer with values set up based on the parameters
 */
position *position_constructor(char* arg_name, int arg_x, int arg_y){
    position *new_node = (position*)malloc(sizeof(position)); //make new node pointer
    strcpy(new_node->name, arg_name);                         //set all the values in the object
    new_node->x = arg_x;
    new_node->y = arg_y;
    new_node->prev = NULL;
    new_node->next = NULL;
    new_node->distance = 0;
    return new_node;
}

/*
 Helper function to create linkedlist and return the object
 */
linkedlist linkedlist_constructor(){
    linkedlist new_list;
    new_list.head = new_list.head = NULL;   //set all of the values
    new_list.size = 0;
    new_list.total_distance = 0;
    return new_list;
}

/*
 Helper function to return a newly copied linkedlist
 */
linkedlist linkedlist_copy(linkedlist *arg_list){
    linkedlist new_list = linkedlist_constructor();
    if(arg_list == NULL){
        return new_list;
    }
    position *new_node= arg_list->head;
    while (new_node != NULL ){
        enqueue(&new_list, new_node->name, new_node->x, new_node->y);
        new_node = new_node->next;
    }
    return new_list;
}


/*
 enqueue to to end of the list and using the position constructor helper function to build the position object
 */
void enqueue(linkedlist *arg_list, char* arg_name, int arg_x, int arg_y){ //put at tail
    position *new_node =  position_constructor(arg_name, arg_x, arg_y);
    if(arg_list->size == 0) {
        new_node->distance = 0;
        arg_list->head = arg_list->tail = new_node;
    }
    else {
        new_node->prev = arg_list->tail;    //enqueueing to the tail of the list
        arg_list->tail->next = new_node;
        arg_list->tail = arg_list->tail->next;
        new_node->distance = sqrt(pow((new_node->x - new_node->prev->x), 2)+ pow((new_node->y - new_node->prev->y), 2));
                        //updating the NODE distance from the previous nodes coordinates using Euclidean Distance
        
        arg_list->total_distance += new_node->distance; //update the TOTAL distance of the list
    }
    arg_list->size++;
}

/*
 pop the head of the list and set the new head, return an object of the popped head.
 */
position pop_dequeue(linkedlist *arg_list){
    position *temp = arg_list->head;
    position node_temp = (*temp);
    if(arg_list->size == 1){
        free(temp);
    }
    else {
        arg_list->head = arg_list->head->next;
        arg_list->head->prev = NULL;
        arg_list->head->distance = 0;               //if there is no previous then the NODE distance is 0 since it's the beginning
        free(temp);
    }
    arg_list->total_distance -= node_temp.distance; //decrease TOTAL distance of the LIST based on the removed object
    arg_list->size--;                               //decrease size of list
    node_temp.next = NULL;
    return node_temp;
}

/*
 remove the end of the specified list in the parameter and return the object that was deleted
 */
position delete_end(linkedlist *arg_list){
    position *temp = (arg_list)->tail;
    position node_temp = (*temp);
    if(arg_list->size == 1){
        free(temp);
    }
    else {
        arg_list->tail = arg_list->tail->prev;
        arg_list->tail->next = NULL;
        free(temp);
    }
    arg_list->total_distance -= node_temp.distance; //decrease TOTAL distance of the LIST based on the removed object
    arg_list->size--;                       //decrease size of list
    return node_temp;
}

/*
 return the top of the list
 */
position *top(linkedlist *arg_list){
    return arg_list->head;
}

/*
 boolean function to check to see if list is empty
 */
bool isEmpty(linkedlist arg_list){
    if (arg_list.size > 0){
        return false;
    }
    else {
        return true;
    }
}


/*
 free all the allocated memory
 */
void destructor(linkedlist *arg_list){
    position *temp;
    if (arg_list != NULL){
        return;
    }
    while (arg_list->head) { //delete till everything is null
        temp = arg_list->head;
        arg_list->head = arg_list->head->next;
        arg_list->size--;
        free(temp);
        
    }
}

/*
 Recursive function that will find all the permutations paths
 */
void pathfinder(linkedlist *arg_path, linkedlist *remainders, linkedlist *previous_path) {
    for (int i = 0; i < remainders->size; i++) {
        position remainder_top = pop_dequeue(remainders);
        enqueue(arg_path, remainder_top.name, remainder_top.x, remainder_top.y);
        if (isEmpty(*remainders)){                                  //base case, if the current set is empty then check the sequence
            position top_position = *top(arg_path);
            enqueue(arg_path, top_position.name, top_position.x, top_position.y);

            if (isEmpty(*previous_path)){      //if previous path is empty then set the current sequence to it for comparing other routes
                *previous_path = linkedlist_copy(arg_path);
            }
            else if (roundf(arg_path->total_distance * 100/100) < roundf(previous_path->total_distance * 100/100)) { //comparing two double values with rounding, since comparing two floating numbers is dangerous.
                destructor(previous_path);
                *previous_path = linkedlist_copy(arg_path);
//                print(previous_path);
            }

//            print_list(arg_path);
//            printf("%.2f\n\n", arg_path->total_distance);
            delete_end(arg_path);
        }
        
        else {
                pathfinder(arg_path, remainders, previous_path);
        }
        remainder_top = delete_end(arg_path);
        enqueue(remainders, remainder_top.name, remainder_top.x, remainder_top.y);
    }
}


int main(int argc, char* argv[])
{
    char *filename = argv[1]; //command line argument file
    char line[50];          //used for line reading
    char name[50];          //used for getting the name string
    int x, y, size;         //used for x and y coordinates
                            //size is used for the first line of the text which specifies the number of locations
    FILE *fileread;         //FILE  pointer for reading the file
    
    linkedlist positionlist = linkedlist_constructor();     //used for the "sets" in the recursive function
    linkedlist pathlist = linkedlist_constructor();         //used for the sequence in the recursive function
    linkedlist previouslist = linkedlist_constructor();     //used for the previous sequences to get the shortest distance in the function
                                                            //previouslist is also the TRUE shortest path at the end of the algorithm
    
    fileread = fopen(filename, "r");
    
    if(!fileread){                                          //basic error file
        printf("Error");
        return 0;
    }
    
    fgets(line, sizeof(line), fileread); //get first line for the number of positions
    sscanf(line, "%d", &size);  //set the number in a variable to be used for the array size
    position sortarray[size-1];      //array used to sort the positions in alpabetical order so that the permutations runs in a alpbetical order
                                //size-1 because we don't need to sort the first position which is packing stations
    
    
    position packing_station;  //variable to grab packing station
    for(int i = 0; i < size; i++) {
        fgets(line, sizeof(line), fileread);
        sscanf(line, "%s %d %d", name, &x, &y);
        if (i == 0) {
            packing_station = *position_constructor(name, x, y);    //if it's the first line then it's the packing station
        }
        else {
            sortarray[i-1] = *position_constructor(name, x, y);      //else add everything to the array to be used for sorting
        }
    }
    
    enqueue(&pathlist, packing_station.name, packing_station.x, packing_station.y); //set the packing station to the top of a sequence path
    
    //bubble sort to enforce the alphabetical order
    for (int i = 1; i < size-1; i++){
        for (int j = 0; j < size-i-1; j++){
            if (strcmp(sortarray[j].name,sortarray[j+1].name) > 0){
                position temp = sortarray[j];
                sortarray[j] = sortarray[j+1];
                sortarray[j+1] = temp;

            }
        }
    }
    
    //enqueue the sorted array now in the permutation algorithm
    for(int i = 0; i < size-1; i++) {
        enqueue(&positionlist, sortarray[i].name, sortarray[i].x, sortarray[i].y);
    }
    
    //start of the permutation algorithm
    pathfinder(&pathlist, &positionlist, &previouslist);
    
    //print the list of the
    print_list(&previouslist);
    printf("%.2f\n", previouslist.total_distance);
    
    //clear all used memory
    destructor(&positionlist);
    destructor(&pathlist);
    destructor(&previouslist);
    
    return 0;
}
