#include <stdio.h>

#define NUM_FAMILIES 10

// Hash function to assign a student ID to a family
int getFamilyNumber(int studentID) {
    int lastThreeDigits = studentID % 1000;
    return lastThreeDigits % NUM_FAMILIES;
}

int main() {
    int numberOfStudents, currentID;

    printf("Enter the number of students: ");
    scanf("%d", &numberOfStudents);

    if (numberOfStudents <= 0) {
        printf("Invalid number of students.\n");
        return 1;
    }

    printf("Enter the student IDs:\n");
    for (int i = 0; i < numberOfStudents; i++) {
        scanf("%d", &currentID);

        if (currentID < 0) {
            printf("Invalid student ID. Must be non-negative.\n");
            continue;
        }

        int family = getFamilyNumber(currentID);
        printf("Student with ID %d belongs to family %d\n", currentID, family);
    }

    return 0;
}
