#ifndef STRINGPARSELIST_H
#define STRINGPARSELIST_H

#define wordsize 256

typedef struct wordnode{ //node containing the string
    char *word;
    struct wordnode *prev, *next;
}StringNode;

typedef struct listword{ //list
    StringNode *head, *tail;
    int size;
}StringList;

bool ListIsEmpty(StringList *arg_list); //returns true if list is empty
void print_list(StringList *arg_list); //helper function to print list
int ListSize(StringList *arg_list); //return list size
StringNode *StringNode_constructor(char* arg_string); //create node
StringList *StringList_constructor(); //get the top of the list
char* getHead(StringList *arg_list); //get the top of the list
void add_front(StringList *arg_list, char *arg_string); //add to the front of the list
void add_end(StringList *arg_list, char *arg_string); //add to the end of the list
char* delete_front(StringList *arg_list); //delete the front and return the string
char *delete_end(StringList *arg_list); //delete at the end of the list and return the string
void StringList_destructor(StringList *arg_list); //empty the list

#endif