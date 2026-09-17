/*
 print-primes.c
 By Yufei Wang, Yimo Xia
 Last modified: 2026/9/16
 This file is in the public domain.
*/
/* sieves-heap.c: 由提供的 print-primes.c 模板改写。 */

#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6

// 全局计数器：记录当前行已经打印了多少个数字。
int counter = 0;

// 打印一个整数，并在每打印 COLUMNS 个数字后换行。
void print_number(int n){
    printf("%10d ", n);
    counter++;
    if(counter == COLUMNS){
        printf("\n");
        counter = 0;
    }
}

// 使用 Sieve of Eratosthenes（埃拉托斯特尼筛法）输出 2 到 n 之间的所有质数。
// 与 sieves.c 的主要区别是：标记数组 arr 从 heap（堆）动态申请。
void print_sieves(int n){
    // n < 2 时没有质数可输出，直接结束函数。
    if(n < 2)
        return;

    // limit 保存上界 n；p 表示当前用于筛选倍数的数；i 用作循环下标。
    size_t limit = (size_t)n;
    size_t p;
    size_t i;

    // malloc 从 heap 申请 limit + 1 个字节，arr 保存这块内存的起始地址。
    // char 占 1 byte，因此这里不需要再乘元素大小。
    char *arr = malloc(limit + 1);

    // malloc 失败时会返回 NULL；此时不能继续访问 arr。
    if(arr == NULL){
        fprintf(stderr, "Unable to allocate sieve array.\n");
        return;
    }

    // 1. 数组下标代表对应的整数；0 表示目前“尚未被标记为合数”。
    for(i = 2; i <= limit; i++)
        arr[i] = 0;

    // 2. 从最小的质数 2 开始。
    p = 2;
    while(p <= limit){
        // 3. 从 2p 开始依次标记 p 的倍数：2p、3p、4p……
        // p 本身不标记。
        for(i = 2 * p; i <= limit; i += p)
            arr[i] = 1;

        // 4. 寻找下一个未标记的数；超过 n 时停止。
        p++;
        while(p <= limit && arr[p] != 0)
            p++;
    }

    // 5. 筛选结束后，仍然未被标记的数就是质数，逐个打印出来。
    for(i = 2; i <= limit; i++){
        if(arr[i] == 0)
            print_number((int)i);
    }

    // heap 内存不会在函数返回时自动释放，因此使用完后必须归还。
    free(arr);
}

// argc 保存程序参数的个数；
// argv 是字符指针数组，其中每个指针
// 指向一个以零字符结尾的字符串。
int main(int argc, char *argv[]){
    if(argc == 2)
    {
        // argv[1] 是字符串；atoi 将它转换为 int 后传给 print_sieves。
        print_sieves(atoi(argv[1]));
    }
  else
    printf("Please state an integer number.\n");
  return 0;
}
