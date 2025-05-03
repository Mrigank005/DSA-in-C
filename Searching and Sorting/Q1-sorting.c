#include <stdio.h>

// Function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Selection sort algorithm
void selectionsort(int arr[], int n) {
    int i, j, smallestIndex;
    for (i = 0; i < n - 1; i++) {
        smallestIndex = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[smallestIndex]) {
                smallestIndex = j;
            }
        }
        swap(&arr[i], &arr[smallestIndex]);
    }
}

// Function to print the array
void Printarray(int arr[], int n) {
    printf("The sorted array is: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n;

    // Get the size of the array from the user
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid input! The number of elements must be positive.\n");
        return 1;
    }

    int arr[n];

    // Get the array elements from the user
    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Sort the array
    selectionsort(arr, n);

    // Print the sorted array
    Printarray(arr, n);

    return 0;
}
