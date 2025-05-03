#include <stdio.h>

// Linear Search Function
int linearSearch(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

// Binary Search Function (Assumes sorted array)
int binarySearch(int arr[], int size, int target) {
    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

// Function to sort the array using selection sort
void selectionSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        // Swap the found minimum element with the first element
        int temp = arr[minIdx];
        arr[minIdx] = arr[i];
        arr[i] = temp;
    }
}

int main() {
    int size, target, choice, result;
    
    // Taking the array size as input
    printf("Enter the number of elements in the array: ");
    scanf("%d", &size);

    if (size <= 0) {
        printf("Array size should be greater than zero.\n");
        return 1;
    }

    int arr[size];
    printf("Enter %d elements of the array:\n", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    // Taking the target element to search
    printf("Enter the element to search: ");
    scanf("%d", &target);

    // User choice for search method
    printf("Choose Search Method:\n");
    printf("1. Linear Search\n");
    printf("2. Binary Search (Array will be sorted if needed)\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            result = linearSearch(arr, size, target);
            if (result != -1) {
                printf("Linear Search: Target found at index %d\n", result);
            } else {
                printf("Linear Search: Target not found\n");
            }
            break;
        case 2:
            // Sort the array before binary search
            selectionSort(arr, size);
            result = binarySearch(arr, size, target);
            if (result != -1) {
                printf("Binary Search: Target found at index %d\n", result);
            } else {
                printf("Binary Search: Target not found\n");
            }
            break;
        default:
            printf("Invalid choice! Please select 1 or 2.\n");
    }

    return 0;
}