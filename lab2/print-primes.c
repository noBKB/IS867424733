/*
 print-primes.c
 By Yufei Wang, Yimo Xia
 Last modified: 2026/9/16
 This file is in the public domain.
*/


#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6

int counter = 0;

int is_prime(int n){
    int i;

    if(n < 2)
        return 0;

    for(i = 2; i <= n / i; i++){
        if(n % i == 0)
            return 0;
    }

    return 1;
}

void print_number(int n){
    printf("%10d ", n);
    counter++;
    if(counter == COLUMNS){
        printf("\n");
        counter = 0;
    }
}

void print_primes(int n){
    // 模板原说明：输出所有小于 n 的质数，
    // 使用以下格式。注意：
    // 每行的列数由宏定义
    // COLUMNS 指定。
    // 2026 年 PDF 要求包含上界 n；若 n 是质数，也要输出。
    int i;

    for(i = 2; i <= n; i++){
        if(is_prime(i))
            print_number(i);
        if(i == n)  // 处理完 n 就退出，避免 n 为 INT_MAX 时 i++ 溢出。
            break;
    }
}

// argc 保存程序参数的个数；
// argv 是字符指针数组，其中每个指针
// 指向一个以零字符结尾的字符串。
int main(int argc, char *argv[]){
    if(argc == 2)
    {
        print_primes(atoi(argv[1]));
    }
  else
    printf("Please state an integer number.\n");
  return 0;
}
