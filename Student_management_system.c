/*
 * LLP.c
 *
 *  Created on: Aug 15, 2024
 *      Author: samaa
 */
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

//----------Structs/Node--------//
struct student{
	int id;
	char name[50];
	int age;
	float gpa;
};

struct node{
	struct student data;
	struct node *next;
};

struct node *head = NULL;
struct node *current = NULL;
struct node *prev = NULL;

//----------FN Declaration--------//
void addStudent(const struct student *const ptr);
void displayStudents(void);
void searchStudentByID(int id);
void updateStudent(int id);
float calculateAverageGPA(void);
void searchHighestGPA(void);
void deleteStudent(int id);
//-----------------MAIN------------------------//
int main (void){
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	int exit = 0, choice;
	float avgGpa=0;

	while (exit != 1){
		printf("--------------------------------------------------------\n");
		printf("Choose an action: \n");
		printf("1. Add Student \n");
		printf("2. Display Students \n");
		printf("3. Search for Student by ID \n");
		printf("4. Update Student Information by ID \n");
		printf("5. Delete Student \n");
		printf("6. Calculate average GPA \n");
		printf("7. Search for student with the highest GPA \n");
		printf("8. Exit \n");
		printf("Enter Choice: ");
		/*Take choice from user*/
		scanf("%d", &choice);
		printf("--------------------------------------------------------\n");

		switch(choice){
		case 1:
			struct student student;
			printf("Enter Student ID: ");
			scanf("%d", &(student.id));
			if(student.id < 0){
				printf("Enter a valid ID");
				scanf("%d", &(student.id));
			}

			printf("Enter name: ");
			scanf("%s", student.name);

			printf("Enter age: ");
			scanf("%d", &(student.age));
			if(student.age < 0){
				printf("Enter a valid age");
				scanf("%d", &(student.age));
			}

			printf("Enter gpa: ");
			scanf("%f", &(student.gpa));
			if(student.gpa < 0){
				printf("Enter a valid GPA");
				scanf("%f", &(student.gpa));
			}

			addStudent(&student);

			break;

		case 2:
			displayStudents();
			break;

		case 3:
			int id;
			printf("Enter student ID to search: ");
			scanf("%d", &id);
			searchStudentByID(id);
			break;

		case 4:
			printf("Enter student ID to update their data: ");
			scanf("%d", &id);
			updateStudent(id);
			break;

		case 5:
			printf("Enter student ID you want to delete: ");
			scanf("%d", &id);
			deleteStudent(id);
			break;

		case 6:
			avgGpa = calculateAverageGPA();
			printf("The average GPA of all students is: %.2f\n", avgGpa);
			break;


		case 7:
			searchHighestGPA();
			break;

		case 8:
			printf("Program exit successful!");
			printf("--------------------------------------------------------\n");
			exit = 1;
			break;

		default:
			printf("Invalid choice!");
		}
	}
	return 0;
}

//-----------------FN DEF--------------------//
void addStudent(const struct student *const ptr){
	struct node *link = (struct node*) malloc(sizeof(struct node));

	link->next = NULL;

	if(head == NULL){
		head = link;
		link->data.id = ptr->id;
		strcpy(link->data.name, ptr->name);
		link->data.age = ptr->age;
		link->data.gpa = ptr->gpa;
		printf("Student added successfully!\n");
		return;
	}

	current = head;

	while (current != NULL) {
		if (current->data.id == ptr->id) {
			printf("This ID already exists!\n");
			free(link);  // Free the memory if ID already exists.
			return;
		}

		if (current->next == NULL) {
			current->next = link;
			printf("Student added successfully!\n");
			return;
		}

		current = current->next;
	}

	current->next = link;
	link->data.id = ptr->id;
	strcpy(link->data.name, ptr->name);
	link->data.age = ptr->age;
	link->data.gpa = ptr->gpa;
	printf("Student added successfully!\n");

}

void displayStudents(void){

	if(head == NULL){
		printf("There are no students present!\n");
	}
	current = head;

	while(current != NULL){
		printf("[ID: %d, Name: %s, Age: %d, GPA: %.2f]\n",current->data.id, current->data.name, current->data.age, current->data.gpa);
		current = current->next;
	}
}

void searchStudentByID(int id){

	if(head == NULL){
		printf("There are no students present!\n");
		return;
	}

	current = head;

	while(current != NULL){

		if(current->data.id == id){
			printf("Student found: \n");
			printf("ID: %d, Name: %s, Age: %d, GPA: %.2f\n",current->data.id, current->data.name, current->data.age, current->data.gpa);
			return;
		}
		current = current->next;
	}
	/*Student not found*/
	printf("Student with ID %d was not found!\n", id);

}

void updateStudent(int id){

	if(head == NULL){
		printf("There are no students present!\n");
		return;
	}

	current = head;

	while(current != NULL){

		if(current->data.id == id){
			printf("Enter Student ID: ");
			scanf("%d", &(current->data.id));

			printf("Enter name: ");
			scanf("%s", current->data.name);

			printf("Enter age: ");
			scanf("%d", &(current->data.age));

			printf("Enter gpa: ");
			scanf("%f", &(current->data.gpa));

			printf("Student updated successfully!");
			return;
		}
		current = current->next;
	}
	/*Student not found*/
	printf("Student with ID %d was not found!\n", id);
}

float calculateAverageGPA(void){

	float avgGpa=0, count=0, sum=0;
	if(head == NULL){
		avgGpa = 0.0;
		return avgGpa;
	}

	current = head;

	while(current != NULL){
		sum += current->data.gpa;
		count++;
		current = current->next;
	}

	avgGpa = sum/count;
	return avgGpa;
}

void searchHighestGPA(void){

	if(head == NULL){
		printf("There are no students present!\n");
		return;
	}

    float maxGpa = head->data.gpa;
    current = head;
    struct node *maxGpaStudent = head;

    while (current != NULL) {
        if (current->data.gpa > maxGpa) {
            maxGpa = current->data.gpa;
            maxGpaStudent = current;
        }
        current = current->next;
    }

    printf("The student with the highest GPA is: \n");
    printf("ID: %d, Name: %s, Age: %d, GPA: %.2f\n", maxGpaStudent->data.id, maxGpaStudent->data.name, maxGpaStudent->data.age, maxGpaStudent->data.gpa);
}

void deleteStudent(int id){

	struct node *delete = NULL;

	if(head == NULL){
		printf("There are no students present!\n");
		return;
	}

	if(head->data.id == id){
		delete = head;
		head = head->next;
		printf("The student with ID %d was deleted successfully!\n", id);
		free(delete);
		return;
	}
	prev = head;
	current = head->next;

	while(current != NULL){
		if(current->data.id == id){
			delete = current;
			prev->next = current->next;
			free(delete);
			printf("The student with ID %d was deleted successfully!\n", id);
			return;

		}
		prev = current;
		current = current->next;
	}

	/*Student not found*/
	printf("Student with ID %d was not found!\n", id);
}
