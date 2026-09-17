/*
 print-primes.c
 By Yufei Wang, Yimo Xia
 Last modified: 2026/9/16
 This file is in the public domain.
*/
/* sieves.c: 由提供的 print-primes.c 模板改写。 */

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
void print_sieves(int n){
    // n < 2 时没有质数可输出，直接结束函数。
    if(n < 2)
        return;

    // limit 保存上界 n；p 表示当前用于筛选倍数的数；i 用作循环下标。
    size_t limit = (size_t)n;
    size_t p;
    size_t i;

    // 在 stack（栈）上创建标记数组。
    // 使用 char 是因为每个位置只需要保存 0 或 1；limit + 1 允许直接访问 arr[limit]。
    char arr[limit + 1];

    // 1. 数组下标代表对应的整数；0 表示目前“尚未被标记为合数”。
    for(i = 2; i <= limit; i++)
        arr[i] = 0;

    // 2. 从最小的质数 2 开始。
    p = 2;
    while(p <= limit){
        // 3. 从 2p 开始依次标记 p 的倍数：2p、3p、4p……
        // p 本身不标记，因为 p 是当前用于筛选的质数。
        for(i = 2 * p; i <= limit; i += p)
            arr[i] = 1;

        // 4. p 先向后移动一个位置，然后跳过所有已经被标记的合数。
        // 最终停在下一个未标记的数；如果超过 limit，循环结束。
        p++;
        while(p <= limit && arr[p] != 0)
            p++;
    }

    // 5. 筛选结束后，仍然没有被标记的数就是质数，逐个打印出来。
    for(i = 2; i <= limit; i++){
        if(arr[i] == 0)
            print_number((int)i);
    }
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
