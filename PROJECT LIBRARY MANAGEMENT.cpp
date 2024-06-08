#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct book {
    int id, available;
    char title[30], author[30];
};

void displayBook();
void addBook();
void removeBook();
void lendBook();
void returnBook();

int main() {
    int choice;
    do {
        printf("WELCOME TO THE LIBRARY\n");
        printf("1. Display Book\n");
        printf("2. Add Books\n");
        printf("3. Remove Book\n");
        printf("4. Lend Book\n");
        printf("5. Return Book\n");
        printf("6. Exit\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                displayBook();
                break;
            case 2:
                addBook();
                break;
            case 3:
                removeBook();
                break;
            case 4:
                lendBook();
                break;
            case 5:
                returnBook();
                break;
        }
    } while (choice != 6);

    return 0;
}

void displayBook() {
    struct book BOOK;
    printf("Displaying Book...\n");
    FILE *fp;
    fp = fopen("library.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }
    int firstChar = fgetc(fp);
    if (firstChar == EOF) { 
        fclose(fp);
        printf("No books added to the library.\n");
        return;
    }
    rewind(fp);
    printf("ID\tTITLE\tAuthor\tAvailable\n");
    while (fscanf(fp, "%d %s %s %d", &BOOK.id, BOOK.title, BOOK.author, &BOOK.available) != EOF) {
        printf("%d\t%s\t%s\t", BOOK.id, BOOK.title, BOOK.author);
        if (BOOK.available == 1)
            printf("Available\n");
        else
            printf("Not Available\n");
    }
    fclose(fp);
}

void addBook() {
    struct book BOOK;
    FILE *fp;
    fp = fopen("library.txt", "a");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }
    printf("Enter ID of Book: ");
    scanf("%d", &BOOK.id);
    printf("Title of Book: ");
    scanf("%s", BOOK.title);
    printf("Author of Book: ");
    scanf("%s", BOOK.author);
    BOOK.available = 1;
    fprintf(fp, "%d %s %s %d\n", BOOK.id, BOOK.title, BOOK.author, BOOK.available);
    fclose(fp);
    printf("Book Added Successfully...\n");
}

void removeBook() {
    struct book BOOK;
    int id1, flag = 0;
    printf("Removing book...\n");
    printf("Enter Book ID: ");
    scanf("%d", &id1);
    FILE *fp, *fp1;
    fp = fopen("library.txt", "r");
    fp1 = fopen("temp.txt", "w");
    if (fp == NULL || fp1 == NULL) {
        printf("Error opening file.\n");
        fclose(fp1);
        fclose(fp);
        return;
    }
    while (fscanf(fp, "%d %s %s %d", &BOOK.id, BOOK.title, BOOK.author, &BOOK.available) != EOF) {
        if (BOOK.id != id1) {
            fprintf(fp1, "%d %s %s %d\n", BOOK.id, BOOK.title, BOOK.author, BOOK.available);
        } else {
            flag = 1;
        }
    }
    fclose(fp1);
    fclose(fp);
    remove("library.txt");
    rename("temp.txt", "library.txt");
    if (flag == 1) {
        printf("Book Removed Successfully...\n");
    } else {
        printf("Book Not Found...\n");
    }
}
void lendBook() {
    struct book BOOK;
    int flag = 0;
    char title1[30];
    printf("Lending book...\n");
    printf("Enter Book Title: ");
    scanf("%s", title1);
    FILE *fp, *temp_fp;
    fp = fopen("library.txt", "r");
    temp_fp = fopen("temp.txt", "w");
    if (fp == NULL || temp_fp == NULL) {
        printf("Error opening file.\n");
        return;
    }
    while (fscanf(fp, "%d %s %s %d", &BOOK.id, BOOK.title, BOOK.author, &BOOK.available) != EOF) {
        if (strcmp(BOOK.title, title1) == 0) {
            BOOK.available = 0;
            fprintf(temp_fp, "%d %s %s %d\n", BOOK.id, BOOK.title, BOOK.author, BOOK.available);
            flag = 1;
        } else {
            fprintf(temp_fp, "%d %s %s %d\n", BOOK.id, BOOK.title, BOOK.author, BOOK.available);
        }
    }
    fclose(fp);
    fclose(temp_fp);
    remove("library.txt");
    rename("temp.txt", "library.txt");
    if (flag == 1)
        printf("Book successfully lent.\n");
    else
        printf("Book not found.\n");
}
void returnBook() {
    struct book BOOK;
    int flag = 0;
    char title1[30];
    printf("Returning book...\n");
    printf("Enter Book Title: ");
    scanf("%s", title1);
    FILE *fp, *fp1;
    fp = fopen("library.txt", "r");
    fp1 = fopen("temp.txt", "w");
    if (fp == NULL || fp1 == NULL) {
        printf("Error opening file.\n");
        return;
    }
    while (fscanf(fp, "%d %s %s %d", &BOOK.id, BOOK.title, BOOK.author, &BOOK.available) != EOF) {
        if (strcmp(BOOK.title, title1) == 0) {
        	if(BOOK.available==1)
        	{
        		printf("This Book is Already Available...\n");
        		return;
			}
            BOOK.available = 1;
            fprintf(fp1, "%d %s %s %d\n", BOOK.id, BOOK.title, BOOK.author, BOOK.available);
            flag = 1;
        } else {
            fprintf(fp1, "%d %s %s %d\n", BOOK.id, BOOK.title, BOOK.author, BOOK.available);
        }
    }
    fclose(fp);
    fclose(fp1);
    remove("library.txt");
    rename("temp.txt", "library.txt");
    if (flag == 1)
        printf("Book successfully returned.\n");
    else
        printf("Book not found.\n");
}
