# IS1200/IS1500 Lab 2 oral preparation

This note is a study guide, not a substitute for understanding or for the student's truthful author declaration. The official questions are kept in the same order as the 2026 Lab 2 PDF.

## Assignment 1 - Basic Control-Flow

### 30-second answer

`is_prime(int n)` returns `0` for values below 2. Otherwise it tests possible divisors `i` from 2 while `i <= n / i`; if `n % i == 0`, the number is composite and the function returns 0. If no divisor is found, it returns 1. The implementation uses only a loop and `if` statements.

### If the teacher asks more

A prime number（质数）greater than 1 has exactly two positive divisors: 1 and itself. If a composite number is written as `n = a * b`, at least one of `a` or `b` is at most `sqrt(n)`, so checking past the square root cannot discover a first divisor that was missed. The `%` operator gives the remainder; a remainder of zero means exact divisibility. `i <= n / i` expresses `i * i <= n` without multiplying and risking overflow.

### Common traps

- 1 is not prime. 2 and 3 are prime; 4, 9, and 25 are not.
- The upper bound in the loop is safe for the positive `int` test domain; do not replace it with an unchecked `i * i <= n`.
- The assignment forbids arrays and recursion in `is_prime`.

## Assignment 2 - Functions and Side Effects

### 30-second answer

`void` means that `print_number` returns no value. It still performs useful work by printing an integer and changing the file-scope global variable `counter`. After each `printf("%10d ", n)`, it increments `counter`; when the value reaches `COLUMNS` (6), it prints a newline and resets the counter. `print_primes` tests every candidate from 2 through `n`, inclusive, using `is_prime` and sends prime candidates to `print_number`.

### Official question: What does a function that returns no value mean?

The return type is written `void`. The caller does not receive a return value, but the procedure can still have observable effects, such as printing, changing an object through a pointer, or changing the required global `counter` state.

### Official question: How is the side effect implemented?

The side effect（副作用）is the update of `counter`, which is outside the parameter list and persists across calls. A global variable（全局变量） is used because `print_number` receives only `n` and therefore cannot otherwise remember the current column. This is convenient for this teaching exercise but poor general design because unrelated code can change the state, call order matters, and reuse or concurrency becomes harder to reason about.

### Formatting details

`%10d` is a minimum field width of ten characters and right-aligns an integer. The literal space after `d` separates columns. The newline is printed after every sixth number; the helper does not need to infer a newline from `n` itself.

## Assignment 3 - Arrays and Sieve of Eratosthenes

### 30-second answer

The marker array represents the consecutive integers 2 through `n`. First all markers are clear and `p` is 2. The code marks `2p, 3p, 4p, ...` through `n`, finds the smallest unmarked value strictly greater than `p`, and repeats. When there is no such value, the remaining unmarked entries are prime and are printed with the Assignment 2 helper. `sieves.c` declares the one-byte `char arr` locally on the stack; `sieves-heap.c` allocates the same marker storage with `malloc` and releases it with `free`.

### Official question: What are the main algorithm steps?

1. Represent the integers 2 through `n` in the marker array.
2. Set `p = 2`.
3. Mark the multiples `2p, 3p, 4p, ...`; do not mark `p` itself.
4. Find the smallest unmarked number greater than `p`. Stop if none exists; otherwise make it the new `p`.
5. Print every remaining unmarked number.

The source follows this textbook order. It does not start at `p*p`, call `is_prime`, use a bitset, or introduce a different optimization.

### Stack, heap, and the memory limit

An array（数组） declared inside `print_sieves` has automatic stack（栈） storage and occupies one byte per marker because `char` is enough for the flag. `char arr[limit + 1U]` uses `n+1` bytes for the indexed representation, within the required `n+8` bytes. Heap（堆） storage from `malloc` remains allocated until `free`; the heap version checks for `NULL` and frees the successful allocation before returning.

### Official performance question

There is no machine-independent largest value. Trial division in `print-primes` repeats divisor tests, so it grows much more slowly than a sieve. The two sieve versions do similar marking work; stack and heap overhead and the machine's stack limit can differ. In the current strict Windows build, stdout was redirected to a null sink: trial division was 1.55 seconds at 5,000,000 and 9.39 seconds at 18,000,000; heap sieve was 0.93 seconds at 100,000,000. The stack sieve succeeded at 1,000,000 but overflowed the current default Windows stack at 1,500,000. These are local samples, not DTEK-V answers and not exact maxima.

### Common traps

- Do not use `int arr[...]`: it is normally four bytes per element and violates the intended memory calculation.
- Do not forget that a VLA with an invalid or negative bound is dangerous; the code returns before declaring the array for `n < 2`.
- Do not say that a stack overflow at a large local input proves the sieve algorithm is wrong. It reflects the required storage region and the host stack limit.

## Assignment 4 - Pointers

### 30-second answer

Reading the assembly gives `void work(void)` and `void copycodes(const char *src, int *dst, int *count)`. `work` passes the addresses of `text1`, `list1`, and `counter`, then repeats with `text2` and `list2`. `copycodes` reads a byte through `src`, stores it as an integer through `dst`, advances `src` by one byte and `dst` by one integer, and increments the integer through `count` until the NUL byte. The C source uses pointer dereference and pointer arithmetic, with no array-subscript access.

### How the signatures are derived

- `a0`, `a1`, and `a2` receive the first three arguments according to the RISC-V calling convention（调用约定）.
- `lb t0,0(a0)` reads one byte, so `a0` is a character/byte pointer.
- `sw t0,0(a1)` stores a 32-bit word and `a1` increases by 4, so `a1` is an `int *` destination for the 20-word lists.
- `lw`/`sw` through `a2` read and write the shared counter, so `a2` is an `int *`.
- Neither function places a result in `a0` before `jr ra`, so both return `void`.

The file-scope declarations `int list1[20]`, `int list2[20]`, and `int counter` correspond to `.space 80`, `.space 80`, and `.word 0`. The brackets are declarations required to reserve the storage; no expression such as `list1[i]` appears in the source.

### Pointer increment versus pointed-to value

`src++` changes the pointer address by `sizeof(char)`, normally 1 byte. `dst++` changes it by `sizeof(int)`, normally 4 bytes. `(*count)++` leaves the pointer `count` at the same address and increments the integer stored there. `*dst = *src` is dereferencing: it reads the source object and writes the destination object. These correspond to `lb`, `sw`, `lw`, and `sw` in the assembly.

### Endianness

After 35 is stored in `counter`, the bytes printed by `endian_proof` are `0x23,0x00,0x00,0x00`. The least significant byte is at the lowest address, so this machine is little-endian（小端序）. Little-endian is convenient for interpreting low-order bytes and is common in modern systems; big-endian can make the byte order look like the written hexadecimal order. Neither is universally better; code should follow the target's convention.

### Common traps

- `&counter` is the address of the integer; `*count` is the integer at that address.
- `p++` and `(*p)++` are different operations.
- `lb` is a signed byte load, while `lbu` would be an unsigned byte load. The supplied strings are ASCII, so their values are positive and the expected output is unchanged.
- RARS may print the PDF-specified warning that it ignores `.type`; this is expected.

## Assignment 5 - Memory Layout

### 30-second answer

`print_word` prints the address passed to it and then reads one 32-bit word at that address. `print_byte` reads one byte as an unsigned value. `gv` is an uninitialized global in `.bss`, `in` is an initialized global in `.data`, and `fun`/`main` are functions in `.text`. `m`, `p`, `cs`, `cp`, and `fun`'s `param` are locals in stack frames. `fun(m)` receives a copy: it changes the copy from 8 to 9 and writes 9 to `gv`, so `m` remains 8 while `gv` becomes 9. `cs[9]` has eight visible characters plus the NUL terminator, and `0x1234abcd` appears as `cd ab 34 12` on little-endian RV32.

### Official question: Why does `gv` change but `m` does not?

`fun(int param)` uses pass-by-value（值传递）. `param` is a separate copy of `m`; after `param++`, AF1 prints 9. The assignment `gv = param` changes the global, but there is no assignment back to `m`. Therefore AM18 is 8 and AM19 is 9.

### Official question: What is the size of `cp`?

`cp` is a character pointer, but pointer size is determined by the address width, not the pointed-to type. On the RISC-V/32 target, `cp` itself occupies 4 bytes.

### Official question: Why does the string need 9 bytes?

`"Bonjour!"` contains eight visible characters. A C string（C 字符串） ends with a NUL byte, so the array requires 8 plus 1, namely 9 bytes.

### Official question: Where are `fun` and `main`?

They are in the `.text` section. Their addresses point to instruction memory. A word read at those addresses is a 32-bit encoded RISC-V instruction. The exact addresses and instruction words depend on the actual cross-compiled binary and must be copied from the DTEK-V run, not guessed from another build.

### Additional address questions

- `in` and `gv` are global variables; `in` is `.data` and `gv` is `.bss`.
- `m` and `p` are local variables in `main` and therefore live in its stack frame. The stack is placed at higher addresses by `_stack_end` and grows downward, so their addresses are much larger than the global data addresses.
- At AM5, `&p` is the address of the pointer slot, `p` is `&m`, and `*p` is 7. At AM7, `&p` and `p` are unchanged, while `*p` is 8.
- At AM14-AM17, the four bytes after storing `0x1234abcd` are `cd`, `ab`, `34`, `12`, which proves little-endian order.

The full AM1-AM19/AF1 table, including each expression and expected region, is in `assignment5-analysis.md`. Its numeric address fields remain intentionally unfilled until the official build and board run.

### Common traps

- AM5 and AM7 print `&p`, not `p` and not `*p`; `print_word` then interprets the word stored at `&p`.
- `cp` points to `cs`, but `p` is explicitly cast to `int *` before the word store. This is the exercise's deliberate type/alignment experiment.
- Do not call `.bss` “the initialized data section”: `gv` starts zero-initialized because it has no explicit initializer, even though its runtime value changes later.
- `print_byte` displays the byte value as decimal; use hexadecimal in parentheses when explaining endianness.

## Assignment 6 - Surprise Assignment

This task is performed during the lab session and is not pre-implemented. A good method is:

1. Restate the changed requirement in one sentence.
2. Identify each variable's type, storage region, and ownership.
3. Trace the first and last loop iterations before editing.
4. Make the smallest change that implements the new rule.
5. Compile with warnings, run a boundary case, and explain one iteration to the teacher.

Likely variations include a changed loop bound, a small prime/sieve change, pointer versus pointed-to-value updates, a changed parameter or global side effect, or a changed load/store width.
