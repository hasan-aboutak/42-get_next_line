This project has been created as part of the 42 curriculum by <login>

get_next_line
Description
get_next_line is a C programming project whose goal is to implement a function capable of reading a file descriptor line by line, returning one line per function call.

The main challenge of this project is to manage buffered reading, persistent state between function calls, and dynamic memory allocation, while respecting strict constraints on allowed functions and coding style.

The function must:
- Read from any valid file descriptor (files or standard input)
- Return one line at a time, including the terminating \n when present
- Handle files with or without a trailing newline
- Work correctly with any buffer size
- Avoid memory leaks and undefined behavior

A bonus version extends the implementation to support multiple file descriptors simultaneously.
Instructions
Compilation
Mandatory part:
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c

Bonus part:
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c

If BUFFER_SIZE is not provided, a default value is defined in the header file.
Algorithm & Design Choices
The algorithm is based on maintaining a persistent buffer (stash) that stores unread data between function calls.

Each call to get_next_line() follows this pipeline:

1. Read and Accumulate:
- Read from the file descriptor into a temporary buffer
- Append the buffer to a static stash
- Stop reading as soon as a newline (\n) is found or EOF is reached

2. Extract Line:
- Allocate and return the first complete line from the stash
- Include the newline character if it exists

3. Clean Stash:
- Remove the extracted line from the stash
- Preserve remaining data for the next call
- Free the stash when no data remains

This approach ensures minimal reading, correct behavior for arbitrary buffer sizes, and efficient reuse of already-read data.
Static Variable Usage
A static variable inside get_next_line is used to preserve state between calls without relying on forbidden global variables.

For the bonus part, a static array indexed by file descriptor is used, allowing independent tracking of read positions for multiple file descriptors.
Memory Management
Special care is taken to ensure:
- Every allocation has a corresponding free
- No access to freed memory occurs
- No memory leaks remain at program termination

The design was validated using memory-checking tools such as Valgrind or AddressSanitizer.
Resources
Technical references:
- man 2 read
- man 3 malloc
- man 3 free
- GNU C Library Documentation
- Buffering and stream parsing concepts in C

AI Usage Disclosure:
AI assistance was used as a learning and review tool to clarify project requirements, discuss algorithm design and edge cases, review memory management strategies, and help structure documentation. All code was written, adapted, and validated by the student.
Final Notes
This project emphasizes low-level system programming concepts such as buffering, static storage duration, and careful memory handling. It serves as a foundational exercise for more advanced topics like socket programming and stream processing.
