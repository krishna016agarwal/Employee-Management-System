#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char name[50];
    int age;
    char gender[10];
    char designation[50];
    char contact[15];
    int employeeID;
    char address[100];
} Employee;

Employee employees[MAX];
int empCount = 0;
int currentMaxID = 1000;

void loadEmployees() {
    FILE *fp = fopen("employees.txt", "r");
    if (fp == NULL) return;

    while (!feof(fp)) {
        Employee e;
        if (fscanf(fp,
                   "Employee ID: %d\nName: %[^\n]\nAge: %d\nGender: %[^\n]\nDesignation: %[^\n]\nContact: %[^\n]\nAddress: %[^\n]\n\n",
                   &e.employeeID,
                   e.name,
                   &e.age,
                   e.gender,
                   e.designation,
                   e.contact,
                   e.address) == 7) {
            employees[empCount++] = e;
            if (e.employeeID >= currentMaxID) {
                currentMaxID = e.employeeID + 1;
            }
        } else {
            break;
        }
    }
    fclose(fp);
}

void saveEmployees() {
    FILE *fp = fopen("employees.txt", "w");
    for (int i = 0; i < empCount; i++) {
        fprintf(fp,
                "Employee ID: %d\n"
                "Name: %s\n"
                "Age: %d\n"
                "Gender: %s\n"
                "Designation: %s\n"
                "Contact: %s\n"
                "Address: %s\n\n",
                employees[i].employeeID,
                employees[i].name,
                employees[i].age,
                employees[i].gender,
                employees[i].designation,
                employees[i].contact,
                employees[i].address);
    }
    fclose(fp);
}

void addEmployee() {
    if (empCount >= MAX) {
        printf("Cannot add more employees.\n");
        return;
    }

    Employee e;
    e.employeeID = currentMaxID++;
    printf("Generated Employee ID: %d\n", e.employeeID);

    printf("Enter Name: ");
    fgets(e.name, sizeof(e.name), stdin); strtok(e.name, "\n");
    printf("Enter Age: ");
    scanf("%d", &e.age); getchar();
    printf("Enter Gender: ");
    fgets(e.gender, sizeof(e.gender), stdin); strtok(e.gender, "\n");
    printf("Enter Designation: ");
    fgets(e.designation, sizeof(e.designation), stdin); strtok(e.designation, "\n");
    printf("Enter Contact: ");
    fgets(e.contact, sizeof(e.contact), stdin); strtok(e.contact, "\n");
    printf("Enter Address: ");
    fgets(e.address, sizeof(e.address), stdin); strtok(e.address, "\n");

    employees[empCount++] = e;
    saveEmployees();
    printf("Employee added successfully!\n");
}

void deleteEmployee() {
    int id, found = 0;
    printf("Enter Employee ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < empCount; i++) {
        if (employees[i].employeeID == id) {
            found = 1;
            for (int j = i; j < empCount - 1; j++) {
                employees[j] = employees[j + 1];
            }
            empCount--;
            saveEmployees();
            printf("Employee deleted successfully!\n");
            break;
        }
    }
    if (!found) {
        printf("Employee with ID %d not found.\n", id);
    }
}

void showEmployees() {
    if (empCount == 0) {
        printf("No employee records found.\n");
        return;
    }

    for (int i = 0; i < empCount; i++) {
        printf("\nEmployee #%d\n", i + 1);
        printf("Employee ID: %d\n", employees[i].employeeID);
        printf("Name: %s\n", employees[i].name);
        printf("Age: %d\n", employees[i].age);
        printf("Gender: %s\n", employees[i].gender);
        printf("Designation: %s\n", employees[i].designation);
        printf("Contact: %s\n", employees[i].contact);
        printf("Address: %s\n", employees[i].address);
    }
}

void findEmployee() {
    char searchName[50];
    int found = 0;

    printf("Enter name of the employee to search: ");
    fgets(searchName, sizeof(searchName), stdin);
    strtok(searchName, "\n");

    for (int i = 0; i < empCount; i++) {
        if (strcasecmp(employees[i].name, searchName) == 0) {
            printf("\nEmployee Found:\n");
            printf("Employee ID: %d\n", employees[i].employeeID);
            printf("Name: %s\n", employees[i].name);
            printf("Age: %d\n", employees[i].age);
            printf("Gender: %s\n", employees[i].gender);
            printf("Designation: %s\n", employees[i].designation);
            printf("Contact: %s\n", employees[i].contact);
            printf("Address: %s\n", employees[i].address);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Employee '%s' not found.\n", searchName);
    }
}

void updateEmployee() {
    char name[50];
    int found = 0;

    printf("Enter name of the employee to update: ");
    fgets(name, sizeof(name), stdin);
    strtok(name, "\n");

    for (int i = 0; i < empCount; i++) {
        if (strcasecmp(employees[i].name, name) == 0) {
            found = 1;
            printf("Leave blank to skip a field.\n");

            char input[100];

            printf("Enter new Age (current: %d): ", employees[i].age);
            fgets(input, sizeof(input), stdin);
            if (strcmp(input, "\n") != 0) {
                employees[i].age = atoi(input);
            }

            printf("Enter new Gender (current: %s): ", employees[i].gender);
            fgets(input, sizeof(input), stdin);
            if (strcmp(input, "\n") != 0) {
                strtok(input, "\n");
                strcpy(employees[i].gender, input);
            }

            printf("Enter new Designation (current: %s): ", employees[i].designation);
            fgets(input, sizeof(input), stdin);
            if (strcmp(input, "\n") != 0) {
                strtok(input, "\n");
                strcpy(employees[i].designation, input);
            }

            printf("Enter new Contact (current: %s): ", employees[i].contact);
            fgets(input, sizeof(input), stdin);
            if (strcmp(input, "\n") != 0) {
                strtok(input, "\n");
                strcpy(employees[i].contact, input);
            }

            printf("Enter new Address (current: %s): ", employees[i].address);
            fgets(input, sizeof(input), stdin);
            if (strcmp(input, "\n") != 0) {
                strtok(input, "\n");
                strcpy(employees[i].address, input);
            }

            saveEmployees();
            printf("Employee data updated successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Employee '%s' not found.\n", name);
    }
}

void sortEmployees() {
    if (empCount == 0) {
        printf("No employee records found to sort.\n");
        return;
    }

    int choice;
    printf("\nSort By:\n");
    printf("1. Age (Ascending)\n");
    printf("2. Gender (Alphabetically)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();

    Employee sorted[MAX];
    for (int i = 0; i < empCount; i++) {
        sorted[i] = employees[i];
    }

    for (int i = 0; i < empCount - 1; i++) {
        for (int j = 0; j < empCount - i - 1; j++) {
            int shouldSwap = 0;
            if (choice == 1 && sorted[j].age > sorted[j + 1].age) {
                shouldSwap = 1;
            } else if (choice == 2 && strcasecmp(sorted[j].gender, sorted[j + 1].gender) > 0) {
                shouldSwap = 1;
            }

            if (shouldSwap) {
                Employee temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }

    printf("\n--- Sorted Employees ---\n");
    for (int i = 0; i < empCount; i++) {
        printf("\nEmployee #%d\n", i + 1);
        printf("Employee ID: %d\n", sorted[i].employeeID);
        printf("Name: %s\n", sorted[i].name);
        printf("Age: %d\n", sorted[i].age);
        printf("Gender: %s\n", sorted[i].gender);
        printf("Designation: %s\n", sorted[i].designation);
        printf("Contact: %s\n", sorted[i].contact);
        printf("Address: %s\n", sorted[i].address);
    }
}

void filterEmployees() {
    if (empCount == 0) {
        printf("No employee records to filter.\n");
        return;
    }

    int choice;
    printf("\nFilter Options:\n");
    printf("1. By Gender\n");
    printf("2. By Age Range\n");
    printf("3. By Designation\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();

    if (choice == 1) {
        char gender[10];
        printf("Enter gender to filter (Male/Female): ");
        fgets(gender, sizeof(gender), stdin);
        strtok(gender, "\n");

        printf("\n--- Filtered Employees (Gender: %s) ---\n", gender);
        int found = 0;
        for (int i = 0; i < empCount; i++) {
            if (strcasecmp(employees[i].gender, gender) == 0) {
                found = 1;
                printf("\nEmployee ID: %d\n", employees[i].employeeID);
                printf("Name: %s\n", employees[i].name);
                printf("Age: %d\n", employees[i].age);
                printf("Gender: %s\n", employees[i].gender);
                printf("Designation: %s\n", employees[i].designation);
                printf("Contact: %s\n", employees[i].contact);
                printf("Address: %s\n", employees[i].address);
            }
        }
        if (!found) printf("No employees found with gender %s.\n", gender);

    } else if (choice == 2) {
        int minAge, maxAge;
        printf("Enter minimum age: ");
        scanf("%d", &minAge);
        printf("Enter maximum age: ");
        scanf("%d", &maxAge);

        printf("\n--- Filtered Employees (Age %d to %d) ---\n", minAge, maxAge);
        int found = 0;
        for (int i = 0; i < empCount; i++) {
            if (employees[i].age >= minAge && employees[i].age <= maxAge) {
                found = 1;
                printf("\nEmployee ID: %d\n", employees[i].employeeID);
                printf("Name: %s\n", employees[i].name);
                printf("Age: %d\n", employees[i].age);
                printf("Gender: %s\n", employees[i].gender);
                printf("Designation: %s\n", employees[i].designation);
                printf("Contact: %s\n", employees[i].contact);
                printf("Address: %s\n", employees[i].address);
            }
        }
        if (!found) printf("No employees found in the given age range.\n");

    } else if (choice == 3) {
        char designation[50];
        printf("Enter designation to filter: ");
        fgets(designation, sizeof(designation), stdin);
        strtok(designation, "\n");

        printf("\n--- Filtered Employees (Designation: %s) ---\n", designation);
        int found = 0;
        for (int i = 0; i < empCount; i++) {
            if (strcasecmp(employees[i].designation, designation) == 0) {
                found = 1;
                printf("\nEmployee ID: %d\n", employees[i].employeeID);
                printf("Name: %s\n", employees[i].name);
                printf("Age: %d\n", employees[i].age);
                printf("Gender: %s\n", employees[i].gender);
                printf("Designation: %s\n", employees[i].designation);
                printf("Contact: %s\n", employees[i].contact);
                printf("Address: %s\n", employees[i].address);
            }
        }
        if (!found) printf("No employees found with designation '%s'.\n", designation);

    } else {
        printf("Invalid choice. Returning to menu.\n");
    }
}

void adminMenu() {
    int choice;
    do {
        printf("\n--- Admin Menu ---\n");
        printf("1. Add New Employee\n");
        printf("2. Delete Employee\n");
        printf("3. Show All Employees\n");
        printf("4. Find Employee by Name\n");
        printf("5. Update Employee Data\n");
        printf("6. Sort Employees\n");
        printf("7. Filter Employees\n");
        printf("8. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: deleteEmployee(); break;
            case 3: showEmployees(); break;
            case 4: findEmployee(); break;
            case 5: updateEmployee(); break;
            case 6: sortEmployees(); break;
            case 7: filterEmployees(); break;
            case 8: printf("Logging out...\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 8);
}

void employeeMenu() {
    int choice;
    do {
        printf("\n--- Employee Menu ---\n");
        printf("1. Show All Employees\n");
        printf("2. Find Employee by Name\n");
        printf("3. Sort Employees\n");
        printf("4. Filter Employees\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: showEmployees(); break;
            case 2: findEmployee(); break;
            case 3: sortEmployees(); break;
            case 4: filterEmployees(); break;
            case 5: printf("Exiting employee menu...\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 5);
}

int verifyAdmin() {
    char username[20], password[20];
    printf("Enter admin username: ");
    fgets(username, sizeof(username), stdin); strtok(username, "\n");
    printf("Enter admin password: ");
    fgets(password, sizeof(password), stdin); strtok(password, "\n");

    if (strcmp(username, "admin") == 0 && strcmp(password, "pass123") == 0) {
        return 1;
    } else {
        printf("Invalid username or password!\n");
        return 0;
    }
}

int main() {
    loadEmployees();

    int choice;
    do {
        printf("\n--- Welcome to Employee Management System ---\n");
        printf("1. Admin Login\n");
        printf("2. Employee Access\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                if (verifyAdmin()) {
                    adminMenu();
                }
                break;
            case 2:
                employeeMenu();
                break;
            case 3:
                printf("Thank you for using the system!\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 3);

    return 0;
}
