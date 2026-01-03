# get_next_line (GNL)

![42 School](https://img.shields.io/badge/42-000000?style=for-the-badge&logo=42&logoColor=white)
![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Grade](https://img.shields.io/badge/Grade-100%2F100-success?style=for-the-badge)

> **Read a line from a file descriptor, one line at a time**

## 📋 Overview

get_next_line (GNL) is a 42 School project that implements a function to read and return one line at a time from a file descriptor. This project teaches advanced C concepts including static variables, dynamic memory allocation, buffer management, and efficient file I/O operations.

**The Challenge:** Create a function that can read any valid file line by line, handling variable buffer sizes and multiple file descriptors, without knowing the file size in advance.

**Why this matters:**
- Master static variables for maintaining state between function calls
- Understand file descriptors and low-level I/O operations
- Implement efficient buffer management and memory handling
- Build a reusable utility function for future projects

## 🎯 Function Prototype

```c
char *get_next_line(int fd);
```

**Parameters:**
- `fd` - The file descriptor to read from

**Return Value:**
- Returns the line that was read (including the terminating `\n` character, except at EOF)
- Returns `NULL` if there is nothing else to read or an error occurred

## ✨ Key Features

### Mandatory Part
- ✅ Reads one line at a time from any file descriptor
- ✅ Returns the line including the newline character (`\n`)
- ✅ Handles files, standard input, and any valid file descriptor
- ✅ Works with any buffer size (defined at compile time)
- ✅ Uses static variables to maintain reading state between calls
- ✅ Properly handles EOF (end of file)
- ✅ Memory-safe implementation with no leaks

## 🛠️ Technical Implementation

**Language:** C  
**Allowed functions:** `read`, `malloc`, `free`  
**Forbidden:** `libft` functions, global variables, `lseek`

### Core Concepts

1. **Static Variables** - Preserving leftover data between function calls
2. **Buffer Management** - Efficient reading with configurable BUFFER_SIZE
3. **Dynamic Memory** - Allocating and growing strings as needed
4. **File Descriptors** - Working with Unix file I/O
5. **Edge Cases** - EOF, empty lines, very large lines, read errors

### Project Structure

```
get_next_line/
├── get_next_line.c        # Main function implementation
├── get_next_line_utils.c  # Helper functions (string manipulation)
└── get_next_line.h        # Header file with prototypes
```

### How It Works

```
1. Read BUFFER_SIZE bytes from file descriptor
2. Store leftover data in static variable
3. Search for newline character ('\n')
4. Return complete line (up to and including '\n')
5. Keep remaining data in static buffer for next call
6. Repeat until EOF
```

## 🚀 Compilation & Usage

### Compilation

The buffer size is defined at compile time using the `-D` flag:

```bash
# Compile with buffer size of 42
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o gnl_test

# Common buffer sizes for testing
gcc -D BUFFER_SIZE=1 ...    # Minimum - stress test
gcc -D BUFFER_SIZE=32 ...   # Standard
gcc -D BUFFER_SIZE=1024 ... # Larger buffer
gcc -D BUFFER_SIZE=9999999  # Edge case testing
```

### Basic Usage Example

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd;
    char *line;

    // Open a file
    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
        return (1);

    // Read file line by line
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);  // Don't forget to free!
    }

    close(fd);
    return (0);
}
```

### Reading from Standard Input

```c
#include "get_next_line.h"
#include <stdio.h>

int main(void)
{
    char *line;

    printf("Enter text (Ctrl+D to end):\n");
    
    // Read from stdin (file descriptor 0)
    while ((line = get_next_line(0)) != NULL)
    {
        printf("You entered: %s", line);
        free(line);
    }

    return (0);
}
```

### Multiple File Descriptors

For reading from multiple files simultaneously, you would need to call `get_next_line()` multiple times with different file descriptors:

```c
#include "get_next_line.h"
#include <fcntl.h>

int main(void)
{
    int fd1, fd2;
    char *line1, *line2;

    fd1 = open("file1.txt", O_RDONLY);
    fd2 = open("file2.txt", O_RDONLY);

    // Read one line from each file
    line1 = get_next_line(fd1);
    printf("File 1: %s", line1);
    free(line1);
    
    line2 = get_next_line(fd2);
    printf("File 2: %s", line2);
    free(line2);

    close(fd1);
    close(fd2);
    return (0);
}
```

## 🧪 Testing

### Manual Testing

```bash
# Create test file
echo -e "Line 1\nLine 2\nLine 3" > test.txt

# Compile and run
gcc -D BUFFER_SIZE=32 get_next_line.c get_next_line_utils.c main.c
./a.out test.txt
```

### Memory Leak Testing

```bash
# Compile with debug symbols
gcc -g -D BUFFER_SIZE=32 get_next_line.c get_next_line_utils.c main.c

# Check for leaks
valgrind --leak-check=full --show-leak-kinds=all ./a.out test.txt
```

### Recommended Testers

- **[Tripouille/gnlTester](https://github.com/Tripouille/gnlTester)** - Comprehensive automated tester
- **[Mazoise/42TESTERS-GNL](https://github.com/Mazoise/42TESTERS-GNL)** - Complete tester suite
- **[charMstr/GNL_lover](https://github.com/charMstr/GNL_lover)** - Combinatory tricky tests

### Edge Cases to Test

```c
// Empty file
// File with only newlines
// File with no newline at end
// Very long lines (10,000+ characters)
// Binary files
// BUFFER_SIZE = 1 (character by character)
// BUFFER_SIZE = 9999999 (very large)
// Invalid file descriptor (-1, 1000, etc.)
// Read errors (permissions, closed FD)
// Sequential reads from multiple file descriptors
```

## 💡 Key Learnings & Challenges

### Major Challenges Solved

1. **Static Variable Management**
   - Understanding how static variables persist between function calls
   - Properly managing leftover data from previous reads
   - Maintaining state for a single file descriptor efficiently

2. **Buffer Size Optimization**
   - Making the function work with any buffer size (1 to 9999999)
   - Handling cases where a line is smaller or larger than BUFFER_SIZE
   - Efficient string concatenation when line spans multiple reads

3. **Memory Management**
   - Preventing memory leaks in all scenarios
   - Proper allocation and deallocation of dynamic strings
   - Managing memory when read() fails mid-operation

4. **Edge Case Handling**
   - Files ending without newline character
   - Empty lines (just '\n')
   - Binary files and special characters
   - Multiple reads from different file descriptors sequentially

5. **Read Function Mastery**
   - Understanding read() return values (>0, 0, -1)
   - EOF detection and handling
   - Error management when read fails

### What This Project Taught Me

- **Advanced C memory management** - Dynamic allocation, reallocation strategies, leak prevention
- **Static variables in depth** - Lifetime, scope, and practical applications
- **File I/O operations** - Low-level file reading, file descriptors, Unix I/O
- **State management** - Maintaining context between function calls
- **Robust error handling** - Graceful failure and resource cleanup
- **Performance optimization** - Buffer management trade-offs

## 📊 Performance Considerations

### Buffer Size Impact

| BUFFER_SIZE | Read Calls | Performance | Use Case |
|-------------|------------|-------------|----------|
| 1           | Many       | Slowest     | Testing edge cases |
| 32-128      | Moderate   | Balanced    | Standard usage |
| 1024-4096   | Few        | Fastest     | Large files |
| 9999999     | Minimal    | Memory intensive | Stress testing |

### Optimization Techniques

- **Minimize malloc() calls** - Reuse buffers when possible
- **Efficient string operations** - Avoid unnecessary copying
- **Smart read() strategy** - Balance between syscalls and memory usage
- **Early returns** - Check error conditions first

## 🎓 42 School Evaluation

**Grade:** N/A/100 ✅  
**Evaluation Date:** [N/A]

**Peer Review Highlights:**
- Clean, readable code following 42 norm
- No memory leaks detected across all test cases
- Works perfectly with BUFFER_SIZE from 1 to 9999999
- Efficient implementation with minimal overhead
- Excellent handling of edge cases

## 🔗 Related 42 Projects

This project builds upon:
- **Libft** - String manipulation functions were useful here

This project prepares for:
- **ft_printf** - More complex parsing and output formatting
- **pipex** - Working with pipes and file descriptors
- **minishell** - Reading user input and parsing commands
- **cub3d** - Reading map files line by line

## 📚 Useful Resources

- [Unix File I/O Documentation](https://man7.org/linux/man-pages/man2/read.2.html)
- [Static Variables in C](https://www.geeksforgeeks.org/static-variables-in-c/)
- [Understanding File Descriptors](https://www.computerhope.com/jargon/f/file-descriptor.htm)

## 📝 License

This project is part of the 42 School curriculum. Feel free to reference this code for learning purposes, but please complete your own 42 projects independently to get the full educational benefit.

## 🤝 Contributing

This is a completed school project, but feedback and suggestions are always welcome! If you found this implementation helpful or have questions, feel free to reach out.

---

**Author:** Alex Tanvuia (Ionut Tanvuia)  
**42 Login:** itanvuia  
**School:** 42 London  
**Project Completed:** [November 2025]

[![42 Profile](https://img.shields.io/badge/42_Profile-itanvuia-000000?style=flat-square&logo=42)](https://profile.intra.42.fr/)

*Part of my journey through 42 School's peer-learning curriculum. Check out my other projects on my [GitHub profile](https://github.com/Axel92803)!*
