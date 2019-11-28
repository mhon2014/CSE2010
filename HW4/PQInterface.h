#include "PQTypes.h"
#include <stdbool.h>

#ifndef PQINTERFACE_H
#define PQINTERFACE_H

void printarray(PriorityQueue *arg_PQ); //used for debugging
void PQheapify(PriorityQueue *arg_PQ, int arg_index); //heapify function for ordering
void PQheapsortUp(PriorityQueue *arg_PQ); //calls the heapify function to all internal nodes starting bottom up
void PQheapsortDown(PriorityQueue *arg_PQ);//heapify top to bottom internal nodes
void PQinitialize(PriorityQueue *arg_PQ); //set the size to 0
void PQinsert(PriorityQueue *arg_PQ, PQItem arg_entry); //insert into the datastructure
PQItem PQremoveMax(PriorityQueue *arg_PQ); // return and remove entry with the maximum key
PQItem PQgetMax(PriorityQueue *arg_PQ); // return entry with the maximum key
bool PQfull(PriorityQueue *PQ); //check if PQ is full
bool PQempty(PriorityQueue *PQ); //check if PQ is empty

#endif