/*
 prime.c
 By Yufei Wang, Yimo Xia
 Last modified: 2026/9/16
 This file is in the public domain.
*/


#include <stdio.h>

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
int main(void){
  printf("%d\n", is_prime(11));  // 11 是质数，应输出 1。
  printf("%d\n", is_prime(383)); // 383 是质数，应输出 1。
  printf("%d\n", is_prime(987)); // 987 不是质数，应输出 0。
  return 0;
}
