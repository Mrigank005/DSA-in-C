#include <stdio.h>
#include <stdlib.h>

typedef struct CircularNode
{
    int val;
    struct CircularNode *next;
} CircularNode;

typedef struct CircularLinkedList
{
    CircularNode *head;
    CircularNode *tail;
    int size;
} CircularLinkedList;

void circular_insertAtHead(CircularLinkedList *ll, int val)
{
    CircularNode *temp = (CircularNode *)malloc(sizeof(CircularNode));
    temp->val = val;

    if (ll->size == 0)
    {
        ll->head = ll->tail = temp;
        temp->next = temp; // Circular link: tail points to head
    }
    else
    {
        temp->next = ll->head;
        ll->head = temp;
        ll->tail->next = temp; // Update tail's next to point to the new head
    }

    ll->size++;
}

void circular_insertAtTail(CircularLinkedList *ll, int val)
{
    CircularNode *temp = (CircularNode *)malloc(sizeof(CircularNode));
    temp->val = val;

    if (ll->size == 0)
    {
        ll->head = ll->tail = temp;
        temp->next = temp; // Circular link: tail points to head
    }
    else
    {
        temp->next = ll->head; // New tail points to head
        ll->tail->next = temp; // Old tail points to new tail
        ll->tail = temp;       // Update tail
    }

    ll->size++;
}

void circular_insertAtIdx(CircularLinkedList *ll, int val, int idx)
{
    if (idx < 0 || idx > ll->size)
    {
        printf("Index out of bounds\n");
        return;
    }

    if (idx == 0)
    {
        circular_insertAtHead(ll, val);
        return;
    }
    else if (idx == ll->size)
    {
        circular_insertAtTail(ll, val);
        return;
    }

    CircularNode *new = (CircularNode *)malloc(sizeof(CircularNode));
    new->val = val;

    CircularNode *temp = ll->head;
    for (int i = 0; i < idx - 1; i++)
    {
        temp = temp->next;
    }

    new->next = temp->next;
    temp->next = new;

    ll->size++;
}

void circular_insertAfterNode(CircularLinkedList *ll, int val, int targetVal)
{
    CircularNode *temp = ll->head;
    do
    {
        if (temp->val == targetVal)
        {
            CircularNode *new = (CircularNode *)malloc(sizeof(CircularNode));
            new->val = val;
            new->next = temp->next;
            temp->next = new;

            if (temp == ll->tail)
            {
                ll->tail = new; // Update tail if inserting after tail
            }

            ll->size++;
            return;
        }
        temp = temp->next;
    } while (temp != ll->head);

    printf("Node with value %d not found\n", targetVal);
}

void circular_insertBeforeNode(CircularLinkedList *ll, int val, int targetVal)
{
    if (ll->head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    if (ll->head->val == targetVal)
    {
        circular_insertAtHead(ll, val);
        return;
    }

    CircularNode *prev = ll->head;
    CircularNode *current = ll->head->next;

    do
    {
        if (current->val == targetVal)
        {
            CircularNode *new = (CircularNode *)malloc(sizeof(CircularNode));
            new->val = val;
            new->next = current;
            prev->next = new;

            ll->size++;
            return;
        }
        prev = current;
        current = current->next;
    } while (current != ll->head);

    printf("Node with value %d not found\n", targetVal);
}

void circular_bubbleSort(CircularLinkedList *ll, int ascending)
{
    if (ll->size <= 1)
    {
        return;
    }

    int swapped;
    CircularNode *ptr1;
    CircularNode *ptr = NULL;

    do
    {
        swapped = 0;
        ptr1 = ll->head;

        while (ptr1->next != ptr)
        {
            if ((ascending && ptr1->val > ptr1->next->val) || (!ascending && ptr1->val < ptr1->next->val))
            {
                int temp = ptr1->val;
                ptr1->val = ptr1->next->val;
                ptr1->next->val = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        ptr = ptr1;
    } while (swapped);
}

void circular_insertInSortedList(CircularLinkedList *ll, int val, int ascending)
{
    circular_bubbleSort(ll, ascending);

    CircularNode *new = (CircularNode *)malloc(sizeof(CircularNode));
    new->val = val;

    if (ll->size == 0)
    {
        ll->head = ll->tail = new;
        new->next = new; // Circular link
    }
    else
    {
        CircularNode *prev = NULL;
        CircularNode *current = ll->head;

        do
        {
            if ((ascending && current->val >= val) || (!ascending && current->val <= val))
            {
                break;
            }
            prev = current;
            current = current->next;
        } while (current != ll->head);

        if (prev == NULL)
        {
            new->next = ll->head;
            ll->head = new;
            ll->tail->next = new; // Update tail's next to point to new head
        }
        else
        {
            new->next = current;
            prev->next = new;

            if (current == ll->head)
            {
                ll->tail = new; // Update tail if inserting at the end
            }
        }
    }

    ll->size++;
}

void circular_deleteAtHead(CircularLinkedList *ll)
{
    if (ll->size == 0)
    {
        printf("List is empty\n");
        return;
    }

    CircularNode *temp = ll->head;

    if (ll->size == 1)
    {
        ll->head = ll->tail = NULL;
    }
    else
    {
        ll->head = ll->head->next;
        ll->tail->next = ll->head; // Update tail's next to point to new head
    }

    free(temp);
    ll->size--;
}

void circular_deleteAtTail(CircularLinkedList *ll)
{
    if (ll->size == 0)
    {
        printf("List is empty\n");
        return;
    }

    if (ll->size == 1)
    {
        circular_deleteAtHead(ll);
        return;
    }

    CircularNode *temp = ll->head;
    while (temp->next != ll->tail)
    {
        temp = temp->next;
    }

    free(ll->tail);
    ll->tail = temp;
    ll->tail->next = ll->head; // Update tail's next to point to head

    ll->size--;
}

void circular_deleteAtIdx(CircularLinkedList *ll, int idx)
{
    if (idx < 0 || idx >= ll->size)
    {
        printf("Index out of bounds\n");
        return;
    }

    if (idx == 0)
    {
        circular_deleteAtHead(ll);
        return;
    }
    else if (idx == ll->size - 1)
    {
        circular_deleteAtTail(ll);
        return;
    }

    CircularNode *temp = ll->head;
    for (int i = 0; i < idx - 1; i++)
    {
        temp = temp->next;
    }

    CircularNode *toDelete = temp->next;
    temp->next = toDelete->next;

    free(toDelete);
    ll->size--;
}

void circular_deleteAfterNode(CircularLinkedList *ll, int targetVal)
{
    CircularNode *temp = ll->head;
    do
    {
        if (temp->val == targetVal)
        {
            if (temp->next == ll->head)
            {
                printf("No node after the node with value %d\n", targetVal);
                return;
            }

            CircularNode *toDelete = temp->next;
            temp->next = toDelete->next;

            if (toDelete == ll->tail)
            {
                ll->tail = temp; // Update tail if deleting the tail
            }

            free(toDelete);
            ll->size--;
            return;
        }
        temp = temp->next;
    } while (temp != ll->head);

    printf("Node with value %d not found\n", targetVal);
}

void circular_deleteBeforeNode(CircularLinkedList *ll, int targetVal)
{
    if (ll->head == NULL || ll->head->val == targetVal)
    {
        printf("No node before the node with value %d\n", targetVal);
        return;
    }

    CircularNode *prev = NULL;
    CircularNode *current = ll->head;

    do
    {
        if (current->next->val == targetVal)
        {
            if (prev == NULL)
            {
                circular_deleteAtHead(ll);
            }
            else
            {
                prev->next = current->next;
                free(current);
                ll->size--;
            }
            return;
        }
        prev = current;
        current = current->next;
    } while (current != ll->head);

    printf("Node with value %d not found\n", targetVal);
}

void circular_deleteInSortedList(CircularLinkedList *ll, int val, int ascending)
{
    circular_bubbleSort(ll, ascending);

    if (ll->size == 0)
    {
        printf("List is empty\n");
        return;
    }

    CircularNode *prev = NULL;
    CircularNode *current = ll->head;

    do
    {
        if (current->val == val)
        {
            if (prev == NULL)
            {
                circular_deleteAtHead(ll);
            }
            else
            {
                prev->next = current->next;

                if (current == ll->tail)
                {
                    ll->tail = prev; // Update tail if deleting the tail
                }

                free(current);
                ll->size--;
            }
            return;
        }
        prev = current;
        current = current->next;
    } while (current != ll->head);

    printf("Node with value %d not found\n", val);
}

void circular_searchValue(CircularLinkedList *ll, int val)
{
    if (ll->size == 0)
    {
        printf("List is empty\n");
        return;
    }

    CircularNode *temp = ll->head;
    int idx = 0;

    do
    {
        if (temp->val == val)
        {
            printf("Value %d found at index %d\n", val, idx);
            return;
        }
        temp = temp->next;
        idx++;
    } while (temp != ll->head);

    printf("Value %d not found in the list\n", val);
}

void circular_findDuplicate(CircularLinkedList *ll)
{
    if (ll->size == 0)
    {
        printf("List is empty\n");
        return;
    }

    int found = 0;
    CircularNode *current = ll->head;
    int currentIdx = 0;

    do
    {
        CircularNode *runner = current->next;
        int runnerIdx = currentIdx + 1;

        while (runner != ll->head)
        {
            if (current->val == runner->val)
            {
                if (!found)
                {
                    found = 1;
                    printf("\nDuplicates found:\n");
                }
                printf("Value %d found at indexes: %d and %d\n", current->val, currentIdx, runnerIdx);
            }
            runner = runner->next;
            runnerIdx++;
        }
        current = current->next;
        currentIdx++;
    } while (current != ll->head);

    if (!found)
    {
        printf("No duplicates found in the list\n");
    }
}

void circular_printList(CircularLinkedList *ll)
{
    if (ll->size == 0)
    {
        printf("List is empty\n");
        return;
    }

    CircularNode *temp = ll->head;
    do
    {
        printf("%d ", temp->val);
        temp = temp->next;
    } while (temp != ll->head);
    printf("\n");
}

void circular_displayMenu()
{
    printf("\nMenu:\n");
    printf("1. Search for a Value\n");
    printf("2. Search Duplicates\n");
    printf("3. Print Current Linked List\n");
    printf("4. Insert at Head\n");
    printf("5. Insert at Tail\n");
    printf("6. Insert at Index\n");
    printf("7. Insert after a given node\n");
    printf("8. Insert before a given node\n");
    printf("9. Insert in a Sorted Linked List\n");
    printf("10. Deletion at Head\n");
    printf("11. Deletion at Tail\n");
    printf("12. Deletion at Index\n");
    printf("13. Deletion after a given node\n");
    printf("14. Deletion before a given node\n");
    printf("15. Deletion in a Sorted Linked List\n");
    printf("16. Exit\n");
    printf("Enter your choice: ");
}

void circular_createLinkedList(CircularLinkedList *ll)
{
    int n, val;
    while (ll->size > 0)
    {
        circular_deleteAtHead(ll);
    }

    printf("Enter the number of elements in the linked list: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("Enter value for node %d: ", i + 1);
        scanf("%d", &val);
        circular_insertAtTail(ll, val);
    }
}

void circular_clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int circular_main()
{
    CircularLinkedList ll;
    ll.head = ll.tail = NULL;
    ll.size = 0;

    int choice, val, idx, targetVal, ascending;
    char continue_choice;

    // First, ask the user to enter a linked list
    circular_createLinkedList(&ll);
    printf("Initial List: ");
    circular_printList(&ll);

    do
    {
        circular_displayMenu();
        scanf("%d", &choice);
        circular_clearInputBuffer();

        switch (choice)
        {
        case 1:
            printf("Enter value to search: ");
            scanf("%d", &val);
            circular_searchValue(&ll, val);
            break;
        case 2:
            circular_findDuplicate(&ll);
            break;
        case 3:
            printf("Current List: ");
            circular_printList(&ll);
            break;
        case 4:
            printf("Enter value to insert at head: ");
            scanf("%d", &val);
            circular_insertAtHead(&ll, val);
            printf("Updated List: ");
            circular_printList(&ll);
            break;
        case 5:
            printf("Enter value to insert at tail: ");
            scanf("%d", &val);
            circular_insertAtTail(&ll, val);
            printf("Updated List: ");
            circular_printList(&ll);
            break;
        case 6:
            printf("Enter value and index to insert at: ");
            scanf("%d %d", &val, &idx);
            circular_insertAtIdx(&ll, val, idx);
            printf("Updated List: ");
            circular_printList(&ll);
            break;
        case 7:
            printf("Enter value to insert and target value: ");
            scanf("%d %d", &val, &targetVal);
            circular_insertAfterNode(&ll, val, targetVal);
            printf("Updated List: ");
            circular_printList(&ll);
            break;
        case 8:
            printf("Enter value to insert and target value: ");
            scanf("%d %d", &val, &targetVal);
            circular_insertBeforeNode(&ll, val, targetVal);
            printf("Updated List: ");
            circular_printList(&ll);
            break;
        case 9:
            printf("Sort in ascending order? (1 for yes, 0 for no): ");
            scanf("%d", &ascending);
            printf("Enter value to insert: ");
            scanf("%d", &val);
            circular_insertInSortedList(&ll, val, ascending);
            printf("Updated List: ");
            circular_printList(&ll);
            break;
        case 10:
            circular_deleteAtHead(&ll);
            printf("Updated List: ");
            circular_printList(&ll);
            break;
        case 11:
            circular_deleteAtTail(&ll);
            printf("Updated List: ");
            circular_printList(&ll);
            break;
        case 12:
            printf("Enter index to delete: ");
            scanf("%d", &idx);
            circular_deleteAtIdx(&ll, idx);
            printf("Updated List: ");
            circular_printList(&ll);
            break;
        case 13:
            printf("Enter target value to delete after: ");
            scanf("%d", &targetVal);
            circular_deleteAfterNode(&ll, targetVal);
            printf("Updated List: ");
            circular_printList(&ll);
            break;
        case 14:
            printf("Enter target value to delete before: ");
            scanf("%d", &targetVal);
            circular_deleteBeforeNode(&ll, targetVal);
            printf("Updated List: ");
            circular_printList(&ll);
            break;
        case 15:
            printf("Sort in ascending or descending order? (1 for ascending, 0 for descending): ");
            scanf("%d", &ascending);
            printf("Enter value to delete: ");
            scanf("%d", &val);
            circular_deleteInSortedList(&ll, val, ascending);
            printf("Updated List: ");
            circular_printList(&ll);
            break;
        case 16:
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }

        circular_clearInputBuffer();
        printf("\nDo you want to perform another Circular Linked Link Operation? (y/n): ");
        scanf("%c", &continue_choice);

        if (continue_choice != 'y' && continue_choice != 'Y')
        {
            printf("Exiting...\n");
            break;
        }

    } while (1);

    return 0;
}