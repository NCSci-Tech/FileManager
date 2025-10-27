#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to print the title sequence
void titleSequence() {
    puts(
        "_____________________________________________________\n"
        "||_________________________________________________||\n"
        "|| _____             ____              ____ ____   ||\n"
        "|| |    * | ____    |       |   |   | |    |       ||\n"
        "|| |___ | | |___|   |____ __|__ |   | |___ |___    ||\n"
        "|| |    | | |           |   |   |   | |    |       ||\n"
        "|| |    | | |___    ____|   |   |___| |    |       ||\n"
        "||_________________________________________________||\n"
        "/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\\n"
    );
}

// Function to get the file name from user input
char *getFile(void) {
    size_t size = 16;  // Initial buffer size
    size_t len = 0;    // Length of the input string
    char *buffer = malloc(size);  // Allocate memory for the buffer

    if (!buffer) {
        perror("malloc");  // Error if memory allocation fails
        return NULL;
    }

    int c;
    // Read characters until EOF or newline is encountered
    while ((c = getchar()) != EOF && c != '\n') {
        buffer[len++] = c;

        // If the buffer is full, double its size and reallocate memory
        if (len >= size) {
            size *= 2;
            char *new_buffer = realloc(buffer, size);
            if (!new_buffer) {
                perror("realloc");  // Error if realloc fails
                free(buffer);       // Free the original buffer
                return NULL;
            }
            buffer = new_buffer;
        }
    }

    buffer[len] = '\0';  // Null-terminate the string
    return buffer;
}

// Function to list the contents of the current directory
void listDir(void) {
    printf("Listing current directory contents:\n\n");

    // Platform-specific directory listing
#ifdef _WIN32
    system("dir");  // Windows
#else
    system("ls -l");  // Unix/Linux/macOS
#endif

    printf("\n");
}

// Function to read the contents of a file
void readF() {
    printf("Enter file name: ");
    char *fName = getFile();  // Get the file name from the user
    if (!fName) {
        fprintf(stderr, "ERROR: failed to read file name!\n");
        return;
    }
    if (strlen(fName) == 0) {
        printf("No file name entered.\n");
        free(fName);  // Free the allocated memory
        return;
    }

    FILE *fptr = fopen(fName, "r");  // Open the file for reading
    if (!fptr) {
        perror("Error opening file");
        free(fName);  // Free the allocated memory
        return;
    }

    // Print the contents of the file
    printf("\n");
    int ch;
    while ((ch = fgetc(fptr)) != EOF) {
        putchar(ch);  // Output each character
    }

    fclose(fptr);  // Close the file
    free(fName);   // Free the allocated memory
}

// Function to create a new file and write to it
void writeF(void) {
    printf("Enter file name: ");
    char *fName = getFile();  // Get the file name from the user
    if (!fName) {
        fprintf(stderr, "ERROR: failed to read file name!\n");
        return;
    }
    if (strlen(fName) == 0) {
        printf("No file name entered.\n");
        free(fName);  // Free the allocated memory
        return;
    }

    FILE *fptr = fopen(fName, "w");  // Open the file for writing
    if (!fptr) {
        perror("Error creating file");
        free(fName);  // Free the allocated memory
        return;
    }

    printf("Enter text to write (end with an empty line):\n");
    // Read lines from the user and write them to the file
    while (1) {
        char *line = getFile();
        if (!line || strlen(line) == 0) {  // Empty line ends input
            free(line);
            break;
        }
        fprintf(fptr, "%s\n", line);  // Write the line to the file
        free(line);  // Free the allocated memory for the line
    }

    fclose(fptr);  // Close the file
    printf("File written successfully.\n");
    free(fName);  // Free the allocated memory for the file name
}

// Function to append text to an existing file
void appendF(void) {
    printf("Enter file name: ");
    char *fName = getFile();  // Get the file name from the user
    if (!fName) {
        fprintf(stderr, "ERROR: failed to read file name!\n");
        return;
    }
    if (strlen(fName) == 0) {
        printf("No file name entered.\n");
        free(fName);  // Free the allocated memory
        return;
    }

    FILE *fptr = fopen(fName, "a");  // Open the file for appending
    if (!fptr) {
        perror("Error opening file for append");
        free(fName);  // Free the allocated memory
        return;
    }

    printf("Enter text to append (end with an empty line):\n");
    // Read lines from the user and append them to the file
    while (1) {
        char *line = getFile();
        if (!line || strlen(line) == 0) {  // Empty line ends input
            free(line);
            break;
        }
        fprintf(fptr, "%s\n", line);  // Append the line to the file
        free(line);  // Free the allocated memory for the line
    }

    fclose(fptr);  // Close the file
    printf("Text appended successfully.\n");
    free(fName);  // Free the allocated memory for the file name
}

// Function to delete a file
void delFile() {
    printf("Enter file name: ");
    char *fName = getFile();  // Get the file name from the user
    if (!fName) {
        fprintf(stderr, "ERROR: failed to read file name!\n");
        return;
    }
    if (strlen(fName) == 0) {
        printf("No file name entered.\n");
        free(fName);  // Free the allocated memory
        return;
    }

    // Ask for confirmation to delete the file
    printf("Are you sure you want to delete '%s'? (y/n): ", fName);
    int confirm = getchar();
    while (getchar() != '\n');  // Clear the newline from the input buffer
    if (confirm != 'y' && confirm != 'Y') {
        printf("Delete canceled.\n");
        free(fName);  // Free the allocated memory
        return;
    }

    // Delete the file
    if (remove(fName) == 0) {
        printf("File deleted successfully.\n");
    } else {
        printf("Error: Unable to delete the file.\n");
    }

    free(fName);  // Free the allocated memory for the file name
}

int main(void) {
    titleSequence();  // Display the title sequence

    while (1) {
        printf("\n");
        puts(
            "________________\n"
            "|1. read\n"
            "|2. write\n"
            "|3. append\n"
            "|4. delete\n"
            "|5. list directory\n"
            "|6. Quit"
        );

        printf("|Option: ");

        char input[16];  // Buffer to store user input (enough for one char + newline)
        if (!fgets(input, sizeof(input), stdin)) {
            // If fgets fails, exit the program
            puts("\nInput error or EOF. Exiting...");
            break;
        }

        // Remove newline if present
        input[strcspn(input, "\n")] = '\0';

        // Determine the action based on user input
        char option = input[0];

        // Execute the corresponding function based on the user's choice
        switch (option) {
            case '1': readF(); break;
            case '2': writeF(); break;
            case '3': appendF(); break;
            case '4': delFile(); break;
            case '5': listDir(); break;
            case '6': printf("Exiting...\n"); return 0;  // Exit the program
            default: printf("Invalid option.\n"); break;
        }
    }

    return 0;
}