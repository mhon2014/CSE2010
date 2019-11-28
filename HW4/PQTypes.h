#ifndef PQTYPES_H
#define PQTYPES_H

#define MAXCOUNT 100

typedef struct{
  int time; //time for when bid was set
  char name[50]; //name of the bidder
  double price; //price that the bidder offered
  int quantity; //quantity that the bidder wants
}PQItem;

// typedef PQItem PQArray[MAXCOUNT+1]; //ignore this, just the book implementation

typedef struct
{
    int count; //size of total amount of elements
    PQItem array[MAXCOUNT+1]; //array for the priority queue
}PriorityQueue;


#endif