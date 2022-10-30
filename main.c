/*
Write a C program to do the following into a file
1. Add a record
2. Add Bulk record
3. List Student
4. Search Student
5. Quit

Record should contain the following
Name
Roll
Marks in Mathematics
Marks in Science
Marks in English
Marks in Nepali
Marks in Social

Add a record should ask for one record at a time
Add Bulk record should ask for number of records to be added
List Student should list roll and name of all the students
Search Student should ask for roll and ask for the following options
1. Edit record
2. Delete record
3. View marksheet
4, Quit

Delete record should delete the records
Edit record should ask all the data again

View marksheet should display the marksheet of the student with the following format
Name: <Name>
Roll: <Roll>
Marks in Mathematics: <Marks in Mathematics>
Marks in Science: <Marks in Science>
Marks in English: <Marks in English>
Marks in Nepali: <Marks in Nepali>
Marks in Social: <Marks in Social>
Percentage: <Percentage>
Division: <Division>

Conditions
1. Program should be able to handle name of different lengths upto 30.
2. Program should handle invalid input

*/
#include <stdio.h>
#include <stdlib.h>

void addRecord();
void addBulkRecord();
void listStudent();
void searchStudent();
void editRecord(int);
void deleteRecord(int);
void viewMarksheet(int);
char* getDivision(float,float,float,float,float);
int main(void)
{
    int choice;
start:
    printf("1. Add a record \n2. Add Bulk record \n3. List Students \n4. Search Student \n5. Quit\n");
    printf("What is your choice?: ");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        addRecord();
        break;
    case 2:
        addBulkRecord();
        break;
    case 3:
        listStudent();
        break;
    case 4:
        searchStudent();
        break;
    case 5:
        return 0;
    default:
        printf("Invalid choice");
        break;
    }
    printf("\n");
    goto start;
    return 0;
}

void addRecord()
{
    FILE* fp;
    fp = fopen("student.dat", "a");
    if (fp == NULL) {
        printf("Error");
        exit(1);
    }
    char name[30];
    int roll;
    float math, science, english, nepali, social;
    printf("Enter name: ");
    scanf("%s", name);
    printf("Enter roll: ");
    scanf("%d", &roll);
    printf("Enter marks in math: ");
    scanf("%f", &math);
    printf("Enter marks in science: ");
    scanf("%f", &science);
    printf("Enter marks in english: ");
    scanf("%f", &english);
    printf("Enter marks in nepali: ");
    scanf("%f", &nepali);
    printf("Enter marks in social: ");
    scanf("%f", &social);
    fprintf(fp, "%s %d %f %f %f %f %f\n", name, roll, math, science, english, nepali, social);
    printf("Record added successfully\n");
    fclose(fp);
}
void addBulkRecord()
{
    FILE* fp;
    fp = fopen("student.dat", "a");
    if (fp == NULL) {
        printf("Error");
        exit(1);
    }
    int n;
    printf("Enter number of records to be added: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        char name[30];
        int roll;
        float math, science, english, nepali, social;
        printf("Enter name: ");
        scanf("%s", name);
        printf("Enter roll: ");
        scanf("%d", &roll);
        printf("Enter marks in math: ");
        scanf("%f", &math);
        printf("Enter marks in science: ");
        scanf("%f", &science);
        printf("Enter marks in english: ");
        scanf("%f", &english);
        printf("Enter marks in nepali: ");
        scanf("%f", &nepali);
        printf("Enter marks in social: ");
        scanf("%f", &social);
        fprintf(fp, "%s %d %f %f %f %f %f\n", name, roll, math, science, english, nepali, social);
    }
    printf("Records added successfully\n");
    fclose(fp);
}
void listStudent()
{
    /*
     It should display the records in the following format
     Roll               name
     1                  Ram
     2                  Shyam
     3                  Hari

     */

    FILE* fp;
    fp = fopen("student.dat", "r");
    if (fp == NULL) {
        printf("Error");
        exit(1);
    }
    char name[30];
    int roll;
    float math, science, english, nepali, social;

    printf("Roll\t\tName\n");
    while (fscanf(fp, "%s %d %f %f %f %f %f\n", name, &roll, &math, &science, &english, &nepali, &social) != EOF) {
        printf("%d\t\t%s\n", roll, name);
    }
    fclose(fp);
}
void searchStudent()
{
    int choice;
    int roll;
    printf("Enter roll: ");
    scanf("%d", &roll);
    char name[30];
    float math, science, english, nepali, social;
    printf("1. Edit record:\n");
    printf("2. Delete record:\n");
    printf("3. View marksheet:\n");
    printf("4. Quit:\n");
    printf("What is your choice?: ");
    scanf("%d", &choice);
    printf("\n");
    switch (choice) {
    case 1:
        editRecord(roll);
        break;
    case 2:
        deleteRecord(roll);
        break;
    case 3:
        viewMarksheet(roll);
        break;
    case 4:
        return;
    default:
        printf("Invalid choice");
        break;
    }
}

void editRecord(int roll)
{
    FILE *fp, *temp;
    fp = fopen("student.dat", "r");
    if (fp == NULL) {
        printf("Error");
        exit(1);
    }
    temp = fopen("temp.dat", "w");
    if (temp == NULL) {
        printf("Error");
        exit(1);
    }
    char name[30];
    int roll1= roll;
    float math, science, english, nepali, social;
    while (fscanf(fp, "%s %d %f %f %f %f %f\n", name, &roll, &math, &science, &english, &nepali, &social) != EOF) {
        if (roll1 == roll) {
            printf("Enter name: ");
            scanf("%s", name);
            printf("Enter marks in math: ");
            scanf("%f", &math);
            printf("Enter marks in science: ");
            scanf("%f", &science);
            printf("Enter marks in english: ");
            scanf("%f", &english);
            printf("Enter marks in nepali: ");
            scanf("%f", &nepali);
            printf("Enter marks in social: ");
            scanf("%f", &social);
            fprintf(temp, "%s %d %f %f %f %f %f\n", name, roll, math, science, english, nepali, social);
        } else {
            fprintf(temp, "%s %d %f %f %f %f %f\n", name, roll, math, science, english, nepali, social);
        }
    }
    fclose(fp);
    fclose(temp);
    remove("student.dat");
    rename("temp.dat", "student.dat");
    printf("Record edited successfully\n");
}
void deleteRecord(int roll)
{
    FILE* fp;
    fp = fopen("student.dat", "r");
    if (fp == NULL) {
        printf("Error");
        exit(1);
    }
    FILE* fp1;
    fp1 = fopen("temp.dat", "w");
    if (fp1 == NULL) {
        printf("Error");
        exit(1);
    }
    char name[30];
    int roll1;
    float math, science, english, nepali, social;
    while (fscanf(fp, "%s %d %f %f %f %f %f\n", name, &roll1, &math, &science, &english, &nepali, &social) != EOF) {
        if (roll1 != roll) {
            fprintf(fp1, "%s %d %f %f %f %f %f\n", name, roll1, math, science, english, nepali, social);
        }
    }
    fclose(fp);
    fclose(fp1);
    remove("student.dat");
    rename("temp.dat", "student.dat");
}
void viewMarksheet(int roll)
{
    FILE *fp;
    fp = fopen("student.dat", "r");
    if (fp == NULL) {
        printf("Error");
        exit(1);
    }
    char name[30];
    int roll1;
    float math, science, english, nepali, social;
    while (fscanf(fp, "%s %d %f %f %f %f %f\n", name, &roll1, &math, &science, &english, &nepali, &social) != EOF) {
        if (roll1 == roll) {
            printf("Name: %s\n", name);
            printf("Roll: %d\n", roll1);
            printf("Math: %f\n", math);
            printf("Science: %f\n", science);
            printf("English: %f\n", english);
            printf("Nepali: %f\n", nepali);
            printf("Social: %f\n", social);
            printf("Percentage: %f\n", (math + science + english + nepali + social) / 5);
            printf("Division: %s\n", getDivision(math, science, english, nepali, social));
            fclose(fp);
            return;
        }
    }
    printf("Record not found\n");
    fclose(fp);
}
char* getDivision(float math, float science, float english, float nepali, float social)
{
    if(math<40 || science<40 || english<40 || nepali<40 || social<40){
        return "Fail";
    }
    float percentage = (math + science + english + nepali + social) / 5;
    if (percentage >= 80) {
        return "First";
    } else if (percentage >= 60) {
        return "Second";
    } else if (percentage >= 40) {
        return "Third";
    } else {
        return "Fail";
    }
}
