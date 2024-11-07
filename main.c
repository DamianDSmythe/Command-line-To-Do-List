#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASK_LENGTH 100
#define FILENAME "todo_list.txt"

void print_menu() {
    printf("\nTodo List Menu:\n");
    printf("1. Add a task\n");
    printf("2. View tasks\n");
    printf("3. Remove a task\n");
    printf("4. Exit\n");
    printf("Choose an option: ");
}

void add_task(const char *task) {
    FILE *file = fopen(FILENAME, "a"); // Open file in append mode
    if (file == NULL) {
        perror("Unable to open file");
        return;
    }
    fprintf(file, "%s\n", task);  // Write the task to the file
    fclose(file);
    printf("Task added successfully.\n");
}

void view_tasks() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("No tasks found!\n");
        return;
    }

    char task[MAX_TASK_LENGTH];
    printf("\nYour To-Do List:\n");
    int task_number = 1;
    while (fgets(task, sizeof(task), file)) {
        printf("%d. %s", task_number++, task);
    }
    fclose(file);
}

void remove_task(int task_num) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("No tasks to remove.\n");
        return;
    }

    char tasks[100][MAX_TASK_LENGTH];
    int task_count = 0;

    while (fgets(tasks[task_count], sizeof(tasks[task_count]), file)) {
        task_count++;
    }
    fclose(file);

    if (task_num < 1 || task_num > task_count) {
        printf("Invalid task number.\n");
        return;
    }

    // Remove the task by shifting subsequent tasks up
    for (int i = task_num - 1; i < task_count - 1; i++) {
        strcpy(tasks[i], tasks[i + 1]);
    }

    // Write the updated task list back to the file
    file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Unable to open file for updating.\n");
        return;
    }

    for (int i = 0; i < task_count - 1; i++) {
        fprintf(file, "%s", tasks[i]);
    }

    fclose(file);
    printf("Task removed successfully.\n");
}

int main() {
    int choice;
    char task[MAX_TASK_LENGTH];

    while (1) {
        print_menu();
        scanf("%d", &choice);
        getchar(); // Consume the newline character left by scanf

        switch (choice) {
            case 1:
                printf("Enter a task: ");
                fgets(task, sizeof(task), stdin);
                task[strcspn(task, "\n")] = '\0'; // Remove the newline character at the end
                add_task(task);
                break;
            case 2:
                view_tasks();
                break;
            case 3:
                printf("Enter task number to remove: ");
                int task_num;
                scanf("%d", &task_num);
                remove_task(task_num);
                break;
            case 4:
                printf("Exiting the program.\n");
                return 0;
            default:
                printf("Invalid option, try again.\n");
        }
    }
}
