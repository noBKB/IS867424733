/*
 prime.c
 By Yufei Wang, Yimo Xia
 Last modified: 2026/9/16
 This file is in the public domain.
*/


#include <stdio.h>

// 判断整数 n 是否为质数：是质数返回 1，不是质数返回 0。
int is_prime(int n){
    int i;

    // 小于 2 的整数不是质数，直接返回 0。
    if(n < 2)
        return 0;

    // 从 2 开始寻找因数。
    // i <= n / i 等价于检查到 sqrt(n) 附近，同时避免直接计算 i*i 可能造成的整数溢出。
    for(i = 2; i <= n / i; i++){
        // 如果 n 能被 i 整除，说明找到了除 1 和自身之外的因数，因此不是质数。
        if(n % i == 0)
            return 0;
    }

    // 如果循环结束都没有找到因数，说明 n 是质数。
    return 1;
}
int main(void){
  // 用几个已知例子测试 is_prime 的返回值。
  printf("%d\n", is_prime(11));  // 11 是质数，应输出 1。
  printf("%d\n", is_prime(383)); // 383 是质数，应输出 1。
  printf("%d\n", is_prime(987)); // 987 不是质数，应输出 0。
  return 0;
}
