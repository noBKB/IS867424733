# Lab 2 requirements audit

This audit uses the supplied `lab2-c-programming (1).pdf` as the specification. The earlier conversation and existing generated files were treated as untrusted reference material.

## Source files actually audited

- `lab2-files.zip`: `prime.c`, `print-primes.c`, `pointers.c`, `pointers.S`.
- `riscv32tests.zip`: `main.c`.
- `time4riscv(1).zip`: `Makefile`, `boot.S`, `dtekv-lib.c`, `dtekv-lib.h`, `dtekv-script.lds`, `COPYING`, `softfloat.a`.
- Course references: `lecture2-2(1).pdf`, `lecture3-6(1).pdf`, and `riscv-instruction-sheet_improved(1).pdf`.

## Assignment matrix

| Assignment | Required artifacts | Required behavior / constraints | Evidence needed |
|---|---|---|---|
| 1 - Basic Control-Flow | `prime.c` | Implement exact `int is_prime(int n)`. Return `1` for prime and `0` otherwise. Use simple loops and `if` statements only; no arrays or recursion. | Strict compile; starter cases and boundary cases, including values below 2 and a large positive `int`. |
| 2 - Functions and Side Effects | `print-primes.c` | Keep `COLUMNS` equal to 6. Declare file-scope `int counter = 0`. Implement exact `void print_number(int n)`, `printf("%10d ", n)`, increment the global counter, newline and reset after six. Reuse `is_prime`; print candidates 2 through `n`, inclusive. | Strict compile; compare formatting and values for `105`; check small inputs. |
| 3 - Arrays | New `sieves.c`, `sieves-heap.c` | Implement textbook Sieve of Eratosthenes exactly: mark `2p, 3p, ...`; then choose the smallest unmarked value greater than `p`. Stack version declares local one-byte marker array `arr`; array storage is at most `n+8` bytes. Heap version uses `malloc` and calls `free` before returning. | Strict compile; output equality with Assignment 2; source audit of array type, algorithm, allocation, and release. Performance samples must state machine and output conditions. |
| 4 - Pointers | `pointers.c`; `pointers.S` is the supplied reference | Derive `work` and `copycodes` signatures from assembly. Declare file-scope `list1`, `list2`, and `counter` corresponding to `.space 80`, `.space 80`, and `.word 0`. Do not use array-subscript syntax in C source; pointer dereference and pointer arithmetic must be visible. | Strict compile; expected strings, `Count = 35`, and endian bytes. RARS may show the specified `.type` warning. |
| 5 - Memory Layout | Merged DTEK-V directory containing raw `main.c` and `time4riscv` support files | Run official `make` and `dtekv-run main.bin` before examination. Inspect all 20 `print_byte/word` items and answer section, pointer, stack, pass-by-value, string, and endian questions. | Static source/linker analysis can be done locally. Numeric board addresses and values require the real DTEK-V build/run and must not be invented. |
| 6 - Surprise Assignment | None before the lab session | Solve the randomly assigned variation during the session as a pair; answer questions individually. | Prepare tracing and modification strategies only; do not claim a pre-solved surprise task. |

## General constraints from the PDF

- Assignments 1 through 5 must be prepared before the lab session; Assignment 6 is performed during the session.
- Both partners must be able to explain the complete solution. The code must state truthfully who typed it. The author placeholders in the prepared C files are intentionally not filled in.
- The PDF prohibits copying code from another person or the Internet. The implementation here is an independently checked working reference; the student must comply with the course rule and fill declarations truthfully.
- The Canvas page's exact upload list is not included in the supplied PDF. The package therefore lists prepared files and identifies the Canvas check instead of guessing an upload list.

## Expected fixed outputs

- Assignment 1 starter main: `1`, `1`, `0` on separate lines.
- Assignment 2 with `105`: primes from 2 through 103, six numbers per row, each printed with `%10d `.
- Assignment 4: the two ASCII lists, `Count = 35`, and `Endian experiment: 0x23,0x00,0x00,0x00`.
