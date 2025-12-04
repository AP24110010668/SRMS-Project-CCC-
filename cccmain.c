#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STUDENT_FILE "students.txt"
#define CREDENTIAL_FILE "credentials.txt"

struct Student {
    int roll;
    char name[50];
    float marks;
};

char currentRole[10];
char currentUser[50];

/* Function Declarations */
int loginSystem();
void mainMenu();
void adminMenu();
void staffMenu();
void userMenu();
void guestMenu();

void addStudent();
void displayStudents();
void searchByRoll();
void searchByName();
void updateStudent();
void deleteStudent();

/* MAIN */
int main() {
    if(loginSystem()) {
        mainMenu();
    } else {
        printf("Access Denied.\n");
    }
    return 0;
}

/* LOGIN SYSTEM */
int loginSystem() {
    char username[50], password[50];
    char fileUser[50], filePass[50], fileRole[10];

    printf("===== LOGIN =====\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    FILE *fp = fopen(CREDENTIAL_FILE, "r");
    if(!fp) {
        printf("credentials.txt missing!\n");
        return 0;
    }

    while(fscanf(fp, "%s %s %s", fileUser, filePass, fileRole) == 3) {
        if(strcmp(username, fileUser) == 0 && strcmp(password, filePass) == 0) {
            strcpy(currentRole, fileRole);
            strcpy(currentUser, fileUser);
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

/* MAIN MENU */
void mainMenu() {
    if(strcmp(currentRole, "admin") == 0)
        adminMenu();
    else if(strcmp(currentRole, "staff") == 0)
        staffMenu();
    else if(strcmp(currentRole, "user") == 0)
        userMenu();
    else
        guestMenu();
}

/* ADMIN MENU */
void adminMenu() {
    int ch;
    do {
        printf("\n===== ADMIN MENU =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search by Roll\n");
        printf("4. Search by Name\n");
        printf("5. Update Student\n");
        printf("6. Delete Student\n");
        printf("7. Logout\n");
        printf("Enter: ");
        scanf("%d", &ch);

        switch(ch) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchByRoll(); break;
            case 4: searchByName(); break;
            case 5: updateStudent(); break;
            case 6: deleteStudent(); break;
            case 7: return;
        }
    } while(1);
}

/* STAFF MENU */
void staffMenu() {
    int ch;
    do {
        printf("\n===== STAFF MENU =====\n");
        printf("1. Display Students\n");
        printf("2. Search by Roll\n");
        printf("3. Logout\n");
        printf("Enter: ");
        scanf("%d", &ch);

        switch(ch) {
            case 1: displayStudents(); break;
            case 2: searchByRoll(); break;
            case 3: return;
        }
    } while(1);
}

/* USER MENU */
void userMenu() {
    printf("\n===== USER VIEW =====\n");
    displayStudents();
}

/* GUEST MENU */
void guestMenu() {
    printf("\n===== GUEST VIEW =====\n");
    displayStudents();
}

/* ADD STUDENT */
void addStudent() {
    struct Student s;
    FILE *fp = fopen(STUDENT_FILE, "a");

    printf("Roll: ");
    scanf("%d", &s.roll);
    printf("Name: ");
    scanf("%s", s.name);
    printf("Marks: ");
    scanf("%f", &s.marks);

    fprintf(fp, "%d %s %.2f\n", s.roll, s.name, s.marks);
    fclose(fp);
    printf("Added!\n");
}

/* DISPLAY */
void displayStudents() {
    struct Student s;
    FILE *fp = fopen(STUDENT_FILE, "r");
    if(!fp) {
        printf("No file found!\n");
        return;
    }
    printf("\n===== STUDENTS =====\n");
    while(fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) == 3) {
        printf("%d %s %.2f\n", s.roll, s.name, s.marks);
    }
    fclose(fp);
}

/* SEARCH BY ROLL */
void searchByRoll() {
    struct Student s;
    int r, found = 0;

    FILE *fp = fopen(STUDENT_FILE, "r");
    printf("Enter roll: ");
    scanf("%d", &r);

    while(fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) == 3) {
        if(s.roll == r) {
            printf("Found: %d %s %.2f\n", s.roll, s.name, s.marks);
            found = 1;
        }
    }
    if(!found) printf("Not found.\n");
    fclose(fp);
}

/* SEARCH BY NAME */
void searchByName() {
    struct Student s;
    char name[50];
    int found = 0;

    FILE *fp = fopen(STUDENT_FILE, "r");
    printf("Enter name: ");
    scanf("%s", name);

    while(fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) == 3) {
        if(strcmp(s.name, name) == 0) {
            printf("Found: %d %s %.2f\n", s.roll, s.name, s.marks);
            found = 1;
        }
    }
    if(!found) printf("Not found.\n");
    fclose(fp);
}

/* UPDATE */
void updateStudent() {
    struct Student s;
    int r, found = 0;

    FILE *fp = fopen(STUDENT_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    printf("Enter roll to update: ");
    scanf("%d", &r);

    while(fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) == 3) {
        if(s.roll == r) {
            found = 1;
            printf("New Name: ");
            scanf("%s", s.name);
            printf("New Marks: ");
            scanf("%f", &s.marks);
        }
        fprintf(temp, "%d %s %.2f\n", s.roll, s.name, s.marks);
    }

    fclose(fp);
    fclose(temp);
    remove(STUDENT_FILE);
    rename("temp.txt", STUDENT_FILE);

    if(found) printf("Updated.\n");
    else printf("Not found.\n");
}

/* DELETE */
void deleteStudent() {
    struct Student s;
    int r, found = 0;

    FILE *fp = fopen(STUDENT_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    printf("Enter roll to delete: ");
    scanf("%d", &r);

    while(fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) == 3) {
        if(s.roll != r)
            fprintf(temp, "%d %s %.2f\n", s.roll, s.name, s.marks);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);
    remove(STUDENT_FILE);
    rename("temp.txt", STUDENT_FILE);

    if(found) printf("Deleted.\n");
    else printf("Not found.\n");
}
