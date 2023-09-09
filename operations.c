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

    while(validBookId(n)){
        printf("There already exist a book with Id: %d\n", n);
        printf("Enter valid Book Id\n");
        scanf("%d", &n);
    }  
    getchar(); 

    printf("Enter name of the Book\n");
    fgets(book, 50, stdin);
    
    printf("Enter author of the book\n");
    fgets(author, 50, stdin);

    printf("Enter the available stock\n");
    scanf("%d", &stock);

    FILE *fp;
    fp =fopen("books.txt", "a");
    if(fp==NULL){
   	 printf("Failed to open the file\n");
    }
    printf("%d %s %s %d\n", n, book, author, stock);
    fprintf(fp, "%d%s%s%d\n", n, book, author, stock);
    fclose(fp);
}

void findBookBy(char findBy[]){
    bool found = false;
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
    // scanf("%s", search);
    getchar();
    fgets(search, 50, stdin);
    search[strcspn(search, "\n")] = '\0';

    char book[50], ch, author[50];
    int stock, id;

    do {
    fscanf(fp, "%d", &id);
    char sid[50];
    sprintf(sid, "%d", id);

     fgets(book, 50, fp);
     book[strcspn(book, "\n")] = '\0';

     fgets(author, 50, fp);
     author[strcspn(author, "\n")] = '\0';

   	 ch = fscanf(fp, "%d", &stock);
   	 if (ch == EOF){
   		 break;

   	 }

   	 if((identify == 0 && strcmp(sid, search)==0) ||
   		(identify == 1 && strcmp(book, search)==0) ||
   		(identify == 2 && strcmp(author, search)==0)){
   		 printf("%5s %30s %30s %10s\n","BookId","BookName",  "Authors", "Stock");
   		 printf("%5d %30s %30s %10d\n", id, book, author, stock);
         found = true;
   	 }
    } while (ch != EOF);

    fclose(fp);
    if(!found){
        printf("\nNo book Found\n");
    }
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

bool validBookId(int bookId){
    FILE *fp;
    fp = fopen("books.txt", "r");

    if (fp == NULL){
   	 printf("Failed to open the file\n");
    }

    char book[50], ch, author[50];
    int stock, id;
    bool found = false;

    do {
    fscanf(fp, "%d", &id);

     fgets(book, 50, fp);
     book[strcspn(book, "\n")] = '\0';

     fgets(author, 50, fp);
     author[strcspn(author, "\n")] = '\0';

   	 ch = fscanf(fp, "%d", &stock);

   	 if (ch == EOF){
   		 break;

   	 }

   	 if(id == bookId){
   		return true;
   	 }
    } while (ch != EOF);

    fclose(fp);
    return false;

}

void updateStock(int bookId, int newStock){

    FILE *fp, *temp;

    temp = fopen("temp.txt", "w");
    fclose(temp);

    temp = fopen("temp.txt", "a");
    fp = fopen("books.txt", "r");

    if(fp == NULL || temp == NULL){
        printf("Failed to open the file\n");
    }

    char book[50], ch, author[50];
    int stock, id;
    do {
    fscanf(fp, "%d", &id);

     fgets(book, 50, fp);
     book[strcspn(book, "\n")] = '\0';

     fgets(author, 50, fp);
     author[strcspn(author, "\n")] = '\0';

   	 ch = fscanf(fp, "%d", &stock);

   	 if (ch == EOF){
   		 break;

   	 }

   	 if(id == bookId){
   		stock += newStock;
   	 }

    fprintf(temp, "%d%s\n%s\n%d\n", id, book, author, stock);

    } while (ch != EOF);
    fclose(fp);
    fclose(temp);

    fp = fopen("books.txt", "w");
    fclose(fp);

    fp = fopen("books.txt", "a");
    temp = fopen("temp.txt", "r");
    
    char line[1024];
    while(fgets(line, 1024, temp) != NULL){
   	 fputs(line, fp);
    }

    fclose(fp);
    fclose(temp);
    printf("Stock updated Successfully.\n");
}

void display(){

    FILE *fp;
    fp = fopen("books.txt", "r");
    if (fp == NULL){
   	 printf("Failed to open the file\n");
    }
    
    char ch, book[50], author[50];
    int id, stock;  

    printf("%5s %30s %30s %10s\n","BookId","BookName",  "Authors", "Stock");  
    do {
   	 fscanf(fp, "%d", &id);

     fgets(book, 50, fp);
     book[strcspn(book, "\n")] = '\0';

     fgets(author, 50, fp);
     author[strcspn(author, "\n")] = '\0';

   	 ch = fscanf(fp, "%d", &stock);

   	 if (ch == EOF){
   		 break;

   	 }

   	 printf("%5d %30s %30s %10d\n", id, book, author, stock);
   	 
    } while (ch != EOF);
    fclose(fp);

}

void userDashboard(char username[]){
    printf("\n1. Find a Book\n");
    printf("2. Display Books\n");
    printf("3. My Books\n");

    char n;
    scanf("%s", &n);
    if(n == '1'){
   	 findBook();
    }else if (n == '2'){
   	 display();
    }else if(n =='3'){
   	 myBooks(username);
    }else{
   	 printf("Invalid Input");
    }
    userDashboard(username);
}

void adminDashboard(){
    printf("\n1. Add a Book\n");
    printf("2. Update Stock\n");
    printf("3. Find a Book\n");
    printf("4. Display Books\n");
    printf("5. Issue Book\n");
    printf("6. Return Book\n");

    char n;
    scanf("%s", &n);
    if(n == '1'){
   	 addBook();
    }else if(n == '2'){
        printf("Enter Id of the Book.\n");
        int bookId;
        scanf("%d", &bookId);
        if(!validBookId(bookId)){
            printf("Enter valid book Id.\n");
            scanf("%d", &bookId);
        }
        printf("Enter new stock.\n");
        int newStock;
        scanf("%d", &newStock);
        updateStock(bookId, newStock);
    }else if(n == '3'){
   	 findBook();
    }else if (n == '4'){
   	 display();
    }else if (n == '5'){
   	 issue();
    }else if(n == '6'){
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

     fgets(book, 50, fp);
     book[strcspn(book, "\n")] = '\0';

     fgets(author, 50, fp);
     author[strcspn(author, "\n")] = '\0';

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
    bool issued = false, userFound = false;

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

    if(!userFound){
        printf("Invalid user name.\n");
    }else{
        printf("Book with Id %d is issued to %s.\n", bookId, username);
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

     fgets(book, 50, fp);
     book[strcspn(book, "\n")] = '\0';

     fgets(author, 50, fp);
     author[strcspn(author, "\n")] = '\0';

   	 ch = fscanf(fp, "%d", &stock);

   	 if (ch == EOF){
   		 break;

   	 }
   	 if(id == bookId){
   		 --stock;
   	 }

    fprintf(temp, "%d%s\n%s\n%d\n", id, book, author, stock);
   	 
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

     fgets(book, 50, fp);
     book[strcspn(book, "\n")] = '\0';

     fgets(author, 50, fp);
     author[strcspn(author, "\n")] = '\0';

   	 ch = fscanf(fp, "%d", &stock);

   	 if (ch == EOF){
   		 break;

   	 }
   	 if(id == bookId){
   		 ++stock;
   	 }

   	//  fprintf(temp, "%d %s %s %d\n", id, book, author, stock);
    fprintf(temp, "%d%s\n%s\n%d\n", id, book, author, stock);
   	 
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
    int book1, book2, booksArr[2], noBooksIssued = 0;
   	 
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

         if(book1 != -1){
            noBooksIssued++;
         }
         if(book2 != -1){
            noBooksIssued++;
         }
   	 }
    }while(ch != EOF);
    fclose(users);

    if(noBooksIssued == 0){
        printf("No Book issued yet.\n");
        return;
    }

    booksPointer = fopen("books.txt", "r");
    if (booksPointer == NULL){
   	 printf("Failed to open the file\n");
    }
    
    char book[50], author[50];
    int id, stock;

    printf("%5s %10s %10s\n","BookId","BookName","Authors");
    do {
    fscanf(booksPointer, "%d", &id);

     fgets(book, 50, booksPointer);
     book[strcspn(book, "\n")] = '\0';

     fgets(author, 50, booksPointer);
     author[strcspn(author, "\n")] = '\0';

   	 ch = fscanf(booksPointer, "%d", &stock);

   	 if (ch == EOF){
   		 break;

   	 }
   	 //printf("Iterating booksArr\n");
   	 for(int i=0;i< sizeof(booksArr)/sizeof(booksArr[0]);i++){
   		 //printf("%d\n", booksArr[i]);
   		 if(id == booksArr[i]){
   			 printf("%5d %10s %10s\n", id, book, author);
   		 }
   	 }
    } while (ch != EOF);
    fclose(booksPointer);

}
