#include <stdio.h>
#include <stdlib.h>

struct Student {
    int rollNumber;
    char name[30];
    float marks;
};

int main() {
    FILE *file;
    struct Student student;

    // Open file for writing
    file = fopen("students.dat", "wb");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Write records to the file
    for (int i = 1; i <= 5; ++i) {
        student.rollNumber = i;
        sprintf(student.name, "Student%d", i);
        student.marks = i * 10.0;

        fwrite(&student, sizeof(struct Student), 1, file);
    }

    // Close the file
    fclose(file);

    // Open file for reading
    file = fopen("students.dat", "rb");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Read and print records from the file
    printf("Sequential File Organization:\n");
    while (fread(&student, sizeof(struct Student), 1, file) == 1) {
        printf("Roll Number: %d, Name: %s, Marks: %.2f\n", student.rollNumber, student.name, student.marks);
    }

    // Close the file
    fclose(file);

    return EXIT_SUCCESS;
}
