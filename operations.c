#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "operations.h"

void addBook(){
    int n, stock;
    char book[50], author[50];

    printf("\nEnter id of the book\n");
    scanf("%d", &n);
    
    printf("Enter name of the Book\n");
    scanf("%s", book);
    
    printf("Enter author of the book\n");
    scanf("%s", author);

    printf("Enter the available stock\n");
    scanf("%d", &stock);

    FILE *fp;
    fp =fopen("books.txt", "a");
    if(fp==NULL){
   	 printf("Failed to open the file\n");
    }

    fprintf(fp, "%d %s %s %d\n", n, book, author, stock);
    fclose(fp);
}

void findBookBy(char findBy[]){
    FILE *fp;
    fp = fopen("books.txt", "r");
    if (fp == NULL){
   	 printf("Failed to open the file\n");
    }

    int identify;
    if(strcmp(findBy, "Book") == 0){
   	 identify =1;
   	 printf("Enter name of the Book:\n");
    }
    else if(strcmp(findBy, "Author") == 0){
   	 identify =2;
   	 printf("Enter name of the Author:\n");
    }
    else{
   	 identify = 0;
   	 printf("Enter the Book id:\n");
    }

    char search[50];
    scanf("%s", search);

    char book[50], ch;
    char id[50], author[50];
    int stock;

    do {
   	 fscanf(fp, "%s", id);
   	 ch = fscanf(fp, "%s", book);
   	 ch = fscanf(fp, "%s", author);
   	 ch = fscanf(fp, "%d", &stock);

   	 if (ch == EOF){
   		 break;

   	 }

   	 if((identify == 0 && strcmp(id, search)==0) ||
   		(identify == 1 && strcmp(book, search)==0) ||
   		(identify == 2 && strcmp(author, search)==0)){
   		 printf("%5s %10s %10s %10s\n","BookId","BookName",  "Authors", "Stock");
   		 printf("%5s %10s %10s %10d\n", id, book, author, stock);
   	 }
    } while (ch != EOF);

    fclose(fp);

}

void findBook(){
    printf("\nHow you want to search the book:\n");
    printf("1. by Book number:\n");
    printf("2. by Book name:\n");
    printf("3. by Author's name:\n");

    int n;
    scanf("%d", &n);
    if(n == 1){
   	 findBookBy("id");
    }else if(n == 2){
   	 findBookBy("Book");
    }else if(n == 3){
   	 findBookBy("Author");
    }else{
   	 printf("Invalid Input\n");
    }

}

void display(){

    FILE *fp;
    fp = fopen("books.txt", "r");
    if (fp == NULL){
   	 printf("Failed to open the file\n");
    }
    
    char ch, book[50], author[50];
    int id, stock;    
    do {
   	 fscanf(fp, "%d", &id);
   	 ch = fscanf(fp, "%s", book);
   	 ch = fscanf(fp, "%s", author);
   	 ch = fscanf(fp, "%d", &stock);

   	 if (ch == EOF){
   		 break;

   	 }

   	 
   	 printf("%5s %10s %10s %10s\n","BookId","BookName",  "Authors", "Stock");
   	 printf("%5d %10s %10s %10d\n", id, book, author, stock);
   	 
    } while (ch != EOF);
    fclose(fp);

}

void userDashboard(char username[]){
    printf("\n1. Find a Book\n");
    printf("2. Display Books\n");
    printf("3. My Books\n");

    int n;
    scanf("%d", &n);
    if(n == 1){
   	 findBook();
    }else if (n == 2){
   	 display();
    }else if(n ==3){
   	 myBooks(username);
    }else{
   	 printf("Invalid Input");
    }
    userDashboard(username);
}

void adminDashboard(){
    printf("\n1. Add a Book\n");
    printf("2. Find a Book\n");
    printf("3. Display Books\n");
    printf("4. Issue Book\n");
    printf("5. Return Book\n");

    int n;
    scanf("%d", &n);
    if(n == 1){
   	 addBook();
    }else if(n == 2){
   	 findBook();
    }else if (n == 3){
   	 display();
    }else if (n == 4){
   	 issue();
    }else if(n == 5){
   	 returnBook();
    }else{
   	 printf("Invalid Input\n");
    }

    adminDashboard();
}

bool isAvailable(int bookId){
    
    FILE *fp;

    fp = fopen("books.txt", "r");
    if (fp == NULL){
   	 printf("Failed to open the file\n");
    }

    char ch, book[50], author[50];
    int id, stock;    
    do {
   	 fscanf(fp, "%d", &id);
   	 ch = fscanf(fp, "%s", book);
   	 ch = fscanf(fp, "%s", author);
   	 ch = fscanf(fp, "%d", &stock);

   	 if (ch == EOF){
   		 break;

   	 }
   	 if(id == bookId && stock>0){
   		 return true;
   	 }
   	 
    } while (ch != EOF);
    fclose(fp);
    return false;
}

void issue(){
    char username[50];
    int bookId;
    bool issued = false;

    printf("Enter Username:\n");
    scanf("%s", username);

    printf("Enter BookId\n");
    scanf("%d", &bookId);

    if(!isAvailable(bookId)){
   	 printf("Sorry! Book is out of stock\n");
   	 return;
    }

    FILE *fp, *temp;
    fp = fopen("users.txt", "r");
    temp = fopen("temp.txt", "w");
    fclose(temp);
    temp = fopen("temp.txt", "a");


    char ch, Username[50], Password[17];
    int book1, book2;
   	 
    do {
   	 
   	 ch = fscanf(fp, "%s", Username);
   	 ch = fscanf(fp, "%s", Password);
   	 ch = fscanf(fp, "%d", &book1);
   	 ch = fscanf(fp, "%d", &book2);
   	 

   	 if (ch == EOF){
   		 break;

   	 }
   	 
   	 //printf("unmae:%s uname from file:%s\n",username,Username);
   	 if(strcmp(Username,username) == 0){
   		 //printf("username not matched\n");
   		 
   		 if(bookId == book1 || bookId == book2){
   			 printf("You can not issue same book again\n");
   			 break;
   		 }

   		 if(book1 == -1){
   			 book1 = bookId;
   			 issued = true;
   		 }else if(book2 = -1){
   			 book2 = bookId;
   			 issued = true;
   		 }else{
   			 printf("Can't Issue more than two Books\n");
   			 break;
   		 }

   	 }
   	 

   	 fprintf(temp, "%s %s %d %d\n", Username, Password, book1, book2);
   	 
    } while (ch != EOF);
    fclose(fp);
    fclose(temp);

    fp = fopen("users.txt", "w");
    fclose(fp);

    fp = fopen("users.txt", "a");
    temp = fopen("temp.txt", "r");
    
    char line[1024];
    while(fgets(line, 1024, temp) != NULL){
   	 //printf("line appended in users.txt\n");
   	 fputs(line, fp);
    }

    fclose(fp);
    fclose(temp);

    if(issued){
   	 decrementStock(bookId);
    }

}

void returnBook(){
    char username[50];
    int bookId;
    bool returned = false;

    printf("Enter Username:\n");
    scanf("%s", username);

    printf("Enter BookId\n");
    scanf("%d", &bookId);

    FILE *fp, *temp;
    fp = fopen("users.txt", "r");
    temp = fopen("temp.txt", "w");
    fclose(temp);
    temp = fopen("temp.txt", "a");


    char ch, Username[50], Password[17];
    int book1, book2;
   	 
    do {
   	 
   	 ch = fscanf(fp, "%s", Username);
   	 ch = fscanf(fp, "%s", Password);
   	 ch = fscanf(fp, "%d", &book1);
   	 ch = fscanf(fp, "%d", &book2);
   	 

   	 if (ch == EOF){
   		 break;

   	 }
   	 
   	 //printf("unmae:%s uname from file:%s\n",username,Username);
   	 if(strcmp(Username,username) == 0){
   		 //printf("username not matched\n");
   	 
   		 if(book1 == bookId){
   			 book1 = -1;
   			 returned = true;
   		 }else if(book2 == bookId){
   			 book2 = -1;
   			 returned = true;
   		 }
   		 else{
   			 printf("Wrong BookId or Username\n");
   			 return;
   		 }

    
   	 }
   	 

   	 fprintf(temp, "%s %s %d %d\n", Username, Password, book1, book2);
   	 
    } while (ch != EOF);
    fclose(fp);
    fclose(temp);

    fp = fopen("users.txt", "w");
    fclose(fp);

    fp = fopen("users.txt", "a");
    temp = fopen("temp.txt", "r");
    
    char line[1024];
    while(fgets(line, 1024, temp) != NULL){
    //    printf("line appended in users.txt\n");
   	 fputs(line, fp);
    }

    fclose(fp);
    fclose(temp);
    
    if(returned){
   	 incrementStock(bookId);
    }
}

void decrementStock(int bookId){

    FILE *fp, *temp;
    
    temp = fopen("temp.txt", "w");
    fclose(temp);

    temp = fopen("temp.txt", "a");
    fp = fopen("books.txt", "r");
    if (fp == NULL || temp == NULL){
   	 printf("Failed to open the file\n");
    }

    char ch, book[50], author[50];
    int id, stock;    
    do {
   	 fscanf(fp, "%d", &id);
   	 ch = fscanf(fp, "%s", book);
   	 ch = fscanf(fp, "%s", author);
   	 ch = fscanf(fp, "%d", &stock);

   	 if (ch == EOF){
   		 break;

   	 }
   	 if(id == bookId){
   		 --stock;
   	 }

   	 fprintf(temp, "%d %s %s %d\n", id, book, author, stock);
   	 
    } while (ch != EOF);
    fclose(fp);
    fclose(temp);

    fp = fopen("books.txt", "w");
    fclose(fp);

    fp = fopen("books.txt", "a");
    temp = fopen("temp.txt", "r");
    
    char line[1024];
    while(fgets(line, 1024, temp) != NULL){
   	 //printf("line appended in users.txt\n");
   	 fputs(line, fp);
    }

    fclose(fp);
    fclose(temp);
}

void incrementStock(int bookId){

    FILE *fp, *temp;
    
    temp = fopen("temp.txt", "w");
    fclose(temp);

    temp = fopen("temp.txt", "a");
    fp = fopen("books.txt", "r");
    if (fp == NULL || temp == NULL){
   	 printf("Failed to open the file\n");
    }

    char ch, book[50], author[50];
    int id, stock;    
    do {
   	 fscanf(fp, "%d", &id);
   	 ch = fscanf(fp, "%s", book);
   	 ch = fscanf(fp, "%s", author);
   	 ch = fscanf(fp, "%d", &stock);

   	 if (ch == EOF){
   		 break;

   	 }
   	 if(id == bookId){
   		 ++stock;
   	 }

   	 fprintf(temp, "%d %s %s %d\n", id, book, author, stock);
   	 
    } while (ch != EOF);
    fclose(fp);
    fclose(temp);

    fp = fopen("books.txt", "w");
    fclose(fp);

    fp = fopen("books.txt", "a");
    temp = fopen("temp.txt", "r");
    
    char line[1024];
    while(fgets(line, 1024, temp) != NULL){
   	 //printf("line appended in users.txt\n");
   	 fputs(line, fp);
    }

    fclose(fp);
    fclose(temp);
}

void myBooks(char username[]){

    FILE *users, *booksPointer;

    users = fopen("users.txt","r");
    
    char ch, Username[50], Password[17];
    int book1, book2, booksArr[2];
   	 
    do {
   	 
   	 ch = fscanf(users, "%s", Username);
   	 ch = fscanf(users, "%s", Password);
   	 ch = fscanf(users, "%d", &book1);
   	 ch = fscanf(users, "%d", &book2);

   	 if(ch == EOF){
   		 break;
   	 }
   	 
   	 //printf("%s %s\n",Username,username);    
   	 if(strcmp(Username,username) == 0){
   		 //printf("User matched\n");
   		 booksArr[0] = book1;
   		 booksArr[1] = book2;
   	 }
    }while(ch != EOF);
    fclose(users);


    booksPointer = fopen("books.txt", "r");
    if (booksPointer == NULL){
   	 printf("Failed to open the file\n");
    }
    
    char book[50], author[50];
    int id, stock;    
    bool found = false;

    printf("%5s %10s %10s\n","BookId","BookName","Authors");
    do {
   	 ch = fscanf(booksPointer, "%d", &id);
   	 ch = fscanf(booksPointer, "%s", book);
   	 ch = fscanf(booksPointer, "%s", author);
   	 ch = fscanf(booksPointer, "%d", &stock);

   	 if (ch == EOF){
   		 break;

   	 }
   	 //printf("Iterating booksArr\n");
   	 for(int i=0;i< sizeof(booksArr)/sizeof(booksArr[0]);i++){
   		 //printf("%d\n", booksArr[i]);
   		 if(id == booksArr[i]){
			found = true;
   			 printf("%5d %10s %10s\n", id, book, author);
   		 }
   	 }
    } while (ch != EOF);
    fclose(booksPointer);


    if(!found()){
	printf(“No book issued\n”):
    }
}
