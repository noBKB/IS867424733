# KTH IS1200/IS1500 Lab 2 - C Programming

This package was rechecked on 2026-09-16 from the supplied 2026 Lab 2 PDF and the raw starter archives. The existing earlier generated files were not used as proof.

## Prepared C files (Assignments 1-4)

From the directory containing the source files, use GCC with the strict warning flags required for this verification:

```text
gcc -std=c11 -Wall -Wextra -pedantic prime.c -o prime
./prime

gcc -std=c11 -Wall -Wextra -pedantic print-primes.c -o print-primes
./print-primes 105

gcc -std=c11 -Wall -Wextra -pedantic sieves.c -o sieves
./sieves 105

gcc -std=c11 -Wall -Wextra -pedantic sieves-heap.c -o sieves-heap
./sieves-heap 105

gcc -std=c11 -Wall -Wextra -pedantic pointers.c -o pointers
./pointers
```

The verified `105` outputs from `print-primes`, `sieves`, and `sieves-heap` are byte-for-byte equal. `pointers` must include `Count = 35` and `Endian experiment: 0x23,0x00,0x00,0x00`.

The stack sieve uses a variable-length local `char` array as required. Very large inputs can exceed the host's default stack size; that is a host limitation of the required stack allocation. The heap version is the suitable comparison for large local inputs.

Every prepared C source has a `LAB AUTHOR DECLARATION` placeholder. Replace it only with the truthful person(s) who actually typed that assignment. Do not insert an inferred name and do not remove the supplied David Broman comments.

## Assignment 4 and RARS

The supplied `pointers.S` intentionally jumps to `stop` after calling `work`, so a direct RARS simulation does not terminate. RARS 1.6 may report the expected warning that it ignores `.type`. The re-verification used a temporary copy with only the stop loop changed to exit syscall 10; the original `pointers.S` remains unchanged.

## Assignment 5 - DTEK-V

The prepared `assignment5/` directory contains the raw `riscv32tests/main.c` merged with the eight files from `time4riscv`. The supplied Makefile flow is:

```text
cd assignment5
make
dtekv-run main.bin
```

Run this on the KTH lab machine or a correctly configured DTEK-V toolchain. The current Windows environment has no official `make`, `riscv32-unknown-elf-*` toolchain, or `dtekv-run`, and no board connection. Consequently this package does not claim a `main.elf`, `main.bin`, runtime address, or host-monitor value. Use `assignment5-analysis.md` to prepare the explanations, then fill the actual addresses and values from the board output.

## Assignment 6

Assignment 6 is the in-session surprise assignment. It is deliberately not implemented in advance; `oral-prep.md` contains only tracing and problem-solving preparation.

## Submission note

The supplied PDF says that the Canvas page lists the exact upload files, but that Canvas list was not included in the supplied materials. The clean archive therefore contains the prepared source set and notes without claiming that this is the exact Canvas list. Check the Canvas assignment before uploading. See `submission-manifest.md` for the distinction between prepared files, supplied references, and verification-only material.

## Evidence

Read `requirements.md` for the PDF requirements matrix, `source-audit.md` for raw archive hashes and assembly derivation, `test-report.md` for commands and observed results, and `assignment5-analysis.md` for the complete static AM1-AM19/AF1 table.
