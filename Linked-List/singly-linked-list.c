#include <stdio.h>
#include <stdlib.h>

typedef struct SLL_Node
{
    int val;
    struct SLL_Node *next;
} SLL_Node;

typedef struct SLL_LinkedList
{
    SLL_Node *head;
    SLL_Node *tail;
    int size;
} SLL_LinkedList;

void SLL_insertAtHead(SLL_LinkedList *ll, int val)
{
    SLL_Node *temp = (SLL_Node *)malloc(sizeof(SLL_Node));
    temp->val = val;
    temp->next = ll->head;
    ll->head = temp;
    if (ll->size == 0)
    {
        ll->tail = temp;
    }
    ll->size++;
}

void SLL_insertAtTail(SLL_LinkedList *ll, int val)
{
    SLL_Node *temp = (SLL_Node *)malloc(sizeof(SLL_Node));
    temp->val = val;
    temp->next = NULL;
    if (ll->size == 0)
    {
        ll->head = ll->tail = temp;
    }
    else
    {
        ll->tail->next = temp;
        ll->tail = temp;
    }
    ll->size++;
}

void SLL_insertAtIdx(SLL_LinkedList *ll, int val, int idx)
{
    if (idx < 0 || idx > ll->size)
    {
        printf("Index out of bounds\n");
        return;
    }
    SLL_Node *new = (SLL_Node *)malloc(sizeof(SLL_Node));
    new->val = val;
    new->next = NULL;
    if (idx == 0)
    {
        new->next = ll->head;
        ll->head = new;
        if (ll->size == 0)
        {
            ll->tail = new;
        }
    }
    else
    {
        SLL_Node *temp = ll->head;
        for (int i = 0; i < idx - 1; i++)
        {
            temp = temp->next;
        }
        new->next = temp->next;
        temp->next = new;
        if (new->next == NULL)
        {
            ll->tail = new;
        }
    }
    ll->size++;
}

void SLL_insertAfterNode(SLL_LinkedList *ll, int val, int targetVal)
{
    SLL_Node *temp = ll->head;
    while (temp != NULL && temp->val != targetVal)
    {
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("Node with value %d not found\n", targetVal);
        return;
    }
    SLL_Node *new = (SLL_Node *)malloc(sizeof(SLL_Node));
    new->val = val;
    new->next = temp->next;
    temp->next = new;
    if (new->next == NULL)
    {
        ll->tail = new;
    }
    ll->size++;
}

void SLL_insertBeforeNode(SLL_LinkedList *ll, int val, int targetVal)
{
    if (ll->head == NULL)
    {
        printf("List is empty\n");
        return;
    }
    if (ll->head->val == targetVal)
    {
        SLL_insertAtHead(ll, val);
        return;
    }
    SLL_Node *prev = NULL;
    SLL_Node *current = ll->head;
    while (current != NULL && current->val != targetVal)
    {
        prev = current;
        current = current->next;
    }
    if (current == NULL)
    {
        printf("Node with value %d not found\n", targetVal);
        return;
    }
    SLL_Node *new = (SLL_Node *)malloc(sizeof(SLL_Node));
    new->val = val;
    new->next = current;
    prev->next = new;
    ll->size++;
}

void SLL_bubbleSort(SLL_LinkedList *ll, int ascending)
{
    if (ll->size <= 1)
    {
        return;
    }
    int swapped;
    SLL_Node *ptr1;
    SLL_Node *ptr = NULL;
    while (1)
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
        if (!swapped)
        {
            break;
        }
    }
}

void SLL_insertInSortedList(SLL_LinkedList *ll, int val, int ascending)
{
    SLL_bubbleSort(ll, ascending);
    SLL_Node *new = (SLL_Node *)malloc(sizeof(SLL_Node));
    new->val = val;
    new->next = NULL;
    if (ll->size == 0)
    {
        ll->head = ll->tail = new;
    }
    else
    {
        SLL_Node *prev = NULL;
        SLL_Node *current = ll->head;
        while (current != NULL && ((ascending && current->val < val) || (!ascending && current->val > val)))
        {
            prev = current;
            current = current->next;
        }
        if (prev == NULL)
        {
            new->next = ll->head;
            ll->head = new;
        }
        else
        {
            new->next = current;
            prev->next = new;
        }
        if (new->next == NULL)
        {
            ll->tail = new;
        }
    }
    ll->size++;
}

void SLL_deleteAtHead(SLL_LinkedList *ll)
{
    if (ll->size == 0)
    {
        printf("List is empty\n");
        return;
    }
    SLL_Node *temp = ll->head;
    ll->head = ll->head->next;
    free(temp);
    ll->size--;
    if (ll->size == 0)
    {
        ll->tail = NULL;
    }
}

void SLL_deleteAtTail(SLL_LinkedList *ll)
{
    if (ll->size == 0)
    {
        printf("List is empty\n");
        return;
    }
    if (ll->size == 1)
    {
        free(ll->head);
        ll->head = ll->tail = NULL;
    }
    else
    {
        SLL_Node *temp = ll->head;
        while (temp->next != ll->tail)
        {
            temp = temp->next;
        }
        free(ll->tail);
        ll->tail = temp;
        ll->tail->next = NULL;
    }
    ll->size--;
}

void SLL_deleteAtIdx(SLL_LinkedList *ll, int idx)
{
    if (idx < 0 || idx >= ll->size)
    {
        printf("Index out of bounds\n");
        return;
    }
    if (idx == 0)
    {
        SLL_deleteAtHead(ll);
        return;
    }
    SLL_Node *temp = ll->head;
    for (int i = 0; i < idx - 1; i++)
    {
        temp = temp->next;
    }
    SLL_Node *toDelete = temp->next;
    temp->next = toDelete->next;
    if (toDelete->next == NULL)
    {
        ll->tail = temp;
    }
    free(toDelete);
    ll->size--;
}

void SLL_deleteAfterNode(SLL_LinkedList *ll, int targetVal)
{
    SLL_Node *temp = ll->head;
    while (temp != NULL && temp->val != targetVal)
    {
        temp = temp->next;
    }
    if (temp == NULL || temp->next == NULL)
    {
        printf("Node with value %d not found or no node after it\n", targetVal);
        return;
    }
    SLL_Node *toDelete = temp->next;
    temp->next = toDelete->next;
    if (toDelete->next == NULL)
    {
        ll->tail = temp;
    }
    free(toDelete);
    ll->size--;
}

void SLL_deleteBeforeNode(SLL_LinkedList *ll, int targetVal)
{
    if (ll->head == NULL || ll->head->val == targetVal)
    {
        printf("No node before the node with value %d\n", targetVal);
        return;
    }
    if (ll->head->next->val == targetVal)
    {
        SLL_deleteAtHead(ll);
        return;
    }
    SLL_Node *prev = NULL;
    SLL_Node *current = ll->head;
    while (current->next != NULL && current->next->val != targetVal)
    {
        prev = current;
        current = current->next;
    }
    if (current->next == NULL)
    {
        printf("Node with value %d not found\n", targetVal);
        return;
    }
    SLL_Node *toDelete = current;
    prev->next = current->next;
    free(toDelete);
    ll->size--;
}

void SLL_deleteInSortedList(SLL_LinkedList *ll, int val, int ascending)
{
    SLL_bubbleSort(ll, ascending);
    if (ll->size == 0)
    {
        printf("List is empty\n");
        return;
    }
    SLL_Node *prev = NULL;
    SLL_Node *current = ll->head;
    while (current != NULL && ((ascending && current->val < val) || (!ascending && current->val > val)))
    {
        prev = current;
        current = current->next;
    }
    if (current == NULL || current->val != val)
    {
        printf("Node with value %d not found\n", val);
        return;
    }
    if (prev == NULL)
    {
        SLL_deleteAtHead(ll);
    }
    else
    {
        prev->next = current->next;
        if (current->next == NULL)
        {
            ll->tail = prev;
        }
        free(current);
        ll->size--;
    }
}

void SLL_searchValue(SLL_LinkedList *ll, int val)
{
    SLL_Node *temp = ll->head;
    int idx = 0;
    while (temp != NULL)
    {
        if (temp->val == val)
        {
            printf("Value %d found at index %d\n", val, idx);
            return;
        }
        temp = temp->next;
        idx++;
    }
    printf("Value %d not found in the list\n", val);
}

void SLL_findduplicate(SLL_LinkedList *ll)
{
    if (ll->size == 0)
    {
        printf("List is empty\n");
        return;
    }

    int found = 0;
    SLL_Node *current = ll->head;
    int currentIdx = 0;

    while (current != NULL)
    {
        SLL_Node *runner = current->next;
        int runnerIdx = currentIdx + 1;

        while (runner != NULL)
        {
            if (current->val == runner->val)
            {
                if (!found)
                {
                    found = 1;
                    printf("\nDuplicates found:\n");
                }
                printf("Value %d found at indexes: %d and %d\n",
                       current->val, currentIdx, runnerIdx);
            }
            runner = runner->next;
            runnerIdx++;
        }
        current = current->next;
        currentIdx++;
    }

    if (!found)
    {
        printf("No duplicates found in the list\n");
    }
}

void SLL_printList(SLL_LinkedList *ll)
{
    SLL_Node *temp = ll->head;
    while (temp != NULL)
    {
        printf("%d ", temp->val);
        temp = temp->next;
    }
    printf("\n");
}

void SLL_displayMenu()
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

void SLL_createLinkedList(SLL_LinkedList *ll)
{
    int n, val;
    while (ll->size > 0)
    {
        SLL_deleteAtHead(ll);
    }

    printf("Enter the number of elements in the linked list: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("Enter value for node %d: ", i + 1);
        scanf("%d", &val);
        SLL_insertAtTail(ll, val);
    }
}

void SLL_clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int singly_main()
{
    SLL_LinkedList ll;
    ll.head = ll.tail = NULL;
    ll.size = 0;

    int choice, val, idx, targetVal, ascending;
    char continue_choice;

    SLL_createLinkedList(&ll);
    printf("Initial List: ");
    SLL_printList(&ll);

    do
    {
        SLL_displayMenu();
        scanf("%d", &choice);
        SLL_clearInputBuffer();

        switch (choice)
        {
        case 1:
            printf("Enter value to search: ");
            scanf("%d", &val);
            SLL_searchValue(&ll, val);
            break;
        case 2:
            SLL_findduplicate(&ll);
            break;
        case 3:
            printf("Current List: ");
            SLL_printList(&ll);
            break;
        case 4:
            printf("Enter value to insert at head: ");
            scanf("%d", &val);
            SLL_insertAtHead(&ll, val);
            printf("Updated List: ");
            SLL_printList(&ll);
            break;
        case 5:
            printf("Enter value to insert at tail: ");
            scanf("%d", &val);
            SLL_insertAtTail(&ll, val);
            printf("Updated List: ");
            SLL_printList(&ll);
            break;
        case 6:
            printf("Enter value and index to insert at: ");
            scanf("%d %d", &val, &idx);
            SLL_insertAtIdx(&ll, val, idx);
            printf("Updated List: ");
            SLL_printList(&ll);
            break;
        case 7:
            printf("Enter value to insert and target value: ");
            scanf("%d %d", &val, &targetVal);
            SLL_insertAfterNode(&ll, val, targetVal);
            printf("Updated List: ");
            SLL_printList(&ll);
            break;
        case 8:
            printf("Enter value to insert and target value: ");
            scanf("%d %d", &val, &targetVal);
            SLL_insertBeforeNode(&ll, val, targetVal);
            printf("Updated List: ");
            SLL_printList(&ll);
            break;
        case 9:
            printf("Sort in which order? (1 for ascending, 0 for descending): ");
            scanf("%d", &ascending);
            printf("Enter value to insert: ");
            scanf("%d", &val);
            SLL_insertInSortedList(&ll, val, ascending);
            printf("Updated List: ");
            SLL_printList(&ll);
            break;
        case 10:
            SLL_deleteAtHead(&ll);
            printf("Updated List: ");
            SLL_printList(&ll);
            break;
        case 11:
            SLL_deleteAtTail(&ll);
            printf("Updated List: ");
            SLL_printList(&ll);
            break;
        case 12:
            printf("Enter index to delete: ");
            scanf("%d", &idx);
            SLL_deleteAtIdx(&ll, idx);
            printf("Updated List: ");
            SLL_printList(&ll);
            break;
        case 13:
            printf("Enter target value to delete after: ");
            scanf("%d", &targetVal);
            SLL_deleteAfterNode(&ll, targetVal);
            printf("Updated List: ");
            SLL_printList(&ll);
            break;
        case 14:
            printf("Enter target value to delete before: ");
            scanf("%d", &targetVal);
            SLL_deleteBeforeNode(&ll, targetVal);
            printf("Updated List: ");
            SLL_printList(&ll);
            break;
        case 15:
            printf("Sort in ascending or descending order? (1 for ascending, 0 for descending): ");
            scanf("%d", &ascending);
            printf("Enter value to delete: ");
            scanf("%d", &val);
            SLL_deleteInSortedList(&ll, val, ascending);
            printf("Updated List: ");
            SLL_printList(&ll);
            break;
        case 16:
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }

        SLL_clearInputBuffer();
        printf("\nDo you want to perform another Singly Linked Link operation? (y/n): ");
        scanf("%c", &continue_choice);

        if (continue_choice != 'y' && continue_choice != 'Y')
        {
            printf("Exiting...\n");
            break;
        }

    } while (1);

    return 0;
}