/*
 
 Author: Michael James Hon
 Email: mhon2014@my.fit.edu
 Course: CSE2010
 Section: E1 / 14
 Description: HW1 using 3 singly linked list to solve the problem given.
 
 
 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const int time_difference_and_travel = 5;//const used for time calculation 


typedef struct orders{                                  //orders node
  char customer_name[20];                             //customer name of the order
  int order_time, num_of_books,num_of_electronics;    //time ordered, and their number of products ordered
  struct orders *next;                                //next order in line
}customer_orders;

typedef struct available{                               //list of available workers
  char available_name[20];                            //ismply has names and the next worker in line
  struct available *next;;
}available_workers;

typedef struct assignments{                           //assignment list used to assign workers
  char worker_name[20];                             //worker name
  char order_names[20];
  int time_assigned;
  int time_finished;
  struct assignments *next;;
}worker_assignments;

void print_orders(customer_orders *list) { //funcion to print the orders, not really used in the input file
  customer_orders *temp = list;            //I just use it for troubleshooting, it can be ignored
  
  while(temp != NULL) {
      printf("%s ", temp->customer_name);
      temp = temp->next;
  }
  printf("\n");
}
void print_available(available_workers *list) {   //function to print the list of available workers
    available_workers *temp = list;               //loop and print names untill null
    printf("AvailableWorkersList ");
    
    while(temp != NULL) {
        printf("%s ", temp->available_name);
        temp = temp->next;
    }
    printf("\n");
}
void print_assignments(worker_assignments *list) {      //function to print list of assignments
    worker_assignments *temp = list;                    //just loop and print the names until you reach null 
    printf("WorkerAssignmentList ");
    
    while(temp != NULL) {
        printf("%s:%s ", temp->worker_name,temp->order_names);
        temp = temp->next;
    }
    printf("\n");
}

/*
  function to add to the orders list, creates a new node and set values to them
  if list is null then it is at the top.
  if list is not empty (not null), add to the back.
*/
void orders_add(customer_orders **f_order, int time, char *name, int books, int electronics) {
    customer_orders *new_node = (customer_orders*)malloc(sizeof(customer_orders));
    new_node->next = NULL;
    strcpy(new_node->customer_name, name);
    new_node->order_time = time;
    new_node->num_of_books = books;
    new_node->num_of_electronics = electronics;
    if ((*f_order) == NULL) {
        (*f_order) = new_node;
    }
    else {
        customer_orders *temp = (*f_order);
        while(temp->next) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}
/*
  works the 
  function to add to the orders list, creates a new node and set values to them
  if list is null then it is at the top.
  if list is not empty (not null), add to the back.
*/
void workers_add(available_workers **f_workers, char* name){
    available_workers *new_node = (available_workers*)malloc(sizeof(available_workers));
    new_node->next = NULL;
    strcpy(new_node->available_name, name);
    if ((*f_workers)== NULL) {
        (*f_workers) = new_node;
        return;
    }
    else {
        available_workers *temp = (*f_workers);
        while(temp->next) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}


/*
  same as the previous function, add at the back if not empty
*/
void assignments_add(worker_assignments **f_assignment, char *name, char *f_customer_name, int time_start, int time_to_finish){
    worker_assignments *new_node = (worker_assignments*)malloc(sizeof(worker_assignments));
    new_node->next = NULL;
    strcpy(new_node->worker_name, name);
    new_node->time_assigned = time_start;
    new_node->time_finished = time_to_finish;
    strcpy(new_node->order_names, f_customer_name);
    if ((*f_assignment) == NULL){
        (*f_assignment) = new_node;
    }
    else {
        worker_assignments *temp = (*f_assignment);
        while(temp->next) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

/*
  pop function to pop the top of the list in the argument
  returns the customer name to be used in the assignment list
*/
char *pop_orders(customer_orders **list) {
    if ((*list) == NULL) {
        printf("List is empty.\n");
        return NULL;
    }
    customer_orders *temp = (*list);
    char *return_val = temp->customer_name;
    (*list) = (*list)->next;
    free(temp);
    return return_val;
    
}

/*
  pop function to pop the top of the list in the argument
  this one the worker name instead so it can be used in assignment list
*/
char *pop_workers(available_workers **list) {
    if ((*list) == NULL) {
        printf("List is empty.\n");
        return NULL;
    }
    
    available_workers *temp = (*list);
    char *return_name = temp->available_name;
    (*list) = (*list)->next;
    free(temp);
    return return_name;
}

/*
  pop function of the assignment list
  this function just pops the top of the order
  and print out what as at the top as completed
*/
void pop_assignments(worker_assignments **list) {
    if ((*list) == NULL) {
        printf("List is empty.\n");
        return;
    }
    worker_assignments *temp = (*list);
    (*list) = (*list)->next;
    printf("OrderCompletion %d %s\n", temp->time_finished, temp->order_names);
    free(temp);
}

/*
  function used for cleaning the list to avoid memory leaks
*/
void clean_orders(customer_orders **list_to_delete) {
  while(*list_to_delete) {
    pop_orders(list_to_delete);
  }
}

/*
  function used for cleaning the list to avoid memory leaks
*/
void clean_workers(available_workers **list_to_delete) {
  while(*list_to_delete) {
    pop_workers(list_to_delete);
  }
}

/*
  function used for cleaning the list to avoid memory leaks
*/
void clean_assignments(worker_assignments **list_to_delete) {
  while(*list_to_delete) {
    pop_assignments(list_to_delete);
  }
}

/*
function used to calculate the time it takes to finish the order
if there is 2 category then it's (2*5)+(number of books)+(number of electronics) 
if there's only 1 catergory then it's 5+(number of products)
*/
int calculate_finish(customer_orders *list) {
    int calculated_time = 0;
    if (list->num_of_books > 0 && list->num_of_electronics > 0){
        calculated_time = 2*time_difference_and_travel + list->num_of_books + list->num_of_electronics;
    }
    else {
        calculated_time = time_difference_and_travel + list->num_of_books + list->num_of_electronics;
    }
    return calculated_time;
}

/*
  function used to return the size of the orders list
  used in main to check if the list is lest than 2
  returns and int -> size of the list
*/
int size_orders(customer_orders **list) {
    customer_orders *temp = (*list);
    int count = 0;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
    
}

//Function that returns an int, if 0 then cannot be bundled, else any other number is the number of bundles
//uses the list of orders to check if they can be bunndled to the next one in the list.
//the start integer is the time before
int bundlefunction(customer_orders **list) {
    int bundled_number = 0;
    customer_orders *temp = (*list);
    
    //set the value of the bundles
    // if there's 2 products then just return 0, meaning it cannot be bundled
    //else make the bundles equal to the product of which there is only 1
    if (temp->num_of_books > 0 && temp->num_of_electronics > 0) {
        return 0;
    }
    else if (temp->num_of_books > 0) {
        bundled_number = temp->num_of_books;
    }
    else if (temp->num_of_electronics > 0) {
        bundled_number = temp->num_of_electronics;
    }
    //iterate though the list to count the bundles, if it encounters another product then return 0
    while (temp != NULL && temp->next != NULL) {
        if(temp->next->order_time - temp->order_time > time_difference_and_travel) {
            return 0; //check the time to make sure it is equal or less than 5, if it's higher then just return;
        }
        
        if (temp->num_of_books > 0 && temp->next->num_of_books > 0){
            if(temp->num_of_electronics == 0 && temp->next->num_of_electronics == 0) {
                bundled_number += temp->next->num_of_books;     //this block used to count, only if there is books
            }
        }
        else if(temp->num_of_electronics > 0 && temp->next->num_of_electronics >0) {
            if(temp->num_of_books == 0 && temp->next->num_of_books) {
                bundled_number += temp->next->num_of_electronics; //this block used to count, only if there is electronics
            }
        }
        temp = temp->next;
    }
    //return the number of bundled product
    return bundled_number;
}

/*
 Description for each function, parameter, and return value (if any)
 */

int main(int argc, char* argv[])
{
    /*
     description of declared variables
     */
    
    customer_orders *list_orders = NULL; //orders list
    available_workers *list_available = NULL; //available workers list
    worker_assignments *list_assignments = NULL;  //assignment list
    
    char file_name[20];     //used for input file
    char line[50];          //used for reading lines
    char command[20];       //used for reading a command from line
    char name[20];          //name from line variable
    int prev_time = 0, max_fulfillment = 0, time, num_books, num_electronics; //prev_time to keep track of the time before
                                              //max fullment for getting the max
                                              //time for the time values from line variable
                                              //num_books for book values from line variable
                                              //num_electronics for electronics values from line variable
    FILE *file_read;                              
    
    printf("Enter filename: ");         //file name used for input
    scanf("%s", file_name);
    
    file_read = fopen(file_name, "r");

    workers_add(&list_available, "Alice");    //Add available workers to the list at the beginning
    workers_add(&list_available, "Bob");
    workers_add(&list_available, "Carol");
    workers_add(&list_available, "David");
    workers_add(&list_available, "Emily");
    
    
    if (file_read == NULL){
        printf("Error");
        return 0;
    }
    
    while (fgets(line, sizeof(line), file_read)) { //read lines
        sscanf(line, "%s %d %s %d %d", command, &time, name, &num_books, &num_electronics);//read the values from the line varaible
        
        int finish = 0;
        char assigned_worker_name[20] ="";
        
        if (list_assignments != NULL && time > list_assignments->time_finished) {
            workers_add(&list_available, list_assignments->worker_name);  //add workers to available when they're are free
            pop_assignments(&list_assignments);
        }

        if (strcmp(command, "CustomerOrder") == 0) {      //check command
          char customer_name_string[20] = "";           //variable used to store the customer name to the assignment list
          orders_add(&list_orders, time, name, num_books, num_electronics);  //add to order list
          if (size_orders(&list_orders) < 2) {        //if order is less than 1, wait for the next one to decide bundling
            prev_time = time;
            printf("%s", line);             

            }
          else if (bundlefunction(&list_orders) == 0){ // 0 means that it cannot be bundled

              finish = calculate_finish(list_orders); //calculate the time it takes to finish

              strcpy(assigned_worker_name, pop_workers(&list_available));   //copy the name of the workers to put in assignment
              strcat(customer_name_string, pop_orders(&list_orders));     //copy name of the customer order to put in assignment

              assignments_add(&list_assignments, assigned_worker_name ,customer_name_string, prev_time, prev_time+finish);

              prev_time = time; //change prev time to current to use for comparison and setting time

              printf("WorkerAssignment %d %s %s\n", prev_time, assigned_worker_name, customer_name_string);
              printf("%s", line);

            }
            else if (time - prev_time <= time_difference_and_travel){     //bundling
              
              prev_time += time_difference_and_travel;

              finish = 2*time_difference_and_travel + bundlefunction(&list_orders);//calculate finish

              strcpy(assigned_worker_name, pop_workers(&list_available));

              while(list_orders != NULL) {          //concatenate strings of customer names 
                  strcat(customer_name_string, pop_orders(&list_orders));
                  strcat(customer_name_string, " ");
              }

              assignments_add(&list_assignments, assigned_worker_name, customer_name_string, prev_time, prev_time+finish);
              printf("%s", line);
              printf("WorkerAssignment %d %s %s\n", prev_time, assigned_worker_name, customer_name_string);

            }
            if (finish > max_fulfillment) { //get the maximum fullment time
                max_fulfillment = finish;
            }
        }
        
        else if(strcmp(command, "PrintAvailableWorkerList") ==  0){   //just print the list
            print_available(list_available);
        }
        else if(strcmp(command, "PrintWorkerAssignmentList") ==  0){  //print the assignments
            print_assignments(list_assignments);
            
        }
        else if(strcmp(command, "PrintMaxFulfillmentTime") ==  0){
            printf("MaxFulfillmentTime %d\n",max_fulfillment);      //print the max time
        }
        
    }
    //clean the list at the end to avoid memory leaks;
    clean_orders(&list_orders);
    clean_workers(&list_available);
    clean_assignments(&list_assignments);
    fclose(file_read);
    
    
    /*
     description for each "block" (about 5 lines of instructions)
     */
    return 0;
}

