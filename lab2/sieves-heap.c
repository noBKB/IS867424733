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

int counter = 0;

void print_number(int n){
    printf("%10d ", n);
    counter++;
    if(counter == COLUMNS){
        printf("\n");
        counter = 0;
    }
}

void print_sieves(int n){
    if(n < 2)
        return;

    size_t limit = (size_t)n;
    size_t p;
    size_t i;
    char *arr = malloc(limit + 1);
    if(arr == NULL){
        fprintf(stderr, "Unable to allocate sieve array.\n");
        return;
    }

    // 1. 数组下标代表对应的整数；0 表示未标记。
    for(i = 2; i <= limit; i++)
        arr[i] = 0;

    // 2. 从最小的质数 2 开始。
    p = 2;
    while(p <= limit){
        // 3. 标记 2p、3p 等倍数，不标记 p 本身。
        for(i = 2 * p; i <= limit; i += p)
            arr[i] = 1;

        // 4. 寻找下一个未标记的数；超过 n 时停止。
        p++;
        while(p <= limit && arr[p] != 0)
            p++;
    }

    // 5. 输出所有未标记的数。
    for(i = 2; i <= limit; i++){
        if(arr[i] == 0)
            print_number((int)i);
    }

    free(arr);
}

// argc 保存程序参数的个数；
// argv 是字符指针数组，其中每个指针
// 指向一个以零字符结尾的字符串。
int main(int argc, char *argv[]){
    if(argc == 2)
    {
        print_sieves(atoi(argv[1]));
    }
  else
    printf("Please state an integer number.\n");
  return 0;
}
