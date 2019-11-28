#include "PQInterface.h"
#include <stdio.h>
#include <math.h>

#ifndef PQIMPLEMENTATION_C
#define PQIMPLEMENTATION_C


//used for debugging purposes 
void printarray(PriorityQueue *arg_PQ){
    for (int i = 1; i <= arg_PQ->count; i++){
        printf("%.2f ", arg_PQ->array[i].price);
    }
}

void PQheapify(PriorityQueue *arg_PQ, int arg_index){
    int highestpriorityindex = arg_index; //initialize priority child's to current index
    int leftchildindex = 2*arg_index; //left child index
    int rightchildindex = 2*arg_index+1; //right child index
    PQItem highestpriority = arg_PQ->array[arg_index]; //initialize highest priority entry to the current indexed entry

    //if the childs are out of the size of the structure then just return
    if(leftchildindex > arg_PQ->count && rightchildindex > arg_PQ->count){
        return;
    }

    //check to see if left child is bigger
    if(leftchildindex <= arg_PQ->count && arg_PQ->array[leftchildindex].price >= highestpriority.price){
        if(fabs(arg_PQ->array[leftchildindex].price - highestpriority.price) < 0.001){ //check for time if price are the same use fabs to compare doubles
            if(arg_PQ->array[leftchildindex].time < highestpriority.time){
                //set the highest priority to which ever was earlier
                highestpriority = arg_PQ->array[leftchildindex];
                highestpriorityindex = leftchildindex;
            }
        }
        else {
            //just set the highest priority if the price is simply larger
            highestpriority = arg_PQ->array[leftchildindex];
            highestpriorityindex = leftchildindex;
        }
    }

    //check right child
    if(rightchildindex <= arg_PQ->count && arg_PQ->array[rightchildindex].price >= highestpriority.price){
        if(fabs(arg_PQ->array[rightchildindex].price - highestpriority.price) < 0.001){ //check for time if price are the same use fabs to compare doubles
            if(arg_PQ->array[rightchildindex].time < highestpriority.time){
                //set the highest priority to which ever was earlier
                highestpriority = arg_PQ->array[rightchildindex];
                highestpriorityindex = rightchildindex;
            }
        }
        else {
            //just set the highest priority if the price is simply larger
            highestpriority = arg_PQ->array[rightchildindex];
            highestpriorityindex = rightchildindex;
        }
    }

    //if the initial priority index was changed then swap the entries.
    if(highestpriorityindex != arg_index){
        arg_PQ->array[highestpriorityindex] = arg_PQ->array[arg_index];
        arg_PQ->array[arg_index] = highestpriority;
    }

}

//iteratively heapify starting from the bottom up of all the internal node
void PQheapsortUp(PriorityQueue *arg_PQ){
    for(int i = ((arg_PQ->count)/2);i > 0; i--){
        PQheapify(arg_PQ, i);
    }
}

//iteratively heapify starting from the top to bottom of all the internal node
void PQheapsortDown(PriorityQueue *arg_PQ){
    for(int i = 1;i < ((arg_PQ->count)/2); i++){
        PQheapify(arg_PQ, i);
    }
}

//initialize the count
void PQinitialize(PriorityQueue *arg_PQ){
    arg_PQ->count = 0;
}
//insert into the datastructure
void PQinsert(PriorityQueue *arg_PQ, PQItem arg_entry){
    //insert and then heapify
    if (PQfull(arg_PQ)) {
        printf("Priority Queue is full");
        return;
    }
    arg_PQ->array[arg_PQ->count+1] = arg_entry;
    arg_PQ->count++; //increment the count

    PQheapsortUp(arg_PQ);
    // printarray(arg_PQ);
    printf("\n");
}

//remove the entry with highest priority
PQItem PQremoveMax(PriorityQueue *arg_PQ) {
    if (PQempty(arg_PQ)){
        printf("Priority Queue is empty.");
    }
    PQItem return_item = arg_PQ->array[1];
    if(arg_PQ->array[1].quantity > 1) { //if there is more than 1 quantity then decrement the quantity
        arg_PQ->array[1].quantity--;
    }
    else { //if the quantity is 1 then remove and heapify
        arg_PQ->array[1] = arg_PQ->array[arg_PQ->count];
        arg_PQ->count--;
        PQheapsortDown(arg_PQ);

    }
    return return_item;
}

//get the item with highest priority
PQItem PQgetMax(PriorityQueue *arg_PQ){
    if (PQempty(arg_PQ)){
        printf("Priority Queue is empty.");
    }
    return arg_PQ->array[1];
} // return entry with the maximum key

//return true if PQ is full
bool PQfull(PriorityQueue *arg_PQ){
    if (arg_PQ->count == MAXCOUNT) {
        return true;
    }
    return false;
}

//return true if PQ is empty
bool PQempty(PriorityQueue *arg_PQ){
    if (arg_PQ->count == 0) {
        return true;
    }
    return false;
}

#endif