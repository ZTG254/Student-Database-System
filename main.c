//preprocessors
#include <stdio.h> //Provides functions for input and output operations
#include <stdlib.h> //includes functions involving memory allocation
#include <string.h> //Contains functions for string manipulation

// Structure to store student information
struct Student{
    char firstName[50];
    char lastName[50];
    char admissionNumber[20];
    int currentYear;
    char course[50];
    float gpa;
};

// Function to add student information to the database
void addStudent(){   // Takes user input to add a new student to the database file.
    struct Student student;

    printf("Enter First Name: ");
    scanf("%s", student.firstName);

    printf("Enter Last Name: ");
    scanf("%s", student.lastName);

    printf("Enter Admission Number: ");
    scanf("%s", student.admissionNumber);

    printf("Enter Current Year: ");
    scanf("%d", &student.currentYear);

    printf("Enter Course: ");
    scanf("%s", student.course);

    printf("Enter GPA: ");
    scanf("%f", &student.gpa);

    // Open the database file in append mode
    FILE *file = fopen("student_database.txt", "a"); //If the file already exists, new data will be appended to the end of the file

    // Write the student details to the file
    fprintf(file, "%s %s %s %d %s %.2f\n", student.firstName, student.lastName,
            student.admissionNumber, student.currentYear, student.course, student.gpa);

    printf("Student information added successfully!\n\n");

    // Close the file
    fclose(file);
}

// Function to search for a student using their admission number
void searchStudent(){  // Searches for a student by admission number and displays their details.
    char admissionNumber[20]; //Declares a character array to store the admission number entered by the user.
    struct Student student; //Declares a variable of type struct Student to store information about a student.
    int found = 0; //value set to zero initially to indicate no matching student has been found

    printf("Enter Admission Number: ");
    scanf("%s", admissionNumber);

    // Open the database file in read mode
    FILE *file = fopen("student_database.txt", "r"); //The student information is stored this file 

    // Read each line from the file and check if the admission number matches
    //fscan function reads the data from the file and assigns it to the respective fields of the student structure.
    //strcmp to compare the admission number entered by the user with the admission number read from the file using
    while (fscanf(file, "%s %s %s %d %s %f", student.firstName, student.lastName,
                  student.admissionNumber, &student.currentYear, student.course, &student.gpa) != EOF) {
        if (strcmp(student.admissionNumber, admissionNumber) == 0) {
            printf("Student Found:\n\n");
            printf("First Name: %s\n", student.firstName);
            printf("Last Name: %s\n", student.lastName);
            printf("Admission Number: %s\n", student.admissionNumber);
            printf("Current Year: %d\n", student.currentYear);
            printf("Course: %s\n", student.course);
            printf("GPA: %.2f\n", student.gpa);
            printf("____________________________");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student not found!\n");
    }

    // Close the file
    fclose(file);
}

// Function to view all students in the database
void viewStudents() {  //  Displays details of all students in the database.
    struct Student student;

    // Open the database file in read mode
    FILE *file = fopen("student_database.txt", "r");

    // Read each line from the file and display student details
    system("cls");
    printf("\t\t***********************\n");
    printf("\t\t   Enrolled Students   \n");
    printf("\t\t***********************\n\n");
    
    while (fscanf(file, "%s %s %s %d %s %f", student.firstName, student.lastName,
                  student.admissionNumber, &student.currentYear, student.course, &student.gpa) != EOF) {
        printf("First Name: %s\n", student.firstName);
        printf("Last Name: %s\n", student.lastName);
        printf("Admission Number: %s\n", student.admissionNumber);
        printf("Current Year: %d\n", student.currentYear);
        printf("Course: %s\n", student.course);
        printf("GPA: %.2f\n", student.gpa);
        printf("--------------------\n");
    }

    // Close the file
    fclose(file);
}

// Function to authenticate the user
int authenticate() {  //Authenticates the user based on a predefined username and password.
    char username[20];
    char password[20];

    printf("\t\tEnter Username: ");
    scanf("%s", username);

    printf("\t\tEnter Password: ");
    scanf("%s", password);

    // Check if the username and password are correct
    if (strcmp(username, "admin") == 0 && strcmp(password, "pass") == 0) {
        printf("Login successful!\n");
        system("cls"); //Function to clear screen if login is successful
        return 1;
    } else {
        printf("Invalid username or password!\n"); //error handling
        return 0;
    }
}

//Main Function
//If authentication is successful, it enters a menu loop where the user can choose from various options.
int main() { 
    int choice; //Variable to store the user's menu choice.
    int authenticated = 0; //A flag to track whether the user has been authenticated (logged in).

    printf("\t\t|=================================|\n");
    printf("\t\t|     Student Database System     |\n");
    printf("\t\t|=================================|\n\n");

    while (1) { //allows the user to perform multiple operations until they decide to exit.
        if (!authenticated) {
            authenticated = authenticate(); //If the user is not authenticated, it calls the authenticate function to validate the user's login credentials
            if (!authenticated) {
                continue; //if authentication fails, the continue statement skips the rest of the loop and restarts the next iteration, prompting the user to authenticate again.
            }
        }
    //If authentication succeeds, the user is welcomed, and the loop continues to the main menu.
        printf("\t\t**********************************\n");
        printf("\t\t   Welcome!! Choose an Option     \n");
        printf("\t\t**********************************\n\n");

        printf("1. Add Student\n");
        printf("2. Search Student by Admission Number\n");
        printf("3. View Students\n");
        printf("4. Exit\n\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice){ //executes different functions based on the user's choice.
            case 1:
                addStudent();
                break;
            case 2:
                searchStudent();
                break;
            case 3:
                viewStudents();
                break;
            case 4:
                printf("Exiting program...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    }

    return 0;
}