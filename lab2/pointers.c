/*
 pointers.c
 By Yufei Wang, Yimo Xia
 Last modified: 2026/9/16
 This file is in the public domain.
*/


#include <stdio.h>
#include <stdlib.h>

char* text1 = "This is a string.";
char* text2 = "Yet another thing.";
int list1[20];
int list2[20];
int counter = 0;

void copycodes(const signed char* src, int* dst, int* count){
  while(*src != '\0'){
    *dst = *src;
    src++;
    dst++;
    (*count)++;
  }
}

void work(void){
  // signed char matches the signed byte load (lb) in pointers.S.
  copycodes((const signed char*)text1, list1, &counter);
  copycodes((const signed char*)text2, list2, &counter);
}

void printlist(const int* lst){
  printf("ASCII codes and corresponding characters.\n");
  while(*lst != 0){
    printf("0x%03X '%c' ", *lst, (char)*lst);
    lst++;
  }
  printf("\n");
}

void endian_proof(const char* c){
  printf("\nEndian experiment: 0x%02x,0x%02x,0x%02x,0x%02x\n",
         (int)*c,(int)*(c+1), (int)*(c+2), (int)*(c+3));
}

int main(void){
    work();
    printf("\nlist1: ");
    printlist(list1);
    printf("\nlist2: ");
    printlist(list2);
    printf("\nCount = %d\n", counter);

    endian_proof((char*) &counter);
    return 0;
}
