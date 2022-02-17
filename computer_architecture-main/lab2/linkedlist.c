/*Heavily taken from 
http://www.thelearningpoint.net/computer-science/data-structures-singly-linked-list
-with-c-program-source-code*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node *next;
} node;

void insert(node *pointer, int data){
	while(pointer->next != NULL){
		pointer = pointer -> next;
	}
	pointer -> next = (node *) malloc(sizeof(node));
	pointer = pointer -> next;
	pointer -> data = data;
	pointer -> next = NULL;
}

int find(node *pointer , int key){
	pointer = pointer -> next;
	while(pointer != NULL){

		if(pointer -> data == key){
			return 1;
		}

		pointer = pointer -> next;

	}
	return 0;
}

void print(node *pointer){

	if(pointer == NULL){
		return;
	}

//	printf("%ld ", pointer - pointer -> next);
	printf("%d , ",pointer -> data);
	print(pointer -> next);

}

void deleteNode(node * pointer, int data){
	while(pointer -> next != NULL && (pointer -> next) -> data != data){
		pointer = pointer -> next;
	}

	if(pointer -> next == NULL){
		printf("Element %d is not present in the list\n",data);
		return;
	}
	node *temp;
	temp = pointer -> next;
	pointer -> next = temp -> next;
	return;
}

int main(){

	node *start, *temp;
	start = (node *)malloc(sizeof(node));
	temp = start;
	temp -> next = NULL;

	int i = 0;
	for(i = 0; i < 100; i++){
	
		insert(start,i);
	
	}
	int status = find(start,50);
	status = find(start,99);
	status = find(start,10);
	printf("List is: \n");
	print(start -> next);
	printf("\n");
}
