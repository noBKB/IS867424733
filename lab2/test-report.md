# Lab 2 验证记录

验证日期：2026-09-17。针对本次简化源码。此前报告保存在本地旧工作目录，旧压缩包哈希和旧耗时不代表当前版本。

## 编译

Windows / AMD Ryzen 7 9800X3D；gcc --version 实际显示 LLVM-MinGW Clang 22.1.8。

每个源文件分别执行：

```text
gcc -std=c11 -Wall -Wextra -pedantic prime.c -o <build>/prime.exe
gcc -std=c11 -Wall -Wextra -pedantic print-primes.c -o <build>/print-primes.exe
gcc -std=c11 -Wall -Wextra -pedantic sieves.c -o <build>/sieves.exe
gcc -std=c11 -Wall -Wextra -pedantic sieves-heap.c -o <build>/sieves-heap.exe
gcc -std=c11 -Wall -Wextra -pedantic pointers.c -o <build>/pointers.exe
```

五次编译均 exit 0、无诊断。生成文件位于本地 lab2-work/revision-20260917/build，不放进候选 zip 或 GitHub。

## 行为测试

- A1 原始 main 输出 1、1、0。额外 C 断言检查 -1、0、1、2、3、4、9、25、97、INT_MAX；在本机 32 位 int 下全部通过。
- A2/两种 A3：输入 -3、0..200、1000、10000，共 204 组。每个程序的输出分别与独立 Python 试除法生成的预期输出一致，核对整数、字段宽度、空格和换行（仅统一 Windows CRLF 与 LF）。
- n=105 的结果包含 27 个质数、4 个换行，尾行 97、101、103，符合 PDF 的六列规则。
- 多次调用 print_primes(3) 后 counter 分别为 2、4、0；随后调用 print_primes(1)，counter 仍为 0。确认调用之间状态延续。
- A2 新加 i==n 时退出的条件。INT_MAX 的完整打印没有执行；终止前不再执行 i++ 的安全性由代码检查确认，不声称跑过二十多亿个候选数。
- A4 对完整两段 ASCII 输出、Count=35、Endian experiment: 0x23,0x00,0x00,0x00 做了逐字节核对。
- A4 额外使用含 65、-128、-1、0 的 signed char 源串，验证整数写入、原 count 从 10 变 13、NUL 不被复制；再用 -funsigned-char 编译此测试，仍通过。
- heap 源码另用 -fsanitize=address -g 编译，n=10000 运行成功，无 AddressSanitizer 报告。free 的匹配路径经代码检查；不把单次 ASan 运行表述为所有路径均无泄漏的证明。

## 约束检查

筛法标记从 2*p 开始，再找最小未标记后继，未改为 p*p 或平方根终止。局部数组 char arr[limit+1] 为 n+1 字节；n<2 时先退出。heap 版 malloc 分配同样大小，失败时返回，成功路径最后 free。

A4 方括号只出现在两个数组声明，没有数组下标访问。源串使用 const signed char*，明确匹配 lb 的符号扩展；int* 对应 RV32 的 lw/sw 和 4 字节步长。

保留老师模板署名与说明；A2 原注释“less than n”后注明 2026 PDF 要求包含 n。所有 C 源码都有作者占位符和 AI 协助说明，没有填学生姓名。

## 性能

详细命令、31 个实测样本和两种时间预算结果在 performance.md。本次记录用当前源码重新测试；成功、栈溢出、预算超时明确区分。

## A5 与 A6

A5 的 main.c 和七个 time4riscv 支持文件已放到 assignment5/，复制时保持原始内容。源码、Makefile、链接脚本及 20 项观察点已分析，数值表按源码推导；所有实际地址和指令字仍待实机填写。

本次 PATH 中未找到 riscv32-unknown-elf-gcc 或 dtekv-run；没有连接板子，不声称已构建或运行 A5。RARS 在旧版审计中仅验证过临时修改退出循环的副本，本次没有重新运行 RARS，也没有修改原始 pointers.S。

A6 只准备知识和练习，没有提前实现未知随机题。

## 交付核对

assignment5/ 的八个文件及 pointers.S 与原始材料逐字节一致。重新生成的 lab2-final.zip 通过完整性检查，恰好包含五个 C 文件；解压内容与本目录源文件逐字节一致。

ZIP SHA-256：0336679B9E53D305687EA77DFBF685125A455D3683528621E9FF470E140CF1D3。

## 本地验证文件

本地 lab2-work/revision-20260917/ 中保留 verify.py、prime-test.c、pointer-test.c、counter-test.c、performance.json 和 build/。测试脚本里的绝对源路径指向本机 GitHub 仓库 lab2/；换机器运行须相应调整。这些不是 Canvas 候选提交内容。
