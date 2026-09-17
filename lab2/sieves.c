/*
 print-primes.c
 By Yufei Wang, Yimo Xia
 Last modified: 2026/9/16
 This file is in the public domain.
*/
/* sieves.c: adapted from the supplied print-primes.c template. */

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
    char arr[limit + 1];

    // 1. Each index represents a number; 0 means unmarked.
    for(i = 2; i <= limit; i++)
        arr[i] = 0;

    // 2. Start with the smallest prime.
    p = 2;
    while(p <= limit){
        // 3. Mark 2p, 3p, ...; do not mark p itself.
        for(i = 2 * p; i <= limit; i += p)
            arr[i] = 1;

        // 4. Move to the next unmarked number; stop if past n.
        p++;
        while(p <= limit && arr[p] != 0)
            p++;
    }

    // 5. Print the unmarked numbers.
    for(i = 2; i <= limit; i++){
        if(arr[i] == 0)
            print_number((int)i);
    }
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
    if(argc == 2)
    {
        print_sieves(atoi(argv[1]));
    }
  else
    printf("Please state an integer number.\n");
  return 0;
}
