#include <stdio.h>
#include <stdlib.h>

typedef struct CDLL_Node
{
    int val;
    struct CDLL_Node *next;
    struct CDLL_Node *prev;
} CDLL_Node;

typedef struct CDLL_LinkedList
{
    CDLL_Node *head;
    CDLL_Node *tail;
    int size;
} CDLL_LinkedList;

void CDLL_insertAtHead(CDLL_LinkedList *ll, int val)
{
    CDLL_Node *temp = (CDLL_Node *)malloc(sizeof(CDLL_Node));
    temp->val = val;
    if (ll->size == 0)
    {
        ll->head = ll->tail = temp;
        temp->next = temp;
        temp->prev = temp;
    }
    else
    {
        temp->next = ll->head;
        temp->prev = ll->tail;
        ll->head->prev = temp;
        ll->tail->next = temp;
        ll->head = temp;
    }
    ll->size++;
}

void CDLL_insertAtTail(CDLL_LinkedList *ll, int val)
{
    CDLL_Node *temp = (CDLL_Node *)malloc(sizeof(CDLL_Node));
    temp->val = val;
    if (ll->size == 0)
    {
        ll->head = ll->tail = temp;
        temp->next = temp;
        temp->prev = temp;
    }
    else
    {
        temp->next = ll->head;
        temp->prev = ll->tail;
        ll->tail->next = temp;
        ll->head->prev = temp;
        ll->tail = temp;
    }
    ll->size++;
}

void CDLL_insertAtIdx(CDLL_LinkedList *ll, int val, int idx)
{
    if (idx < 0 || idx > ll->size)
    {
        printf("Index out of bounds\n");
        return;
    }
    if (idx == 0)
    {
        CDLL_insertAtHead(ll, val);
        return;
    }
    if (idx == ll->size)
    {
        CDLL_insertAtTail(ll, val);
        return;
    }
    CDLL_Node *new = (CDLL_Node *)malloc(sizeof(CDLL_Node));
    new->val = val;
    CDLL_Node *temp = ll->head;
    for (int i = 0; i < idx - 1; i++)
    {
        temp = temp->next;
    }
    new->next = temp->next;
    new->prev = temp;
    temp->next->prev = new;
    temp->next = new;
    ll->size++;
}

void CDLL_insertAfterNode(CDLL_LinkedList *ll, int val, int targetVal)
{
    CDLL_Node *temp = ll->head;
    do
    {
        if (temp->val == targetVal)
        {
            CDLL_Node *new = (CDLL_Node *)malloc(sizeof(CDLL_Node));
            new->val = val;
            new->next = temp->next;
            new->prev = temp;
            temp->next->prev = new;
            temp->next = new;
            if (temp == ll->tail)
            {
                ll->tail = new;
            }
            ll->size++;
            return;
        }
        temp = temp->next;
    } while (temp != ll->head);
    printf("Node with value %d not found\n", targetVal);
}

void CDLL_insertBeforeNode(CDLL_LinkedList *ll, int val, int targetVal)
{
    if (ll->head == NULL)
    {
        printf("List is empty\n");
        return;
    }
    CDLL_Node *temp = ll->head;
    do
    {
        if (temp->val == targetVal)
        {
            CDLL_Node *new = (CDLL_Node *)malloc(sizeof(CDLL_Node));
            new->val = val;
            new->next = temp;
            new->prev = temp->prev;
            temp->prev->next = new;
            temp->prev = new;
            if (temp == ll->head)
            {
                ll->head = new;
            }
            ll->size++;
            return;
        }
        temp = temp->next;
    } while (temp != ll->head);
    printf("Node with value %d not found\n", targetVal);
}

void CDLL_bubbleSort(CDLL_LinkedList *ll, int ascending)
{
    if (ll->size <= 1)
    {
        return;
    }
    int swapped;
    CDLL_Node *ptr1;
    CDLL_Node *lptr = NULL;
    do
    {
        swapped = 0;
        ptr1 = ll->head;
        while (ptr1->next != lptr && ptr1->next != ll->head)
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
        lptr = ptr1;
    } while (swapped);
}

void CDLL_insertInSortedList(CDLL_LinkedList *ll, int val, int ascending)
{
    CDLL_bubbleSort(ll, ascending);
    CDLL_Node *new = (CDLL_Node *)malloc(sizeof(CDLL_Node));
    new->val = val;
    if (ll->size == 0)
    {
        ll->head = ll->tail = new;
        new->next = new;
        new->prev = new;
    }
    else
    {
        CDLL_Node *current = ll->head;
        while (current->next != ll->head && ((ascending && current->val < val) || (!ascending && current->val > val)))
        {
            current = current->next;
        }
        if ((ascending && current->val > val) || (!ascending && current->val < val))
        {
            new->next = current;
            new->prev = current->prev;
            current->prev->next = new;
            current->prev = new;
            if (current == ll->head)
            {
                ll->head = new;
            }
        }
        else
        {
            new->next = current->next;
            new->prev = current;
            current->next->prev = new;
            current->next = new;
            if (current == ll->tail)
            {
                ll->tail = new;
            }
        }
    }
    ll->size++;
}

void CDLL_deleteAtHead(CDLL_LinkedList *ll)
{
    if (ll->size == 0)
    {
        printf("List is empty\n");
        return;
    }
    CDLL_Node *temp = ll->head;
    if (ll->size == 1)
    {
        ll->head = ll->tail = NULL;
    }
    else
    {
        ll->head = ll->head->next;
        ll->head->prev = ll->tail;
        ll->tail->next = ll->head;
    }
    free(temp);
    ll->size--;
}

void CDLL_deleteAtTail(CDLL_LinkedList *ll)
{
    if (ll->size == 0)
    {
        printf("List is empty\n");
        return;
    }
    CDLL_Node *temp = ll->tail;
    if (ll->size == 1)
    {
        ll->head = ll->tail = NULL;
    }
    else
    {
        ll->tail = ll->tail->prev;
        ll->tail->next = ll->head;
        ll->head->prev = ll->tail;
    }
    free(temp);
    ll->size--;
}

void CDLL_deleteAtIdx(CDLL_LinkedList *ll, int idx)
{
    if (idx < 0 || idx >= ll->size)
    {
        printf("Index out of bounds\n");
        return;
    }
    if (idx == 0)
    {
        CDLL_deleteAtHead(ll);
        return;
    }
    if (idx == ll->size - 1)
    {
        CDLL_deleteAtTail(ll);
        return;
    }
    CDLL_Node *temp = ll->head;
    for (int i = 0; i < idx; i++)
    {
        temp = temp->next;
    }
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    free(temp);
    ll->size--;
}

void CDLL_deleteAfterNode(CDLL_LinkedList *ll, int targetVal)
{
    CDLL_Node *temp = ll->head;
    do
    {
        if (temp->val == targetVal)
        {
            if (temp->next == ll->head)
            {
                printf("No node after the node with value %d\n", targetVal);
                return;
            }
            CDLL_Node *toDelete = temp->next;
            temp->next = toDelete->next;
            toDelete->next->prev = temp;
            if (toDelete == ll->tail)
            {
                ll->tail = temp;
            }
            free(toDelete);
            ll->size--;
            return;
        }
        temp = temp->next;
    } while (temp != ll->head);
    printf("Node with value %d not found\n", targetVal);
}

void CDLL_deleteBeforeNode(CDLL_LinkedList *ll, int targetVal)
{
    if (ll->head == NULL || ll->head->val == targetVal)
    {
        printf("No node before the node with value %d\n", targetVal);
        return;
    }
    CDLL_Node *temp = ll->head;
    do
    {
        if (temp->val == targetVal)
        {
            CDLL_Node *toDelete = temp->prev;
            temp->prev = toDelete->prev;
            toDelete->prev->next = temp;
            if (toDelete == ll->head)
            {
                ll->head = temp;
            }
            free(toDelete);
            ll->size--;
            return;
        }
        temp = temp->next;
    } while (temp != ll->head);
    printf("Node with value %d not found\n", targetVal);
}

void CDLL_deleteInSortedList(CDLL_LinkedList *ll, int val, int ascending)
{
    CDLL_bubbleSort(ll, ascending);
    if (ll->size == 0)
    {
        printf("List is empty\n");
        return;
    }
    CDLL_Node *current = ll->head;
    do
    {
        if (current->val == val)
        {
            if (current == ll->head)
            {
                CDLL_deleteAtHead(ll);
            }
            else if (current == ll->tail)
            {
                CDLL_deleteAtTail(ll);
            }
            else
            {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                free(current);
                ll->size--;
            }
            return;
        }
        current = current->next;
    } while (current != ll->head);
    printf("Node with value %d not found\n", val);
}

void CDLL_searchValue(CDLL_LinkedList *ll, int val)
{
    CDLL_Node *temp = ll->head;
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

void CDLL_findduplicate(CDLL_LinkedList *ll)
{
    if (ll->size == 0)
    {
        printf("List is empty\n");
        return;
    }

    int found = 0;
    CDLL_Node *current = ll->head;
    int currentIdx = 0;

    do
    {
        CDLL_Node *runner = current->next;
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

void CDLL_printList(CDLL_LinkedList *ll)
{
    if (ll->size == 0)
    {
        printf("List is empty\n");
        return;
    }
    CDLL_Node *temp = ll->head;
    do
    {
        printf("%d ", temp->val);
        temp = temp->next;
    } while (temp != ll->head);
    printf("\n");
}

void CDLL_displayMenu()
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

void CDLL_createLinkedList(CDLL_LinkedList *ll)
{
    int n, val;
    while (ll->size > 0)
    {
        CDLL_deleteAtHead(ll);
    }

    printf("Enter the number of elements in the linked list: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("Enter value for node %d: ", i + 1);
        scanf("%d", &val);
        CDLL_insertAtTail(ll, val);
    }
}

void CDLL_clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int CDLL_run()
{
    CDLL_LinkedList ll;
    ll.head = ll.tail = NULL;
    ll.size = 0;

    int choice, val, idx, targetVal, ascending;
    char continue_choice;

    CDLL_createLinkedList(&ll);
    printf("Initial List: ");
    CDLL_printList(&ll);

    do
    {
        CDLL_displayMenu();
        scanf("%d", &choice);
        CDLL_clearInputBuffer();

        switch (choice)
        {
        case 1:
            printf("Enter value to search: ");
            scanf("%d", &val);
            CDLL_searchValue(&ll, val);
            break;
        case 2:
            CDLL_findduplicate(&ll);
            break;
        case 3:
            printf("Current List: ");
            CDLL_printList(&ll);
            break;
        case 4:
            printf("Enter value to insert at head: ");
            scanf("%d", &val);
            CDLL_insertAtHead(&ll, val);
            printf("Updated List: ");
            CDLL_printList(&ll);
            break;
        case 5:
            printf("Enter value to insert at tail: ");
            scanf("%d", &val);
            CDLL_insertAtTail(&ll, val);
            printf("Updated List: ");
            CDLL_printList(&ll);
            break;
        case 6:
            printf("Enter value and index to insert at: ");
            scanf("%d %d", &val, &idx);
            CDLL_insertAtIdx(&ll, val, idx);
            printf("Updated List: ");
            CDLL_printList(&ll);
            break;
        case 7:
            printf("Enter value to insert and target value: ");
            scanf("%d %d", &val, &targetVal);
            CDLL_insertAfterNode(&ll, val, targetVal);
            printf("Updated List: ");
            CDLL_printList(&ll);
            break;
        case 8:
            printf("Enter value to insert and target value: ");
            scanf("%d %d", &val, &targetVal);
            CDLL_insertBeforeNode(&ll, val, targetVal);
            printf("Updated List: ");
            CDLL_printList(&ll);
            break;
        case 9:
            printf("Sort in ascending order? (1 for yes, 0 for no): ");
            scanf("%d", &ascending);
            printf("Enter value to insert: ");
            scanf("%d", &val);
            CDLL_insertInSortedList(&ll, val, ascending);
            printf("Updated List: ");
            CDLL_printList(&ll);
            break;
        case 10:
            CDLL_deleteAtHead(&ll);
            printf("Updated List: ");
            CDLL_printList(&ll);
            break;
        case 11:
            CDLL_deleteAtTail(&ll);
            printf("Updated List: ");
            CDLL_printList(&ll);
            break;
        case 12:
            printf("Enter index to delete: ");
            scanf("%d", &idx);
            CDLL_deleteAtIdx(&ll, idx);
            printf("Updated List: ");
            CDLL_printList(&ll);
            break;
        case 13:
            printf("Enter target value to delete after: ");
            scanf("%d", &targetVal);
            CDLL_deleteAfterNode(&ll, targetVal);
            printf("Updated List: ");
            CDLL_printList(&ll);
            break;
        case 14:
            printf("Enter target value to delete before: ");
            scanf("%d", &targetVal);
            CDLL_deleteBeforeNode(&ll, targetVal);
            printf("Updated List: ");
            CDLL_printList(&ll);
            break;
        case 15:
            printf("Sort in ascending order? (1 for yes, 0 for no): ");
            scanf("%d", &ascending);
            printf("Enter value to delete: ");
            scanf("%d", &val);
            CDLL_deleteInSortedList(&ll, val, ascending);
            printf("Updated List: ");
            CDLL_printList(&ll);
            break;
        case 16:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }

        if (choice != 16)
        {
            printf("Do you want to continue? (y/n): ");
            scanf(" %c", &continue_choice);
            CDLL_clearInputBuffer();
        }
        else
        {
            continue_choice = 'n';
        }

    } while (continue_choice == 'y' || continue_choice == 'Y');

    // Free the remaining nodes in the list before exiting
    while (ll.size > 0)
    {
        CDLL_deleteAtHead(&ll);
    }

    printf("Program terminated.\n");
    return 0;
}