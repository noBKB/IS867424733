# Assignment 5 - static memory-layout analysis

This analysis is based on the raw `riscv32tests/main.c`, `dtekv-script.lds`, `boot.S`, the DTEK-V library, and the lecture material. The official cross compiler and DTEK-V board were not available in this environment, so the numeric addresses and instruction words are intentionally left as board-run fields.

## What the helper functions print

`print_word(str, ptr)` prints the address passed as `ptr`, then reads one 32-bit word at that address and prints that word as an unsigned decimal value. `print_byte(str, ptr)` prints the address and reads one byte as an unsigned value. Thus the label describes the expression passed to the helper; it is not necessarily the value printed as `value=`.

## All 20 observations

| Item | Source expression | Address printed | Value printed / meaning | Static region and explanation |
|---|---|---|---|---|
| AM1 | `&gv` | address of `gv` | `4` | `.bss` global; it starts zero-initialized and is assigned `4` before the call. |
| AM2 | `&in` | address of `in` | `3` | `.data` global because it has the initializer `3`. |
| AM3 | `&fun` | address of the function entry | first 32-bit machine-instruction word at `fun` | `.text`; code is stored as words, so the address points to an instruction. Numeric value depends on the actual link. |
| AM4 | `&main` | address of the function entry | first 32-bit machine-instruction word at `main` | `.text`; numeric value depends on the actual link and compiler output. |
| AM5 | `&p` | address of the local pointer variable `p` | the pointer value `p`, which is `&m` | stack; `print_word` reads the word stored in the pointer slot. |
| AM6 | `&m` | address of local integer `m` | `7` | stack; `m = gv + in` before `*p` is incremented. |
| AM7 | `&p` | same address of the pointer slot | still `&m` | stack; `*p = *p + 1` changes the pointed-to integer, not the pointer variable. |
| AM8 | `&m` | same address of `m` | `8` | stack; `p` points to `m`, so dereferencing `p` incremented `m`. |
| AM9 | `&p` | address of the pointer slot | address of `cs`, because `p = (int*)cp` | stack; the pointer variable remains in its slot while its stored value changes. |
| AM10 | `&cs[0]` | address of first byte of `cs` | `66` (`'B'`) | stack byte array; first byte of `"Bonjour!"`. |
| AM11 | `&cs[1]` | address of second byte of `cs` | `111` (`'o'`) | stack byte array. |
| AM12 | `&cs[2]` | address of third byte of `cs` | `110` (`'n'`) | stack byte array. |
| AM13 | `&cs[3]` | address of fourth byte of `cs` | `106` (`'j'`) | stack byte array. |
| AM14 | `&cs[0]` | address of first byte of `cs` | `205` (`0xcd`) | little-endian low byte after `*p = 0x1234abcd`. |
| AM15 | `&cs[1]` | address of second byte of `cs` | `171` (`0xab`) | next little-endian byte. |
| AM16 | `&cs[2]` | address of third byte of `cs` | `52` (`0x34`) | next little-endian byte. |
| AM17 | `&cs[3]` | address of fourth byte of `cs` | `18` (`0x12`) | most significant byte of the stored word. |
| AF1 | `&param` inside `fun` | address of `fun`'s local parameter copy | `9` | stack; `fun` increments its pass-by-value copy of `m` and prints it. |
| AM18 | `&m` | address of `m` | `8` | stack; passing `m` to `fun` did not modify the caller's variable. |
| AM19 | `&gv` | address of `gv` | `9` | `.bss` global; `fun` stores its incremented parameter into `gv`. |

The calls occur in source order: AF1 is printed inside `fun(m)`, before AM18 and AM19.

## Direct answers to the official questions

### AM18, AM19, and AF1

`fun(int param)` receives a copy of `m`. It increments `param` from 8 to 9 and stores that value into the global `gv`. The original `m` remains 8, so AM18 is 8 and AM19 is 9. AF1 shows the separate stack parameter copy with value 9.

### Size of `cp`

`cp` points to characters, but the pointer itself is an RV32 address. A pointer occupies 4 bytes on the RISC-V/32 target; its pointed-to type controls how dereferencing and pointer arithmetic work, not the pointer's own size.

### Why `cs` has 9 bytes

`"Bonjour!"` has eight visible characters: `B o n j o u r !`. A C string also stores a terminating NUL byte, so the array needs `8 + 1 = 9` bytes.

### `fun` and `main`

Both are functions in `.text`. Their symbols' addresses point to instruction memory. The value read by `print_word` at either address is a 32-bit encoded RISC-V instruction, not a normal data integer. Exact addresses and words require the actual linker output.

### `in` and `gv`

Both are file-scope global variables. `in = 3` belongs in `.data`; `gv` has no initializer and belongs in `.bss`, although its runtime value is 4 at AM1 and 9 at AM19.

### `p` and `m`

They are local variables in `main`, so they are stored in the stack frame. `boot.S` initializes `sp` to `_stack_end`; the linker script places the stack after the lower-addressed code/data regions, so stack addresses are much larger than the addresses of `in` and `gv`. The stack grows downward as frames are used.

### AM5 and AM7

At AM5, `&p` is the address of the pointer slot, `p` is the value stored in that slot (`&m`), and `*p` would be the integer stored at `m`, namely 7. At AM7, `&p` and `p` are unchanged, while `*p` is now 8; the call prints `&p`, not `*p`.

### AM14 through AM17

The word `0x1234abcd` appears in memory as bytes `cd ab 34 12` at increasing addresses. The least significant byte is at the lowest address, so the RISC-V processor is little-endian.

## Linker layout to use when the board is available

The supplied linker script starts `.text` at `0x0`, then places `.data`, `.bss`, `.rodata`, and a `.stack` region. The exact symbols and stack addresses depend on the actual cross-compiled `main.elf`. After the official run, replace the address/value placeholders in the handwritten or uploaded notes with the host-monitor output; do not copy numeric addresses from another build.
