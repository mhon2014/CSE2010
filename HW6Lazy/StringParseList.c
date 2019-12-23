#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "StringParseList.h"

//returns true if list is empty
bool ListIsEmpty(StringList *arg_list){
    if (arg_list == NULL) {
        printf("Error, pointer to list is NULL.");
        return 0;
    } 

    if (arg_list->size == 0) {
        return true;
    }
    else {
        return false;
    }
}


//helper function to print list
void print_list(StringList *arg_list){
    if (ListIsEmpty(arg_list)) {
        printf("List is empty.\n");
        printf("%d\n", arg_list->size);
    }
    else {
        StringNode *iterator_node = arg_list->head;
        while(iterator_node != NULL){
            printf("%s ", iterator_node->word);
            iterator_node = iterator_node->next;
        }
        printf("\n");
    }
}

//return list size
int ListSize(StringList *arg_list){
    if (arg_list == NULL) {
        printf("Error, pointer to list is NULL.");
        return 0;
    }

    return arg_list->size;
}

//create node
StringNode *StringNode_constructor(char* arg_string) {
    StringNode *new_node = (StringNode*)malloc(sizeof(StringNode));
    new_node->word = arg_string;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

//create list
StringList *StringList_constructor(){
    StringList *new_list = (StringList*)malloc(sizeof(StringList));
    new_list->size = 0;
    new_list->head = NULL;
    new_list->tail = NULL;
    return new_list;
}

//get the top of the list
char* getHead(StringList *arg_list){
    if (arg_list == NULL) {
        printf("Error, pointer to list is NULL.");
        return 0;
    }

     if (ListIsEmpty(arg_list)){
         printf("List is empty.\n");
    }
    return arg_list->head->word;
}

//add to the front of the list
void add_front(StringList *arg_list, char *arg_string){
    if (arg_list == NULL) {
        printf("Error, pointer to list is NULL.");
        return;
    }

    StringNode *new_node = StringNode_constructor(arg_string);
    if (ListIsEmpty(arg_list)){
        arg_list->head = arg_list->tail = new_node;
        //add to the front
    }
    else {
        arg_list->head->prev = new_node;
        arg_list->head = arg_list->head->prev;
    }
    arg_list->size++;

}

//add to the end of the list
void add_end(StringList *arg_list, char *arg_string){
    if (arg_list == NULL) {
        printf("Error, pointer to list is NULL.");
        return;
    }

    StringNode *new_node = StringNode_constructor(arg_string);
    if (ListIsEmpty(arg_list)){
        arg_list->head = arg_list->tail = new_node;
        //add to the front
    }
    else {
        arg_list->tail->next = new_node;
        arg_list->tail = arg_list->tail->next;
    }
    arg_list->size++;

}

//delete the front and return the string
char* delete_front(StringList *arg_list){
    if (arg_list == NULL) {
        printf("Error, pointer to list is NULL.");
        return 0;
    }    

    if(ListIsEmpty(arg_list)) {
        printf("List is empty.\n");
        return 0;
    } 
    
    StringNode *temp_string = arg_list->head;
    char* return_string = temp_string->word;

    if(ListSize(arg_list) == 1){
        arg_list->head = NULL;
        arg_list->tail = NULL;
    }
    else {
        arg_list->head = arg_list->head->next;
        arg_list->head->prev = NULL;
        
    }

    free(temp_string);
    arg_list->size--;
    return return_string;

}


//delete at the end of the list and return the string 
char *delete_end(StringList *arg_list){
    if (arg_list == NULL) {
        printf("Error, pointer to list is NULL.");
        return 0;
    }    

    if(ListIsEmpty(arg_list)) {
        printf("List is empty.\n");
        return 0;
    } 
    
    StringNode *temp_string = arg_list->tail;
    char *return_value = arg_list->tail->word;

    if(ListSize(arg_list) == 1){
        arg_list->tail = NULL;
        arg_list->head = NULL;
    }
    else {
        arg_list->tail = arg_list->tail->prev;
        arg_list->tail->next = NULL;
        
    }
    free(temp_string);
    arg_list->size--;
    return return_value;
}


//empty the list
void StringList_destructor(StringList *arg_list){
    while(!ListIsEmpty(arg_list)){
        delete_front(arg_list);
    }
}

