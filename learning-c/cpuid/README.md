Prints the CPU manufacturer ID.
- This was done for fun, as an introduction to assembly language calls in C.
- Since `CPUID` outputs to `EBX`, `EDX` and `ECX`, we then read those into C variables.
- Then, we interpret those as ASCII values by recasting their memory addresses to `char *`s.

Source: https://en.wikipedia.org/wiki/CPUID
