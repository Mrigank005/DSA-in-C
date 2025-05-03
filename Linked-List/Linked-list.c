#include <stdio.h>
#include <stdlib.h>

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

#include "singly-linked-list.c"
void singlyLinkedListMenu()
{
    printf("\nSingly Linked List Menu\n");
    singly_main();
}

#include "doubly-linked-list.c"
void doublyLinkedListMenu()
{
    printf("\nDoubly Linked List Menu\n");
    doubly_main();
}

#include "circular-linked-list.c"
void circularLinkedListMenu()
{
    printf("\nCircular Linked List Menu\n");
    circular_main();
}

#include "doubly-circular-linked-list.c"
void doublyCircularLinkedListMenu()
{
    printf("\nDoubly Circular Linked List Menu\n");
    CDLL_run();
}

void displayMainMenu()
{
    printf("\nMain Menu:\n");
    printf("1. Singly Linked List\n");
    printf("2. Doubly Linked List\n");
    printf("3. Circular Linked List\n");
    printf("4. Doubly Circular Linked List\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

int main()
{
    int choice;
    char continue_choice;

    do
    {
        displayMainMenu();
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice)
        {
        case 1:
            singlyLinkedListMenu();
            break;
        case 2:
            doublyLinkedListMenu();
            break;
        case 3:
            circularLinkedListMenu();
            break;
        case 4:
            doublyCircularLinkedListMenu();
            break;
        case 5:
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }

        clearInputBuffer();
        printf("\nDo you want to go to Main Menu? (y/n): ");
        scanf(" %c", &continue_choice);

    } while (continue_choice == 'y' || continue_choice == 'Y');

    printf("Exiting...\n");
    return 0;
}