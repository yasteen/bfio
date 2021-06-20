# Brainfuck interpreter

This program is an extended brainfuck interpreter that
also supports file reading/writing.

As a recap, the standard brainfuck language follows this
model (as referenced by Wikipedia): There is a program
and an instruction pointer. There is also a 1D array of
at least 30000 x 1 byte cells each initialized to the
value 0. This array is accessed by a movable data pointer
and two streams of bytes for input and output with ASCII
character encoding.

the standard 8 language commands are as follows:
- `>` Increments the data pointer to point to the next
cell to the right
- `<` Decrements the data pointer to point to the next
cell to the left
- `+` Increments the byte at the data pointer by 1
- `-` Decrements the byte at the data pointer by 1
- `.` Outputs the byte at the data pointer
- `,` Accepts one byte of input, storing its value in
the byte at the data pointer
- `[` If the byte at the data pointer is 0, then instead
of moving the instruction pointer to the next command, it
jumps forward to the command right after the matching `]`
command.
- `]` If the byte at the data pointer is NOT 0, then
instead of moving the instruction pointer to the next
command, it jumps backward to the command right after the
matching `[` command.

Now for the new file IO operations:

To open a file, we specify a path, length of path string
(the path string must be less than 256 characters), and
a byte for read/write info.

- `"` Triggers an open/close - only one file open at a time.
- `'` Skips a byte
- `:` Writes a byte to the file.
- ";" Reads a byte from the file, storing its value in
the byte at the data pointer.

For example, the data cells would look like this:
  v
| 9 | 48 | 65 | 6C | 6C | 6F | 2E | 74 | 78 | 74 |
  ^
would open a file called Hello.txt - the data pointer
points at the length of the string.
