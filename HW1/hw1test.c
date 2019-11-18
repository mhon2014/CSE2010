/*

  Author: Michael James Hon
  Email: mhon2014@my.fit.edu
  Course: CSE2010
  Section: E1
  Description: HW1




 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const int time_difference_and_travel = 5;

typedef struct orders{
    char customer_name[20];
    int order_time, num_of_books,num_of_electronics;
    struct orders *next;
}customer_orders;

typedef struct queue_orders{
    customer_orders *head, *tail;
    int size;
}queue_customer_orders;

typedef struct available{
    char available_name[20];
    struct available *next;
}available_workers;

typedef struct assignments{
  char worker_name[20];
  customer_orders *orders;
  int time_assigned;
  int time_finished;
  struct assignments *next;;
}worker_assignments;

void print_orders(customer_orders *list) {
  customer_orders *temp = list;

  while(temp != NULL) {
    printf("%s ", temp->customer_name);
    temp = temp->next;
  }
  printf("\n");
}
void print_available(available_workers *list) {
  available_workers *temp = list;
  printf("AvailableWorkersList ");

  while(temp != NULL) {
    printf("%s ", temp->available_name);
    temp = temp->next;
  }
  printf("\n");
  }
void print_assignments(worker_assignments *list) {
  worker_assignments *temp = list;
  printf("WorkerAssignmentList ");

  while(temp != NULL) {
    printf("%s ", temp->worker_name);
    temp = temp->next;
  }
  printf("\n");
}

// void orders_add(queue_customer_orders *list, customer_orders *node) { 
//     // Create a new LL node 
//     customer_orders *new_node = (customer_orders*)malloc(sizeof(customer_orders));
//     // If queue is empty, then new node is front and rear both 
//     if (list->tail == NULL) 
//     { 
//        list->front = list->tail = temp; 
//        return; 
//     } 
  
//     // Add the new node at the end of queue and change rear 
//     list->tail->next = temp;
//     list->tail = temp; 
// } 
// void list_orders_add(queue_orders **f_order, int time, char *name, int books, int electronics) {
//   customer_orders *new_node = (customer_orders*)malloc(sizeof(customer_orders));
//   new_node->next = NULL;
//   strcpy(new_node->customer_name, name);
//   new_node->order_time = time;
//   new_node->num_of_books = books;
//   new_node->num_of_electronics = electronics;
//   if ((*f_order)->head == NULL) {
//     (*f_order) = new_node;
//   }
//   else {
//     customer_orders *temp = (*f_order);
//     while(temp->next) {
//       temp = temp->next;
//     }
//     temp->next = new_node;
//   }
//   printf("CustomerOrder %d %s %d %d\n", time, name, books, electronics);
// }

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
  printf("CustomerOrder %d %s %d %d\n", time, name, books, electronics);
}

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
void assignments_add(worker_assignments **f_assignment, char *name, customer_orders f_orders, int time_start, int time_to_finish){
  worker_assignments *new_node = (worker_assignments*)malloc(sizeof(worker_assignments));
  new_node->next = NULL;
  strcpy(new_node->worker_name, name);
  new_node->time_assigned = time_start;
  new_node->time_finished = time_to_finish;
  new_node->orders = &f_orders;
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
  printf("WorkerAssignment %d %s ", time_start, name);
  print_orders(&f_orders);
}

customer_orders *pop_orders(customer_orders **list) {
  if ((*list) == NULL) {
    printf("List is empty.\n");
    return NULL;
  }
  customer_orders *temp = (*list);
  customer_orders *return_val = temp;
  return_val->next = NULL;
  (*list) = (*list)->next;
  free(temp);
  return return_val;

}

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

void pop_assignments(worker_assignments **list) {
    if ((*list) == NULL) {
    printf("List is empty.\n");
    return;
  }
  worker_assignments *temp = (*list);
  (*list) = (*list)->next;
  free(temp);
}

void clean_orders(customer_orders **list_to_delete) {
  while(*list_to_delete) {
    pop_orders(list_to_delete);
  }
}

void clean_workers(available_workers **list_to_delete) {
    while(*list_to_delete) {
      pop_workers(list_to_delete);
  }
}

void clean_assignments(worker_assignments **list_to_delete) {
    while(*list_to_delete) {
    pop_assignments(list_to_delete);
  }
}

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

int size_orders(customer_orders **list) {
    customer_orders *temp = (*list);
    int count = 0;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    if (count < 2){
        return 0;
    }

    return count;

}


int bundlefunction(customer_orders **list, int start, int end) {
    int bundled_number = 0;
    customer_orders *temp = (*list);

    //seperate int into 2 division and modulo for hours and minutes /24 , %60
    if (temp->num_of_books > 0 && temp->num_of_electronics > 0) {
        return 0;
    } 
    else if (temp->num_of_books > 0) {
        bundled_number = temp->num_of_books;
    }
    else if (temp->num_of_electronics > 0) {
        bundled_number = temp->num_of_electronics;
    }

    while (temp != NULL && temp->next != NULL) {
        if(temp->next->order_time - temp->order_time <= time_difference_and_travel) {
            return 0;
        }

        if (temp->num_of_books > 0 && temp->next->num_of_books > 0){
        if(temp->num_of_electronics == 0 && temp->next->num_of_electronics == 0) {
            bundled_number += temp->next->num_of_books;
        }
        } 
        else if(temp->num_of_electronics > 0 && temp->next->num_of_electronics >0) {
        if(temp->num_of_books == 0 && temp->next->num_of_books) {
            bundled_number += temp->next->num_of_electronics;
        }
        }
    }

    return bundled_number;
}

/*
  Description for each function, parameter, and return value (if any)
 */

int main(int argc, char* argv[])
{ 
  customer_orders *list_orders = NULL;
  available_workers *list_available = NULL;
  worker_assignments *list_assignments = NULL;

  char file_name[20];
  char line[50];
  char command[20];
  char name[20];
  int prev_time = 0, max_fulfillment, time, num_books, num_electronics;
  FILE *file_read;

  printf("Enter filename: ");
  scanf("%s", file_name);

  file_read = fopen(file_name, "r");
  /*
    description of declared variables
   */

  workers_add(&list_available, "Alice");
  workers_add(&list_available, "Bob");
  workers_add(&list_available, "Carol");
  workers_add(&list_available, "David");
  workers_add(&list_available, "Emily");

    if (file_read == NULL){
    printf("Error");
    return 0;
    }

  while (fgets(line, sizeof(line), file_read)) {
    sscanf(line, "%s %d %s %d %d", command, &time, name, &num_books, &num_electronics);

    int finish = 0;
    
    if (strcmp(command, "CustomerOrder") == 0) {
        orders_add(&list_orders, time, name, num_books, num_electronics);       
        // printf("Check\n");
        if (size_orders(&list_orders) < 2) {
            prev_time = time;
            continue;
        }
        else if (bundlefunction(&list_orders, prev_time, time) == 0){ // 0 means that it cannot be bundled
        //assign worker
            // printf("assigned\n");
            // print_available(list_available);
            // printf("%s\n",pop_workers(&list_available));
            // printf("Dope1\n");
            // printf("%s\n",pop_orders(&list_orders)->customer_name);
            // printf("Dope2");
            finish = calculate_finish(list_orders);
            // printf("bundle %d\n", bundlefunction(&list_orders, prev_time, time));
            // printf("%d\n",finish);
            assignments_add(&list_assignments, pop_workers(&list_available), *pop_orders(&list_orders), prev_time, finish);
            // printf("finished\n");
        }
        else {
            //if both has the same category then bundle them
            // printf("Bundled\n");
            finish = bundlefunction(&list_orders, prev_time, time);
            assignments_add(&list_assignments, pop_workers(&list_available), *pop_orders(&list_orders),time, finish);
            clean_orders(&list_orders);
            //get all the names of the customer and and bundle 
        }
    }

    else if(strcmp(command, "PrintAvailableWorkerList") ==  0){
      print_available(list_available);
    }
    else if(strcmp(command, "PrintWorkerAssignmentList") ==  0){
      print_assignments(list_assignments);

    }
    else if(strcmp(command, "PrintMaxFulfillmentTime") ==  0){
      printf("%d\n",max_fulfillment);
    }

  }
  clean_orders(&list_orders);
  clean_workers(&list_available);
  clean_assignments(&list_assignments);
  fclose(file_read);

  
  /*
    description for each "block" (about 5 lines of instructions)
   */
  return 0;
}

