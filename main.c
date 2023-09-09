#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "operations.h"
#include "authentication.h"

int main(){
    printf("\nIf you are new user please sign in.\n");
    printf("1. Log In\n");
    printf("2. Sign In\n");

    char n;
    printf("Enter your option.\n");
    scanf("%s",&n);

    if(n=='1'){
        logIn();
    }else if (n =='2' ){
        signIn();
        logIn();
    }else{
        printf("Invalid Input\n");
        main();
    }

    return 0;
}