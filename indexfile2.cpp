#include <stdio.h>
#include <stdlib.h>

struct Index {
    int rollNumber;
    long offset;
};

struct Student {
    int rollNumber;
    char name[30];
    float marks;
};

int main() {
    FILE *dataFile, *indexFile;
    struct Student student;
    struct Index index;

    // Open data file for writing
    dataFile = fopen("students_data.dat", "wb");
    if (dataFile == NULL) {
        perror("Error opening data file");
        return EXIT_FAILURE;
    }

    // Open index file for writing
    indexFile = fopen("students_index.dat", "wb");
    if (indexFile == NULL) {
        perror("Error opening index file");
        fclose(dataFile);
        return EXIT_FAILURE;
    }

    // Write records to the data file and create index
    for (int i = 1; i <= 5; ++i) {
        student.rollNumber = i;
        sprintf(student.name, "Student%d", i);
        student.marks = i * 10.0;

        // Write data to the data file
        fwrite(&student, sizeof(struct Student), 1, dataFile);

        // Write index to the index file
        index.rollNumber = i;
        index.offset = ftell(dataFile) - sizeof(struct Student);
        fwrite(&index, sizeof(struct Index), 1, indexFile);
    }

    // Close both files
    fclose(dataFile);
    fclose(indexFile);

    // Open index file for reading
    indexFile = fopen("students_index.dat", "rb");
    if (indexFile == NULL) {
        perror("Error opening index file");
        return EXIT_FAILURE;
    }

    // Open data file for reading
    dataFile = fopen("students_data.dat", "rb");
    if (dataFile == NULL) {
        perror("Error opening data file");
        fclose(indexFile);
        return EXIT_FAILURE;
    }

    // Read and print records using the index
    printf("Indexed File Organization:\n");
    while (fread(&index, sizeof(struct Index), 1, indexFile) == 1) {
        fseek(dataFile, index.offset, SEEK_SET);
        fread(&student, sizeof(struct Student), 1, dataFile);
        printf("Roll Number: %d, Name: %s, Marks: %.2f\n", student.rollNumber, student.name, student.marks);
    }

    // Close both files
    fclose(dataFile);
    fclose(indexFile);

    return EXIT_SUCCESS;
}
