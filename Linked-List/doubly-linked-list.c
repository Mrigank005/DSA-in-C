#include <stdio.h>
#include <stdlib.h>

typedef struct DoublyNode
{
    int val;
    struct DoublyNode *next;
    struct DoublyNode *prev;
} DoublyNode;

typedef struct DoublyLinkedList
{
    DoublyNode *head;
    DoublyNode *tail;
    int size;
} DoublyLinkedList;

void doubly_insertAtHead(DoublyLinkedList *ll, int val)
{
    DoublyNode *temp = (DoublyNode *)malloc(sizeof(DoublyNode));
    temp->val = val;
    temp->next = ll->head;
    temp->prev = NULL;

    if (ll->size == 0)
    {
        ll->tail = temp;
    }
    else
    {
        ll->head->prev = temp;
    }

    ll->head = temp;
    ll->size++;
}

void doubly_insertAtTail(DoublyLinkedList *ll, int val)
{
    DoublyNode *temp = (DoublyNode *)malloc(sizeof(DoublyNode));
    temp->val = val;
    temp->next = NULL;
    temp->prev = ll->tail;

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

void doubly_insertAtIdx(DoublyLinkedList *ll, int val, int idx)
{
    if (idx < 0 || idx > ll->size)
    {
        printf("Index out of bounds\n");
        return;
    }

    if (idx == 0)
    {
        doubly_insertAtHead(ll, val);
        return;
    }
    else if (idx == ll->size)
    {
        doubly_insertAtTail(ll, val);
        return;
    }

    DoublyNode *new = (DoublyNode *)malloc(sizeof(DoublyNode));
    new->val = val;

    DoublyNode *temp = ll->head;
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

void doubly_insertAfterNode(DoublyLinkedList *ll, int val, int targetVal)
{
    DoublyNode *temp = ll->head;
    while (temp != NULL && temp->val != targetVal)
    {
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Node with value %d not found\n", targetVal);
        return;
    }

    DoublyNode *new = (DoublyNode *)malloc(sizeof(DoublyNode));
    new->val = val;
    new->next = temp->next;
    new->prev = temp;

    if (temp->next != NULL)
    {
        temp->next->prev = new;
    }
    else
    {
        ll->tail = new;
    }

    temp->next = new;
    ll->size++;
}

void doubly_insertBeforeNode(DoublyLinkedList *ll, int val, int targetVal)
{
    if (ll->head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    if (ll->head->val == targetVal)
    {
        doubly_insertAtHead(ll, val);
        return;
    }

    DoublyNode *temp = ll->head;
    while (temp != NULL && temp->val != targetVal)
    {
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Node with value %d not found\n", targetVal);
        return;
    }

    DoublyNode *new = (DoublyNode *)malloc(sizeof(DoublyNode));
    new->val = val;
    new->next = temp;
    new->prev = temp->prev;

    temp->prev->next = new;
    temp->prev = new;

    ll->size++;
}

void doubly_bubbleSort(DoublyLinkedList *ll, int ascending)
{
    if (ll->size <= 1)
    {
        return;
    }

    int swapped;
    DoublyNode *ptr1;
    DoublyNode *ptr = NULL;

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

void doubly_insertInSortedList(DoublyLinkedList *ll, int val, int ascending)
{
    doubly_bubbleSort(ll, ascending);

    DoublyNode *new = (DoublyNode *)malloc(sizeof(DoublyNode));
    new->val = val;
    new->next = NULL;
    new->prev = NULL;

    if (ll->size == 0)
    {
        ll->head = ll->tail = new;
    }
    else
    {
        DoublyNode *prev = NULL;
        DoublyNode *current = ll->head;

        while (current != NULL && ((ascending && current->val < val) || (!ascending && current->val > val)))
        {
            prev = current;
            current = current->next;
        }

        if (prev == NULL)
        {
            new->next = ll->head;
            ll->head->prev = new;
            ll->head = new;
        }
        else
        {
            new->next = current;
            new->prev = prev;
            prev->next = new;

            if (current != NULL)
            {
                current->prev = new;
            }
            else
            {
                ll->tail = new;
            }
        }
    }

    ll->size++;
}

void doubly_deleteAtHead(DoublyLinkedList *ll)
{
    if (ll->size == 0)
    {
        printf("List is empty\n");
        return;
    }

    DoublyNode *temp = ll->head;
    ll->head = ll->head->next;

    if (ll->head != NULL)
    {
        ll->head->prev = NULL;
    }
    else
    {
        ll->tail = NULL;
    }

    free(temp);
    ll->size--;
}

void doubly_deleteAtTail(DoublyLinkedList *ll)
{
    if (ll->size == 0)
    {
        printf("List is empty\n");
        return;
    }

    DoublyNode *temp = ll->tail;

    if (ll->size == 1)
    {
        ll->head = ll->tail = NULL;
    }
    else
    {
        ll->tail = ll->tail->prev;
        ll->tail->next = NULL;
    }

    free(temp);
    ll->size--;
}

void doubly_deleteAtIdx(DoublyLinkedList *ll, int idx)
{
    if (idx < 0 || idx >= ll->size)
    {
        printf("Index out of bounds\n");
        return;
    }

    if (idx == 0)
    {
        doubly_deleteAtHead(ll);
        return;
    }
    else if (idx == ll->size - 1)
    {
        doubly_deleteAtTail(ll);
        return;
    }

    DoublyNode *temp = ll->head;
    for (int i = 0; i < idx; i++)
    {
        temp = temp->next;
    }

    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;

    free(temp);
    ll->size--;
}

void doubly_deleteAfterNode(DoublyLinkedList *ll, int targetVal)
{
    DoublyNode *temp = ll->head;
    while (temp != NULL && temp->val != targetVal)
    {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL)
    {
        printf("Node with value %d not found or no node after it\n", targetVal);
        return;
    }

    DoublyNode *toDelete = temp->next;
    temp->next = toDelete->next;

    if (toDelete->next != NULL)
    {
        toDelete->next->prev = temp;
    }
    else
    {
        ll->tail = temp;
    }

    free(toDelete);
    ll->size--;
}

void doubly_deleteBeforeNode(DoublyLinkedList *ll, int targetVal)
{
    if (ll->head == NULL || ll->head->val == targetVal)
    {
        printf("No node before the node with value %d\n", targetVal);
        return;
    }

    DoublyNode *temp = ll->head;
    while (temp != NULL && temp->val != targetVal)
    {
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Node with value %d not found\n", targetVal);
        return;
    }

    DoublyNode *toDelete = temp->prev;

    if (toDelete == ll->head)
    {
        doubly_deleteAtHead(ll);
    }
    else
    {
        toDelete->prev->next = temp;
        temp->prev = toDelete->prev;
        free(toDelete);
        ll->size--;
    }
}

void doubly_deleteInSortedList(DoublyLinkedList *ll, int val, int ascending)
{
    doubly_bubbleSort(ll, ascending);

    if (ll->size == 0)
    {
        printf("List is empty\n");
        return;
    }

    DoublyNode *temp = ll->head;
    while (temp != NULL && ((ascending && temp->val < val) || (!ascending && temp->val > val)))
    {
        temp = temp->next;
    }

    if (temp == NULL || temp->val != val)
    {
        printf("Node with value %d not found\n", val);
        return;
    }

    if (temp == ll->head)
    {
        doubly_deleteAtHead(ll);
    }
    else if (temp == ll->tail)
    {
        doubly_deleteAtTail(ll);
    }
    else
    {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        free(temp);
        ll->size--;
    }
}

void doubly_searchValue(DoublyLinkedList *ll, int val)
{
    DoublyNode *temp = ll->head;
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

void doubly_findduplicate(DoublyLinkedList *ll)
{
    if (ll->size == 0)
    {
        printf("List is empty\n");
        return;
    }

    int found = 0;
    DoublyNode *current = ll->head;
    int currentIdx = 0;

    while (current != NULL)
    {
        DoublyNode *runner = current->next;
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
                printf("Value %d found at indexes: %d and %d\n", current->val, currentIdx, runnerIdx);
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

void doubly_printList(DoublyLinkedList *ll)
{
    DoublyNode *temp = ll->head;
    while (temp != NULL)
    {
        printf("%d ", temp->val);
        temp = temp->next;
    }
    printf("\n");
}

void doubly_displayMenu()
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

void doubly_createLinkedList(DoublyLinkedList *ll)
{
    int n, val;
    while (ll->size > 0)
    {
        doubly_deleteAtHead(ll);
    }

    printf("Enter the number of elements in the linked list: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("Enter value for node %d: ", i + 1);
        scanf("%d", &val);
        doubly_insertAtTail(ll, val);
    }
}

void doubly_clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int doubly_main()
{
    DoublyLinkedList ll;
    ll.head = ll.tail = NULL;
    ll.size = 0;

    int choice, val, idx, targetVal, ascending;
    char continue_choice;

    // First, ask the user to enter a linked list
    doubly_createLinkedList(&ll);
    printf("Initial List: ");
    doubly_printList(&ll);

    do
    {
        doubly_displayMenu();
        scanf("%d", &choice);
        doubly_clearInputBuffer();

        switch (choice)
        {
        case 1:
            printf("Enter value to search: ");
            scanf("%d", &val);
            doubly_searchValue(&ll, val);
            break;
        case 2:
            doubly_findduplicate(&ll);
            break;
        case 3:
            printf("Current List: ");
            doubly_printList(&ll);
            break;
        case 4:
            printf("Enter value to insert at head: ");
            scanf("%d", &val);
            doubly_insertAtHead(&ll, val);
            printf("Updated List: ");
            doubly_printList(&ll);
            break;
        case 5:
            printf("Enter value to insert at tail: ");
            scanf("%d", &val);
            doubly_insertAtTail(&ll, val);
            printf("Updated List: ");
            doubly_printList(&ll);
            break;
        case 6:
            printf("Enter value and index to insert at: ");
            scanf("%d %d", &val, &idx);
            doubly_insertAtIdx(&ll, val, idx);
            printf("Updated List: ");
            doubly_printList(&ll);
            break;
        case 7:
            printf("Enter value to insert and target value: ");
            scanf("%d %d", &val, &targetVal);
            doubly_insertAfterNode(&ll, val, targetVal);
            printf("Updated List: ");
            doubly_printList(&ll);
            break;
        case 8:
            printf("Enter value to insert and target value: ");
            scanf("%d %d", &val, &targetVal);
            doubly_insertBeforeNode(&ll, val, targetVal);
            printf("Updated List: ");
            doubly_printList(&ll);
            break;
        case 9:
            printf("Sort in ascending order? (1 for ascending, 0 for descending): ");
            scanf("%d", &ascending);
            printf("Enter value to insert: ");
            scanf("%d", &val);
            doubly_insertInSortedList(&ll, val, ascending);
            printf("Updated List: ");
            doubly_printList(&ll);
            break;
        case 10:
            doubly_deleteAtHead(&ll);
            printf("Updated List: ");
            doubly_printList(&ll);
            break;
        case 11:
            doubly_deleteAtTail(&ll);
            printf("Updated List: ");
            doubly_printList(&ll);
            break;
        case 12:
            printf("Enter index to delete: ");
            scanf("%d", &idx);
            doubly_deleteAtIdx(&ll, idx);
            printf("Updated List: ");
            doubly_printList(&ll);
            break;
        case 13:
            printf("Enter target value to delete after: ");
            scanf("%d", &targetVal);
            doubly_deleteAfterNode(&ll, targetVal);
            printf("Updated List: ");
            doubly_printList(&ll);
            break;
        case 14:
            printf("Enter target value to delete before: ");
            scanf("%d", &targetVal);
            doubly_deleteBeforeNode(&ll, targetVal);
            printf("Updated List: ");
            doubly_printList(&ll);
            break;
        case 15:
            printf("Sort in ascending or descending order? (1 for ascending, 0 for descending): ");
            scanf("%d", &ascending);
            printf("Enter value to delete: ");
            scanf("%d", &val);
            doubly_deleteInSortedList(&ll, val, ascending);
            printf("Updated List: ");
            doubly_printList(&ll);
            break;
        case 16:
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }

        doubly_clearInputBuffer();
        printf("\nDo you want to perform another Doubly Linked Link operation? (y/n): ");
        scanf("%c", &continue_choice);

        if (continue_choice != 'y' && continue_choice != 'Y')
        {
            printf("Exiting...\n");
            break;
        }

    } while (1);

    return 0;
}