/*
 pointers.c
 By Yufei Wang, Yimo Xia
 Last modified: 2026/9/16
 This file is in the public domain.
*/


#include <stdio.h>
#include <stdlib.h>

// 1. 全局字符串：两个字符串分别有 17 和 18 个字符，因此最终 Count = 35。
char* text1 = "This is a string.";
char* text2 = "Yet another thing.";

// 2. 全局数组与计数器：对应 pointers.S 中的 list1、list2 和 counter。
// 每个数组有 20 个 int；如果 int 为 4 字节，则共占 80 字节。
int list1[20];
int list2[20];
int counter = 0;

// 3. copycodes：把源字符串中的字符编码逐个复制到 int 数组中，并累计复制数量。
// 本题要求使用纯指针操作，不使用 a[i] 形式的数组下标。
void copycodes(const signed char* src, int* dst, int* count){
  // *src 是当前字符；遇到 '\0'（字符串结束符）时停止。
  // 对应汇编中的 lb t0, 0(a0) 以及判断是否为 0。
  while(*src != '\0'){
    *dst = *src;          // 把 src 当前指向的字符值写入 dst 当前指向的 int；对应 sw。
    src++;                // src 是 char*，移动到下一个字符，通常前进 1 字节。
    dst++;                // dst 是 int*，移动到下一个 int，通常前进 4 字节。
    (*count)++;           // 修改 count 指向的整数值；对应 lw -> +1 -> sw。
  }
}

// 4. work：负责调用两次 copycodes。
// 数组名作为参数时表示数组首地址；&counter 取得 counter 的地址。
void work(void){
  // signed char 对应 pointers.S 中带符号的字节加载指令 lb。
  copycodes((const signed char*)text1, list1, &counter);
  copycodes((const signed char*)text2, list2, &counter);
}

// 5. printlist：从数组首地址开始逐个读取 int，直到遇到值 0。
// 同时以十六进制 ASCII 编码和对应字符两种形式打印。
void printlist(const int* lst){
  printf("ASCII codes and corresponding characters.\n");
  while(*lst != 0){
    printf("0x%03X '%c' ", *lst, (char)*lst);
    lst++;                // lst 是 int*，移动到下一个 int。
  }
  printf("\n");
}

// 6. 大小端检验：counter 最终为 35，即十六进制 0x00000023。
// 把 &counter 转成 char* 后，可以按 1 字节一步读取这个 int 的四个字节。
// 在 Little-Endian（小端序）机器上应看到 0x23,0x00,0x00,0x00：低地址存最低有效字节。
void endian_proof(const char* c){
  printf("\nEndian experiment: 0x%02x,0x%02x,0x%02x,0x%02x\n",
         (int)*c,(int)*(c+1), (int)*(c+2), (int)*(c+3));
}

int main(void){
    work();               // 执行两次字符串复制，并更新全局 counter。
    printf("\nlist1: ");
    printlist(list1);     // 打印 text1 对应的 ASCII 编码和字符。
    printf("\nlist2: ");
    printlist(list2);     // 打印 text2 对应的 ASCII 编码和字符。
    printf("\nCount = %d\n", counter);

    endian_proof((char*) &counter); // 取得 counter 地址，并按 char* 逐字节观察其内存表示。
    return 0;
}
