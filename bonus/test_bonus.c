#include <fcntl.h>
#include <stdio.h>
#include "get_next_line_bonus.h"

int main(void)
{
    int     fd1;
    int     fd2;
    char    *line;

    fd1 = open("test1.txt", O_RDONLY);
    fd2 = open("test2.txt", O_RDONLY);

    line = get_next_line(fd1);
    printf("File 1, Line 1: %s", line);
    free(line);

    line = get_next_line(fd2);
    printf("File 2, Line 1: %s", line);
    free(line);

    line = get_next_line(fd1);
    printf("File 1, Line 2: %s", line);
    free(line);

    close(fd1);
    close(fd2);
    return (0);
}
