*This project has been created as part of the 42 curriculum by hasanaboutak.*

# get_next_line (42)

## Description
`get_next_line` is a 42 curriculum project that implements a function able to read from a file descriptor **line by line**, returning one line per call.

The goal is to practice:
- Low-level I/O with `read(2)`
- Buffer management via `BUFFER_SIZE`
- Careful dynamic memory handling (allocation, concatenation, and freeing)
- Correct behavior across edge cases (EOF, empty files, no trailing newline, huge lines)

This repository contains:
- **Mandatory** implementation: `get_next_line.c`, `get_next_line_utils.c`
- **Bonus** implementation (multiple file descriptors): `get_next_line_bonus.c`, `get_next_line_utils_bonus.c`

## Instructions

### Requirements
- A C compiler (e.g., `cc`/`clang`)
- macOS or Linux

### Compile (mandatory)
From the repository root:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

Run:

```sh
./gnl
```

### Compile (bonus)

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main_bonus.c -o gnl_bonus
```

Run:

```sh
./gnl_bonus
```

### Notes
- Change the chunk size by changing `BUFFER_SIZE` at compile time (e.g., `-D BUFFER_SIZE=1` or `-D BUFFER_SIZE=1000000`).
- Expected signature:
  ```c
  char *get_next_line(int fd);
  ```
- Expected behavior:
  - Returns a newly allocated string containing the next line (including `\n` if present).
  - Returns `NULL` when there is nothing left to read or on error.

## Algorithm (Detailed Explanation + Justification)

### Core idea: a persistent “stash” between calls
`read(2)` returns arbitrary-sized chunks; a “line” ends at `\n`, which may occur anywhere (or not at all). To return exactly one line per call without losing data, the function must preserve unread leftovers across calls.

This is achieved with a persistent buffer often called a **stash**:
- After each `read`, append the chunk to the stash.
- If the stash contains a newline, extract and return the next line.
- Keep the remainder in the stash for the next call.

For the **bonus**, the exact same approach is used, except the stash is **per file descriptor** (commonly a static array indexed by `fd`, so concurrent calls on different FDs do not mix state).

### Step-by-step behavior
On each call `get_next_line(fd)`:

1. **Validate inputs**
	- If `fd < 0` or `BUFFER_SIZE <= 0`, return `NULL`.

2. **Read until a full line is available or EOF**
	- Allocate a temporary buffer of size `BUFFER_SIZE + 1`.
	- While the stash has no `\n` and `read(fd, buf, BUFFER_SIZE)` returns `> 0`:
	  - Null-terminate: `buf[n] = '\0'`.
	  - Append `buf` to the stash (string join).

3. **Stop if nothing to return**
	- If EOF reached and the stash is empty, return `NULL`.

4. **Extract exactly one line**
	- If stash contains `\n`, the returned line is everything up to and including that `\n`.
	- Otherwise (EOF without newline), the returned line is the entire stash.
	- Allocate the line and copy it out.

5. **Update the stash**
	- Remove the returned line portion from the stash.
	- Keep the remainder for the next call.
	- If nothing remains, free the stash and set it to `NULL`.

### Why this algorithm?
- **Correctness across chunk boundaries**: a newline can split across reads; the stash ensures lines are reconstructed correctly.
- **One-line-per-call contract**: leftovers are preserved so subsequent calls return subsequent lines.
- **Bonus friendliness**: one stash per FD enables interleaved reading from multiple descriptors.

### Complexity (high-level)
Let $N$ be the number of bytes consumed to produce the returned line.
- Time: $O(N)$ to build + extract the line (joining strategy affects constant factors).
- Space: $O(N)$ for the stash plus the returned line.

### Edge cases covered by design
- Empty file: first call returns `NULL`.
- Single line without trailing newline: returns that line, then `NULL`.
- Very large lines: multiple reads accumulate in stash until newline/EOF.
- `BUFFER_SIZE=1`: still correct (more iterations).

## Usage example

```c
int fd = open("test.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)) != NULL)
{
	 // use line
	 free(line);
}
close(fd);
```

## Resources

### References
- `read(2)` manual: https://man7.org/linux/man-pages/man2/read.2.html
- `open(2)` manual: https://man7.org/linux/man-pages/man2/open.2.html
- `malloc(3)` / `free(3)` manuals:
  - https://man7.org/linux/man-pages/man3/malloc.3.html
  - https://man7.org/linux/man-pages/man3/free.3.html
- The C Programming Language (Kernighan & Ritchie) — core C/string fundamentals

### How AI was used
AI (GitHub Copilot / GPT-5.2) was used for documentation tasks only:
- Drafting/structuring this `README.md`
- Writing the algorithm explanation and complexity summary

No AI-generated code was inserted into the `.c` sources as part of this README change.

---

If your 42 intra login is not `hasanaboutak`, update the first line accordingly.
