#include <stdio.h>
#include <stdlib.h>

#define MAX_STUDENTS 50

struct Student {
    char name[50];
    int rollNumber;
    float marks;
};

// Function declarations
void addStudent(struct Student **students, int *studentCount);
void displayStudents(struct Student *students, int studentCount);
void displayAverageMarks(struct Student *students, int studentCount);
void searchAndUpdateStudent(struct Student *students, int studentCount);
void calculateAndDisplayPercentage(struct Student *students, int studentCount);
void saveToFile(struct Student *students, int studentCount);
void loadFromFile(struct Student **students, int *studentCount);
void sortStudents(struct Student *students, int studentCount, int sortingCriteria);

int main() {
    struct Student *students = NULL;
    int studentCount = 0;

    while (1) {
        printf("\nStudent Management System\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Display Average Marks\n");
        printf("4. Search and Update Student\n");
        printf("5. Calculate Percentage\n");
        printf("6. Save to File\n");
        printf("7. Load from File\n");
        printf("8. Sort Students\n");
        printf("9. Exit\n");

        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(&students, &studentCount);
                break;

            case 2:
                displayStudents(students, studentCount);
                break;

            case 3:
                displayAverageMarks(students, studentCount);
                break;

            case 4:
                searchAndUpdateStudent(students, studentCount);
                break;

            case 5:
                calculateAndDisplayPercentage(students, studentCount);
                break;

            case 6:
                saveToFile(students, studentCount);
                break;

            case 7:
                loadFromFile(&students, &studentCount);
                break;

            case 8: {
                int sortingCriteria;
                printf("Choose sorting criteria (1: Roll No, 2: Marks): ");
                scanf("%d", &sortingCriteria);
                sortStudents(students, studentCount, sortingCriteria);
                break;
            }

            case 9:
                printf("Exiting...\n");
                free(students);
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}

void addStudent(struct Student **students, int *studentCount) {
    if (*studentCount >= MAX_STUDENTS) {
        printf("Maximum students reached!\n");
        return;
    }

    struct Student *temp = realloc(*students, (*studentCount + 1) * sizeof(struct Student));
    if (temp == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    *students = temp;

    printf("Enter name: ");
    scanf(" %[^\n]", (*students)[*studentCount].name);

    printf("Enter roll number: ");
    scanf("%d", &(*students)[*studentCount].rollNumber);

    printf("Enter marks: ");
    scanf("%f", &(*students)[*studentCount].marks);

    (*studentCount)++;
    printf("Student added successfully!\n");
}

void displayStudents(struct Student *students, int studentCount) {
    if (studentCount == 0) {
        printf("No students available.\n");
        return;
    }

    for (int i = 0; i < studentCount; i++) {
        printf("Name: %s | Roll: %d | Marks: %.2f\n",
               students[i].name,
               students[i].rollNumber,
               students[i].marks);
    }
}

void displayAverageMarks(struct Student *students, int studentCount) {
    if (studentCount == 0) {
        printf("No data available.\n");
        return;
    }

    float total = 0;
    for (int i = 0; i < studentCount; i++) {
        total += students[i].marks;
    }

    printf("Average Marks: %.2f\n", total / studentCount);
}

void searchAndUpdateStudent(struct Student *students, int studentCount) {
    int roll;
    printf("Enter roll number: ");
    scanf("%d", &roll);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].rollNumber == roll) {
            printf("Enter new name: ");
            scanf(" %[^\n]", students[i].name);

            printf("Enter new marks: ");
            scanf("%f", &students[i].marks);

            printf("Updated successfully!\n");
            return;
        }
    }
    printf("Student not found.\n");
}

void calculateAndDisplayPercentage(struct Student *students, int studentCount) {
    int roll;
    printf("Enter roll number: ");
    scanf("%d", &roll);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].rollNumber == roll) {
            printf("Percentage: %.2f%%\n", students[i].marks);
            return;
        }
    }
    printf("Student not found.\n");
}

void saveToFile(struct Student *students, int studentCount) {
    FILE *file = fopen("student_data.txt", "w");
    if (!file) {
        printf("File error!\n");
        return;
    }

    for (int i = 0; i < studentCount; i++) {
        fprintf(file, "%s %d %.2f\n",
                students[i].name,
                students[i].rollNumber,
                students[i].marks);
    }

    fclose(file);
    printf("Saved successfully.\n");
}

void loadFromFile(struct Student **students, int *studentCount) {
    FILE *file = fopen("student_data.txt", "r");
    if (!file) {
        printf("No file found.\n");
        return;
    }

    *studentCount = 0;

    while (1) {
        struct Student temp;

        if (fscanf(file, "%s %d %f",
                   temp.name,
                   &temp.rollNumber,
                   &temp.marks) != 3) {
            break;
        }

        struct Student *newPtr = realloc(*students, (*studentCount + 1) * sizeof(struct Student));
        if (!newPtr) {
            printf("Memory error!\n");
            exit(1);
        }

        *students = newPtr;
        (*students)[*studentCount] = temp;
        (*studentCount)++;
    }

    fclose(file);
    printf("Loaded successfully.\n");
}

void sortStudents(struct Student *students, int studentCount, int sortingCriteria) {
    if (studentCount == 0) {
        printf("No data to sort.\n");
        return;
    }

    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = 0; j < studentCount - i - 1; j++) {
            if ((sortingCriteria == 1 && students[j].rollNumber > students[j+1].rollNumber) ||
                (sortingCriteria == 2 && students[j].marks > students[j+1].marks)) {

                struct Student temp = students[j];
                students[j] = students[j+1];
                students[j+1] = temp;
            }
        }
    }

    printf("Sorted successfully.\n");
}
