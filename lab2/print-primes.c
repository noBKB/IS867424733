/*
 print-primes.c
 By Yufei Wang, Yimo Xia
 Last modified: 2026/9/16
 This file is in the public domain.
*/


#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6

// 全局计数器：记录当前这一行已经打印了多少个数字。
// 放在函数外面，这样多次调用 print_number 时可以共享并保留计数。
int counter = 0;

// 判断整数 n 是否为质数：是质数返回 1，不是质数返回 0。
int is_prime(int n){
    int i;

    // 小于 2 的整数不是质数。
    if(n < 2)
        return 0;

    // 从 2 开始寻找因数，只需要检查到 sqrt(n) 附近。
    // 使用 i <= n / i，避免直接计算 i*i 时可能发生整数溢出。
    for(i = 2; i <= n / i; i++){
        // 余数为 0 说明 n 能被 i 整除，因此 n 不是质数。
        if(n % i == 0)
            return 0;
    }

    // 没有找到任何因数，所以 n 是质数。
    return 1;
}

// 打印一个整数，并利用全局 counter 控制每行最多打印 COLUMNS 个数字。
void print_number(int n){
    printf("%10d ", n);   // 以至少 10 个字符宽度、右对齐的格式打印 n。
    counter++;             // 成功打印一个数字后，当前行计数加 1。
    if(counter == COLUMNS){
        printf("\n");     // 一行达到 COLUMNS 个数字后换行。
        counter = 0;       // 新的一行从 0 开始重新计数。
    }
}

// 输出从 2 到 n（包含 n）之间的所有质数。
void print_primes(int n){
    // 模板原说明：输出所有小于 n 的质数，
    // 使用以下格式。注意：
    // 每行的列数由宏定义
    // COLUMNS 指定。
    // 2026 年 PDF 要求包含上界 n；若 n 是质数，也要输出。
    int i;

    // 依次检查 2 到 n 中的每一个候选整数。
    for(i = 2; i <= n; i++){
        // 如果 i 是质数，就交给 print_number 打印。
        if(is_prime(i))
            print_number(i);
        // 处理完 n 后直接退出，避免 n == INT_MAX 时下一次 i++ 发生整数溢出。
        if(i == n)  // 处理完 n 就退出，避免 n 为 INT_MAX 时 i++ 溢出。
            break;
    }
}

// argc 保存程序参数的个数；
// argv 是字符指针数组，其中每个指针
// 指向一个以零字符结尾的字符串。
int main(int argc, char *argv[]){
    // 正常调用时需要恰好一个用户输入参数，例如：./print-primes 20。
    if(argc == 2)
    {
        // argv[1] 是字符串；atoi 将它转换成 int，再传给 print_primes。
        print_primes(atoi(argv[1]));
    }
  else
    // 参数数量不正确时提示用户输入一个整数。
    printf("Please state an integer number.\n");
  return 0;
}
