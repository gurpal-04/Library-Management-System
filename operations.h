#include <stdbool.h>
void addBook();
void findBookBy(char findBy[]);
void findBook();
void display();
void userDashboard(char username[]);
void adminDashboard();
bool isAvailable(int bookId);
void issue();
void returnBook();
void decrementStock(int bookId);
void incrementStock(int bookId);
void myBooks(char username[]);
void updateStock(int, int);
bool validBookId(int);