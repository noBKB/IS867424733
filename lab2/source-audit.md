# Raw input and source audit

## Raw archive inventory

The uploaded attachment paths in the referenced task were resolved to the local temporary preview files and copied without modification into `original/`. SHA-256 values below identify the inputs used for this re-verification.

| Input | SHA-256 | Size |
|---|---|---:|
| `lab2-c-programming (1).pdf` | `CE82CFCAADEDBBE8EE7F7DF26B2C1258B22443804B25E004FFEE1B4391A02BAC` | 257825 |
| `lab2-files.zip` | `0AE00B931160F303EDC980609766DC2C3E5D1EED2FC8E3DE59F360DFBFC9F499` | 2923 |
| `riscv32tests.zip` | `4D6D8D80D223F5EBAAC6881868328F3B5CA042316B527B130F3CFFC90E5361D9` | 1013 |
| `time4riscv(1).zip` | `9F50C55ACE5499B4E1E61C464ECD844E9501BF5253DE95E57F048067F4ADA243` | 13973 |

## Starter content

`lab2-files.zip` contains exactly four entries:

- `prime.c`: the `is_prime` body returns `0`; the supplied main tests 11, 383, and 987.
- `print-primes.c`: `COLUMNS` is 6; the starter `print_primes` prints the same argument repeatedly as demonstration code; no `counter`, `is_prime`, or `print_number` implementation is supplied.
- `pointers.c`: strings, printing helpers, and main are supplied; `list1`, `list2`, `counter`, `work`, and `copycodes` are missing.
- `pointers.S`: complete RISC-V reference program. It declares two `.asciz` strings, two 80-byte buffers, and one word counter. `main` calls `work` and then intentionally spins at `stop`.

`riscv32tests.zip` contains exactly `riscv32tests/main.c`. The merged Assignment 5 directory contains this file plus the eight files from the `time4riscv` archive. There were no filename conflicts during the merge, and no supplied support file was overwritten.

## Assembly-to-C derivation

The relevant observations from `pointers.S` are:

- `work` loads addresses into `a0`, `a1`, and `a2`, calls `copycodes` twice, and returns without placing a result in `a0`; therefore its C form is `void work(void)`.
- `copycodes` reads through `a0` with `lb`, writes through `a1` with `sw`, reads and writes a word through `a2` with `lw`/`sw`, and returns without setting `a0`; therefore the C form is a `void` procedure with a byte source pointer, an `int` destination pointer, and an `int` counter pointer.
- `a0` advances by one byte and `a1` advances by four bytes. The C implementation uses `src++`, `dst++`, `*dst = *src`, and `(*count)++` to express the same operations.
- `list1[20]` and `list2[20]` reserve 80 bytes each, matching the assembly `.space 80` declarations. These are declarations only; no array-subscript access is used.

The assembly uses `lb`, not `lbu`, so the C assignment keeps the source value as a `char` rather than forcing an unsigned-byte conversion. The supplied strings contain ASCII bytes, so the expected output is unchanged.

## Implementation decisions

- A1 uses `i <= n / i`, equivalent to checking through the square root without multiplying `i * i`.
- A3 uses a one-byte `char` marker array. The stack array is declared locally inside `print_sieves`; the heap version allocates the same number of bytes and frees it on the normal path.
- All five prepared C files keep an explicit author-declaration placeholder. No student name was inferred or inserted.
- `pointers.S` remains unchanged in the final source set. A separate temporary copy only replaces its intentional infinite stop loop with RARS exit syscall 10 for a bounded simulation test.

## Course-reference cross-check

- `lecture3-6.pdf` pages 13 and 22-28 were used for stored-program/code memory, RISC-V registers and calling convention, and stack behavior.
- `riscv-instruction-sheet_improved(1).pdf` was used to check `lb`, `lw`, `sw`, `la`, `.data`, `.text`, `.space`, and register roles.
- The duplicate `lecture3-6(1).pdf` contains the same relevant lecture material; no external web source was needed.
