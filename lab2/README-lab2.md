# KTH IS1200/IS1500 2026 Lab 2

2026-09-17 修订。以用户上传的 2026 Lab PDF 和原始模板为依据；代码采用课堂范围内的直接实现。根目录的原始 Lab 2 模板与本目录的已实现版本是不同文件，请进入本目录操作。

## 文件入口

- 五个 C 源文件：A1 prime.c；A2 print-primes.c；A3 sieves.c、sieves-heap.c；A4 pointers.c。
- pointers.S：原样保留的 A4 汇编参考。
- assignment5/：原始 main.c、Makefile、启动文件、链接脚本、库和许可说明。
- oral-prep.md：中文口试准备，含 30 秒答案、逐步讲解和练习。
- assignment5-analysis.md：A5 全部书面答案、20 项实际 RV32 模拟输出、模拟地址逐项解读及独立的实机填写表。模拟已运行，DTEK-V 实机部分仍待完成。
- test-report.md、performance.md：当前版本验证和计时方法。
- lab2-final.zip：仅五个 C 源文件。Canvas 的确切提交清单须在课程页面核对，见 submission-manifest.md。

## A1–A4 编译运行

要求有支持 C11 变长数组的 GCC 或 Clang。这里的 gcc 命令在本次 Windows 环境实际是 LLVM-MinGW 的 Clang 驱动；不冒称为 GNU GCC。MSVC 不支持本题使用的 C 变长数组。

在 Windows PowerShell 中，进入仓库的 lab2 目录后运行：

```powershell
gcc -std=c11 -Wall -Wextra -pedantic prime.c -o prime.exe
gcc -std=c11 -Wall -Wextra -pedantic print-primes.c -o print-primes.exe
gcc -std=c11 -Wall -Wextra -pedantic sieves.c -o sieves.exe
gcc -std=c11 -Wall -Wextra -pedantic sieves-heap.c -o sieves-heap.exe
gcc -std=c11 -Wall -Wextra -pedantic pointers.c -o pointers.exe
.\prime.exe
.\print-primes.exe 105
.\sieves.exe 105
.\sieves-heap.exe 105
.\pointers.exe
```

在 WSL 或 KTH Linux 实验机中，进入同一源码目录：

```sh
gcc -std=c11 -Wall -Wextra -pedantic prime.c -o prime
gcc -std=c11 -Wall -Wextra -pedantic print-primes.c -o print-primes
gcc -std=c11 -Wall -Wextra -pedantic sieves.c -o sieves
gcc -std=c11 -Wall -Wextra -pedantic sieves-heap.c -o sieves-heap
gcc -std=c11 -Wall -Wextra -pedantic pointers.c -o pointers
./prime
./print-primes 105
./sieves 105
./sieves-heap 105
./pointers
```

prime 应打印 1、1、0。三个质数列表应一致；pointers 应得到 Count = 35 和 Endian experiment: 0x23,0x00,0x00,0x00（在本次小端机器上）。

stack sieve 为教学要求使用局部数组；大输入受栈容量限制。不要把栈溢出的失败运行记为成功计时。源文件保留模板的 atoi 参数解析，请输入 int 范围内的十进制整数。

## A5 官方流程

在配置好 DTEK-V 交叉工具链并连接板子的 KTH 环境执行：

```sh
cd assignment5
make
dtekv-run main.bin
```

Makefile 使用 Unix find/rm；仅有 Windows 原生 make 不等于满足环境要求。WSL 中仍需另行具备课程工具链和板子访问条件。本次未连接 DTEK-V，也未成功构建 A5，因此真实地址、指令字和板上输出仍须填写。按 assignment5-analysis.md 的实机记录表逐项抄录。Makefile 的 clean 会删除该目录 *.txt，个人笔记请用 .md 或放到上级目录。

## 作者声明与提交

每个 C 文件开头保留 LAB AUTHOR DECLARATION 占位符。本版本代码由 AI 生成及修订，请按实际情况披露协助，不得声称为自己独立输入。课程要求两位伙伴各完成前四题中的两题输入工作，或各自独立写全部题；双方均应能解释全部实现。模板中的老师署名表示原始模板作者。

Canvas 提交清单不在 PDF 内，提交前核对 Lab 2 Files + Upload code。GitHub 上传不等同 Canvas 提交。A6 为现场随机题，当前只提供知识准备。
