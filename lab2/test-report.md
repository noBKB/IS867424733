# Lab 2 verification report

Verification date: 2026-09-16.

## Local C build

Environment: Windows, LLVM-MinGW `gcc` reporting Clang 22.1.8. Each prepared source was compiled separately with the requested strict command shape:

```text
gcc -std=c11 -Wall -Wextra -pedantic <source>.c -o <output>
```

Results:

| Source | Result |
|---|---|
| `prime.c` | exit 0, no diagnostics |
| `print-primes.c` | exit 0, no diagnostics |
| `sieves.c` | exit 0, no diagnostics |
| `sieves-heap.c` | exit 0, no diagnostics |
| `pointers.c` | exit 0, no diagnostics |

The binaries were written only under the re-verification build directory, not into the clean final archive.

## Assignment 1

The supplied starter main printed:

```text
1
1
0
```

An additional harness tested `0, 1, 2, 3, 4, 9, 25, 97, 98, 383, 987, 2147483647`; every result matched the expected prime/non-prime value and the harness exited 0. The `i <= n / i` condition also avoids `i * i` overflow in this test.

## Assignments 2 and 3

`print-primes 105`, `sieves 105`, and `sieves-heap 105` each exited 0 and produced byte-for-byte equal output. The output contains 27 primes and 4 newlines; the final partial row contains `97`, `101`, and `103` with the required `%10d ` formatting.

The same three programs were compared for `n = 0, 1, 2, 3, 4, 10, 105, 1000`. Every comparison was equal and every process exited 0. Inputs below 2 produce no prime output.

The stack sieve source has a local `char arr[limit + 1U]`; the heap version allocates the same one-byte marker storage and calls `free(arr)` on the normal path. A source audit confirmed that the stack implementation follows the PDF's `2p, 3p, ...` marking step rather than starting at `p*p`. AddressSanitizer compiled and ran the heap version for `n=1000` with exit 0 and no report.

### Performance samples

These are one-run, local samples from the strict build without `-O`; stdout was redirected to the PowerShell null sink. They are not DTEK-V measurements and are not exact largest-number claims.

| Program | n | Time (s) | Exit |
|---|---:|---:|---:|
| `print-primes` | 1,000,000 | 0.17 | 0 |
| `print-primes` | 5,000,000 | 1.55 | 0 |
| `print-primes` | 6,000,000 | 2.00 | 0 |
| `print-primes` | 10,000,000 | 4.09 | 0 |
| `print-primes` | 15,000,000 | 7.26 | 0 |
| `print-primes` | 18,000,000 | 9.39 | 0 |
| `print-primes` | 20,000,000 | 10.90 | 0 |
| `sieves` | 1,000,000 | 0.02 | 0 |
| `sieves` | 1,500,000 | 0.01 | `-1073741571` (Windows stack overflow) |
| `sieves` | 5,000,000 | 0.01 | `-1073741571` (Windows stack overflow) |
| `sieves-heap` | 1,000,000 | 0.01 | 0 |
| `sieves-heap` | 5,000,000 | 0.06 | 0 |
| `sieves-heap` | 10,000,000 | 0.09 | 0 |
| `sieves-heap` | 50,000,000 | 0.42 | 0 |
| `sieves-heap` | 100,000,000 | 0.93 | 0 |

On this Windows executable, trial division is around 5-6 million at two seconds and around 18-20 million at ten seconds. The stack version reaches the local default stack limit near 1.0-1.5 million because the assignment requires its marker array to be on the stack. The heap version passed 100 million in under one second; no artificial maximum search was performed. The comparison illustrates why the answer depends on compiler, stack limit, CPU, and output path.

## Assignment 4

The C program exited 0 and contained both required substrings:

```text
Count = 35
Endian experiment: 0x23,0x00,0x00,0x00
```

The source bracket audit found `[` and `]` only in the required declarations `int list1[20];` and `int list2[20];`; there is no array-subscript access expression.

RARS 1.6 was run against a temporary copy of `pointers.S` whose intentional stop loop was replaced by exit syscall 10. It exited 0, emitted only the expected warning that RARS ignores `.type`, and its `.data` dump contained `00000023` for the shared counter. The dump also showed the four-byte integer values for both copied strings at successive word boundaries. The original `pointers.S` was not modified.

## Assignment 5

The raw `main.c` was merged with the eight supplied `time4riscv` support files without filename conflicts. The current host does not provide the official `make`, `riscv32-unknown-elf-gcc`, `riscv32-unknown-elf-ld`, `riscv32-unknown-elf-objcopy`, or `dtekv-run` commands. A `mingw32-make` attempt also exposed the Unix-only `rm/find` assumptions in the supplied Makefile. An LLVM-MinGW Clang target attempt failed because this installation has no RISC-V backend.

Therefore no `main.elf`, `main.bin`, board output, runtime addresses, or host-monitor values are claimed. The complete static AM1-AM19/AF1 analysis is in `assignment5-analysis.md`; the official build and board run remain required on a KTH lab machine or a correctly configured DTEK-V environment.

## Assignment 6

No surprise assignment was implemented in advance. Oral preparation contains tracing strategies and likely variations only.

## Final packaging check

The clean candidate directory was compiled again after copying the final source files. All five strict compilations exited 0 with no diagnostics. `lab2-final.zip` was reopened with a ZIP integrity check: `testzip=None`, five entries, and no forbidden binary/temp extensions. Its SHA-256 is `ED1EAF946B109CF3246AA4025CC85CAC1A6917CC4530A409C38E8A0E4DBC3BD8` and its size is 3052 bytes. The previous archive was copied to `previous-root-artifacts/lab2-final.previous-20260916.zip` before replacement.
