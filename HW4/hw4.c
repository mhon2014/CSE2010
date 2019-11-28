/*

  Author: Michael Hon
  Email: mhon2014@my.fit.edu
  Course: CSE2010
  Section: E4/14
  Description: Priority queue assignment using heapsort

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "StringParseList.h"
#include "PQInterface.h"


int main(int argc, char* argv[])
{
  /*
    description of declared variables
   */
  PriorityQueue bids; //PQ variable
  FILE *fileptr; //fileptr variable
  char *line = NULL; //used to read entire line
  char *token = NULL; //tokens for seperating the words
  char *linetoken = NULL;
  size_t len_of_line = 0; //to save the length of the line for getline
  double minimum_price = 0; //set the minimum price when the update command is called
  StringList *words = StringList_constructor();

  //fucntion to initialize the size of the queue
  PQinitialize(&bids);
  // printf("This is %d", bids.count);

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

    //the top of the list is the string command
    char *string_command = delete_front(words);


    //compare the string to see which commands are used
    if(strcmp(string_command, "EnterBid") == 0){
      //initialize the entry
      PQItem new_entry;
      //set the values of the entry
      new_entry.time = atoi(delete_front(words));
      strcpy(new_entry.name, delete_front(words));
      new_entry.price = atof(delete_front(words));
      new_entry.quantity = atoi(delete_front(words));

      // insert in the Pqueue
      PQinsert(&bids, new_entry);
    }
    else if(strcmp(string_command, "UpdateMinimumAcceptablePrice") == 0){
      delete_front(words);
      //set the minimum price for bidding
      minimum_price = atof(delete_front(words));
      printf("\n");
    }
    else if(strcmp(string_command, "SellOneItem") == 0){
      //check if the price is bigger than the minimum price
      if (PQgetMax(&bids).price >= minimum_price){
        PQItem item = PQremoveMax(&bids);

        printf("%s %0.2f\n", item.name, item.price);
      }
      else {
        //if it's lower than the minimum price then throw error
        printf("HightestBiddingPriceIsTooLow\n");
      }
    }
    else if(strcmp(string_command, "DisplayHighestBid") == 0){
      //print the highest priority entry in the structure which is at the root of the heap
      PQItem temp = PQgetMax(&bids);
      printf("%s %d %0.2f %d\n", temp.name, temp.time, temp.price, temp.quantity);

    }

    //used to empty the string just incase there was extra lingering pointers to avoid memory leaks
    StringList_destructor(words);

  }
  fclose(fileptr);

  return 0;
}

