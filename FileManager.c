#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#define BLUE   "\033[1;34m"
#define GREEN  "\033[1;32m"
#define YELLOW "\033[1;33m"
#define RED    "\033[1;31m"
#define RESET  "\033[0m"

void titleSequence(void);

char *getF(void);
void readF(const char *filename);
void writeF(const char *filename);
void appendF(const char *filename);
void listDir(void);
void delFile(const char *filename);

int main(void) {
    printf(BLUE);
    titleSequence();
    printf(RESET);

    while (1) {
        int op;
        printf(GREEN
            "__________________\n"
            "Options:\n"
            "1. Read\n"
            "2. Write\n"
            "3. Append\n"
            "4. List Directory\n"
            "5. Delete File\n"
            "6. Exit\n"
            "Option: "
            RESET);

        if (scanf("%d", &op) != 1) {
            while (getchar() != '\n');
            printf(RED "Invalid input! Please enter a number.\n" RESET);
            continue;
        }
        getchar(); // consume newline

        if (op == 1)
            readF(getF());
        else if (op == 2)
            writeF(getF());
        else if (op == 3)
            appendF(getF());
        else if (op == 4)
            listDir();
        else if (op == 5)
            delFile(getF());
        else if (op == 6)
            break;
        else
            printf(RED "Invalid input!\n" RESET);
    }

    printf("\n" BLUE "Goodbye!\n" RESET);
    return 0;
}

void titleSequence(void) {
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

char *getF(void) {
    static char filename[256];
    printf(YELLOW "Enter Filename: " RESET);
    if (fgets(filename, sizeof(filename), stdin) == NULL) {
        printf(RED "Error reading filename!\n" RESET);
        return NULL;
    }

    size_t len = strlen(filename);
    if (len > 0 && filename[len - 1] == '\n')
        filename[len - 1] = '\0';

    if (strlen(filename) == 0) {
        printf(RED "No filename entered!\n" RESET);
        return NULL;
    }

    return filename;
}

void readF(const char *filename) {
    printf("____________________\n");
    if (!filename) return;

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file for reading");
        return;
    }

    printf(YELLOW "Reading file: %s\n" RESET, filename);
    int c;
    while ((c = fgetc(file)) != EOF)
        putchar(c);
    fclose(file);
    printf("\n____________________\n");
}

void writeF(const char *filename) {
    if (!filename) return;

    struct stat st;
    if (stat(filename, &st) == 0) { // file exists
        printf(YELLOW "File '%s' exists. Overwrite? (y/n): " RESET, filename);
        int confirm = getchar();
        while (getchar() != '\n' && !feof(stdin));
        if (confirm != 'y' && confirm != 'Y') {
            printf(RED "Write canceled.\n" RESET);
            return;
        }
    }

    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file for writing");
        return;
    }

    printf(YELLOW "Writing to file: %s\n" RESET, filename);
    printf(YELLOW "Enter text to write (end with a single '.' on a line):\n" RESET);
    char buffer[256];
    while (1) {
        if (!fgets(buffer, sizeof(buffer), stdin))
            break;
        if (buffer[0] == '.' && buffer[1] == '\n')
            break;
        fputs(buffer, file);
    }

    fclose(file);
    printf(GREEN "File write successful\n" RESET);
}

void appendF(const char *filename) {
    if (!filename) return;
    FILE *file = fopen(filename, "a");
    if (!file) {
        perror("Error opening file for append");
        return;
    }

    printf(YELLOW "Appending to file: %s\n" RESET, filename);
    printf(YELLOW "Enter text to append (end with a single '.' on a line):\n" RESET);
    char buffer[256];
    while (1) {
        if (!fgets(buffer, sizeof(buffer), stdin))
            break;
        if (buffer[0] == '.' && buffer[1] == '\n')
            break;
        fputs(buffer, file);
    }

    fclose(file);
    printf(GREEN "File append successful\n" RESET);
}

int cmpStrings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

void listDir(void) {
    printf(GREEN "Listing current directory contents:\n\n" RESET);
    DIR *d = opendir(".");
    if (!d) {
        perror("Error opening current directory");
        return;
    }

    struct dirent *dir;
    char *names[512];
    int count = 0;

    while ((dir = readdir(d)) != NULL && count < 512) {
        names[count++] = strdup(dir->d_name);
    }
    closedir(d);

    qsort(names, count, sizeof(char *), cmpStrings);

    for (int i = 0; i < count; i++) {
        struct stat st;
        if (stat(names[i], &st) == 0) {
            if (S_ISDIR(st.st_mode))
                printf(BLUE "%s/\n" RESET, names[i]);
            else if (st.st_mode & S_IXUSR)
                printf(YELLOW "%s*\n" RESET, names[i]);
            else
                printf(GREEN "%s\n" RESET, names[i]);
        } else {
            printf(RED "%s ?\n" RESET, names[i]);
        }
        free(names[i]);
    }
    printf("\n");
}


void delFile(const char *filename) {
    if (!filename || strlen(filename) == 0) {
        fprintf(stderr, RED "No valid filename entered!\n" RESET);
        return;
    }

    printf(YELLOW "Are you sure you want to delete '%s'? (y/n): " RESET, filename);
    int confirm = getchar();
    while (getchar() != '\n' && !feof(stdin));

    if (confirm != 'y' && confirm != 'Y') {
        printf(RED "Delete canceled.\n" RESET);
        return;
    }

    if (remove(filename) == 0)
        printf(GREEN "File deleted successfully.\n" RESET);
    else
        perror("Error deleting file");
}
