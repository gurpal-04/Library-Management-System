#include <regex.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "authentication.h"
#include "operations.h"


bool emailValidation(char str[]) {
    char *pattern = "^[A-Za-z0-9+_.-]+@(.+)$";

    regex_t emailPattern;

    int ret = regcomp(&emailPattern, pattern, REG_EXTENDED);
    if(ret){
        char error_msg[100];
        regerror(ret, &emailPattern, error_msg, sizeof(error_msg));
        printf("Regular exp compile failed\n");
        printf("Error Message: %s", error_msg);
    }

    ret = regexec(&emailPattern, str, 0, NULL, 0);

	if(ret == 0){
		return true;
	}
    return false; 
}

bool passwordValidation(char str[]){
    char *pattern = "^[A-Za-z0-9!@#$%^&*()_+]{8,16}$";

    regex_t passwordPattern;

    int ret = regcomp(&passwordPattern, pattern, REG_EXTENDED);
    if(ret){
        char error_msg[100];
        regerror(ret, &passwordPattern, error_msg, sizeof(error_msg));
        printf("Regular exp compile failed\n");
        printf("Error Message: %s", error_msg);
    }

    ret = regexec(&passwordPattern, str, 0, NULL, 0);

	if(ret == 0){
        regfree(&passwordPattern);
		return true;
	}
    regfree(&passwordPattern);
    return false;
}

void signIn(){
    FILE *fp;
    char username[50], password[17];
    printf("Enter your email:\n");
    scanf("%s", username);
    while(!emailValidation(username)){
	    printf("Enter valid email address\n");
	    scanf("%s", username);
    }
    printf("Enter password\nYour password should be at least 8 character and maximun 16 character.\n");
    scanf("%s", password);
    while(!passwordValidation(password)){
        printf("Enter valid password:\n");
        scanf("%s", password);
    }

    fp = fopen("users.txt", "a");
    if(fp == NULL){
   	 printf("Failed to open the file\n");
    }

    fprintf(fp, "%s %s %d %d\n", username, password, -1, -1);
    fclose(fp);
    userDashboard(username);
}

bool adminLogIn(char username[50], char password[17]){

    if (strcmp(username, "admin@admin.com") == 0 &&
   		 strcmp(password, "admin") == 0){
   	 printf("admin login successful\n");
   	 return true;
    } else{
   	 printf("login failed\n");
   	 return false;
    }

}


bool userLogIn(char username[50], char password[17]){
    FILE *fp;
    fp = fopen("users.txt", "r");

    
    if(fp == NULL){
   	 printf("Failed to open the file\n");
    }

    char Username[50], Password[17], ch;
    int book1, book2;
    do{
   	 fscanf(fp, "%s", Username);
   	 ch = fscanf(fp, "%s", Password);
   	 ch = fscanf(fp, "%d", &book1);
   	 ch = fscanf(fp, "%d", &book2);

   	 if(ch == EOF){
   		 break;
   	 }
    

   	 if ((strcmp(username, Username) == 0) &&
   		 (strcmp(password, Password) == 0)){
   		 printf("Successful login\n");
   		 return true;
   	 }
    }while(ch != EOF);
    
    fclose(fp);

    printf("Login failed\n");
    return false;
}

void logIn(){
    printf("\nHow you want to login?\n");
    printf("1. Login as user\n");
    printf("2. Login as admin\n");
    
    printf("Enter the option\n");
    char n;
    scanf("%s",&n);
    // printf("%s",n);
    if(n!='1' && n!='2'){
        printf("Enter valid option.\n");
        logIn();
    }

    char username[50], password[17];
    printf("Enter email address: \n");
    scanf("%s", username);
    printf("Password: \n");
    scanf("%s", password);
    
    if (n=='1' && userLogIn(username, password)){
   	 userDashboard(username);
    }else if(n=='2' && adminLogIn(username, password)){
   	 adminDashboard();
    }else{
     printf("Invalid credentials. Try again.\n");
   	 logIn();
    }
}
