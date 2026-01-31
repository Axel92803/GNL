#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>  // For open()

int main(void)
{
    int     fd;
    char    *line;

    printf("--- Test 1: Reading from 'test.txt' ---\n");

    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Error: Could not open test.txt. Make sure it exists.\n");
        return (1);
    }

    int line_count = 1;
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line %d: %s", line_count++, line);
        free(line);
    }
    printf("\n(EOF Reached)\n");
    close(fd);

    printf("\n--- Test 2: Invalid File Descriptor (42) ---\n");
    line = get_next_line(42);
    if (line == NULL)
        printf("Success: Function returned NULL for invalid FD.\n");
    else
    {
        printf("Failure: Function returned a pointer for invalid FD.\n");
        free(line);
    }
}
