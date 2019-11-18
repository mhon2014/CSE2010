else if (bundlefunction(&list_orders, prev_time, time) == 0){ // 0 means that it cannot be bundled
//                if(strcmp(name, "Sarah")){
//                    printf("Yeet");
//                }
              //assign worker
              // printf("assigned\n");
              // print_available(list_available);
              // printf("%s\n",pop_workers(&list_available));
              // printf("Dope1\n");
              // printf("%s\n",pop_orders(&list_orders)->customer_name);
              // printf("Dope2");
              finish = calculate_finish(list_orders);

//                 printf("bundle %d\n", bundlefunction(&list_orders, prev_time, time));
              // printf("%d\n",finish);
              //printf("worker name: %s",pop_workers(&list_available));
//                printf("before name: %s\n", list_orders->customer_name);
              strcpy(assigned_worker_name, pop_workers(&list_available));
              strcat(customer_name_string, pop_orders(&list_orders));
//                printf("customer_name_string: %s\n", customer_name_string);
              assignments_add(&list_assignments, assigned_worker_name ,customer_name_string, prev_time, prev_time+finish);
              prev_time = time;
              printf("WorkerAssignment %d %s %s\n", prev_time, assigned_worker_name, customer_name_string);
