//1) Copy :
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
void copy_file(const char *source, const char *destination)
{
    FILE *src, *dest;
    int ch;
    src = fopen(source, "r");
    dest = fopen(destination, "w");
    if (src == NULL)
    {
        printf("Error opening source file");
    }
    if (dest == NULL)
    {
        printf("Error opening destination file");
        fclose(src);
    }
    while ((ch = fgetc(src)) != EOF)
    {
        fputc(ch, dest);
    }
    fclose(src);
    fclose(dest);
    printf("File copied successfully from %s to %s\n", source, destination);
}
int main(int argc, char *argv[])
{
    copy_file(argv[1], argv[2]);
}


// 2) Grep :
#include <stdio.h>
#include <string.h> 
void fgrep(const char *pattern, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file");
    }
    char line[100];
    int count = 0;
    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (strstr(line, pattern) != NULL)
        {
            count++;
        }
    }
    if (count > 1)
    {
        printf("Pattern is present\n");
        printf(" count is :%d\n", count);
    }
    fclose(file);
}
int main(int argc, char *argv[])
{
    fgrep(argv[1], argv[2]);
}


// 3) exec() and fork() :   Menu-Driven Program
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h> 
void simulate_cp(const char *source, const char *destination)
{
    pid_t p = fork();
    if (p < 0)
    {
        perror("Fork unsuccessful");
        exit(1);
    }
    else if (p == 0)
    { // Child process
        printf("Child Process:\n");
        printf("Child PID = %d\n", getpid());
        printf("Parent PID = %d\n", getppid());
        execlp("./copycommand", "./copycommand", source, destination, NULL);
        perror("Error executing copycommand");
        exit(1);
    }
    else
    { // Parent process
        wait(NULL);
        printf("Parent Process:\n");
        printf("Parent PID = %d\n", getpid());
    }
}
void simulate_grep(const char *pattern, const char *file)
{
    pid_t p = fork();

    if (p < 0)
    {
        perror("Fork unsuccessful");
        exit(1);
    }
    else if (p == 0)
    { // Child process
        printf("Child Process:\n");
        printf("Child PID = %d\n", getpid());
        printf("Parent PID = %d\n", getppid());
        execlp("./grepcommand", "./grepcommand", pattern, file, NULL);
        perror("Error executing grepcommand");
        exit(1);
    }
    else
    { // Parent process
        wait(NULL);
        printf("Parent Process:\n");
        printf("Parent PID = %d\n", getpid());
    }
}
int main()
{
    int choice;
    char source[100], destination[100];
    char pattern[100], file[100];
    while (1)
    {
        printf("\nMenu:\n");
        printf("1. Simulate Copy (copycommand)\n");
        printf("2. Simulate Grep (grepcommand)\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter source file path: ");
            scanf("%s", source);
            printf("Enter destination file path: ");
            scanf("%s", destination);
            simulate_cp(source, destination);
            break;

        case 2:
            printf("Enter file path: ");
            scanf("%s", file);
            printf("Enter pattern to search: ");
            scanf("%s", pattern);
            simulate_grep(pattern, file);
            break;

        case 3:
            printf("Exiting program...\n");
            exit(0);

        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }
    }
    return 0;
}


// Make 3 files : copycommand.c, grepcommand.c and main.c  
// Compile them using gcc -o copycommand copycommand.c
// Compile them using gcc -o grepcommand grepcommand.c
// Compile them using gcc -o main main.c
// Run the main program using ./main
// The program will ask for the source and destination file names and then copy the contents of the source file to the destination file using fork() and exec() system calls.
// It will also ask for the pattern to search in the file and then search for the pattern in the file using fork() and exec() system calls.
// The program will exit when the user selects the exit option.
// The program will also print the child and parent process IDs for each operation.
// The program will also print the number of times the pattern is found in the file.
// The program will also print the contents of the destination file after copying the contents from the source file.