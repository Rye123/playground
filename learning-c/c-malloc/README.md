# c-malloc

This is a basic implementation of `malloc()` and `free()`, using the `sbrk()` system call to dynamically allocate memory.
- Here, we have a `memblock` which keeps track of the size, the freed status and the next `memblock`.
- This allows for `free()` to be naively implemented -- allowing us to reuse freed blocks with sufficient space.

## TODO
- Splitting of the allocated `memblock` space to allow better, more efficient usage of already-allocated but freed memory.
- Actual freeing of contiguous memory that has been marked as freed.