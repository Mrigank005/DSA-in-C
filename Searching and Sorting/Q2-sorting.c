#include <stdio.h>

// Function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function for quicksort
int partition(int arr[], int beg, int end) {
    int pivot = arr[end];  // Choosing the last element as pivot
    int i = beg - 1;  // Index of the smaller element

    // Rearranging elements so that smaller ones are on the left of pivot
    for (int j = beg; j < end; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    // Place the pivot in the correct position
    swap(&arr[i + 1], &arr[end]);
    return i + 1;
}

// Quicksort algorithm
void quick_sort(int arr[], int beg, int end) {
    if (beg < end) {
        int loc = partition(arr, beg, end);  // Get pivot index
        quick_sort(arr, beg, loc - 1);  // Sort left of pivot
        quick_sort(arr, loc + 1, end);  // Sort right of pivot
    }
}

// Function to print the array
void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {29, 10, 14, 37, 14};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    print_array(arr, n);

    // Perform quicksort
    quick_sort(arr, 0, n - 1);

    printf("Sorted array: ");
    print_array(arr, n);

    return 0;
}
