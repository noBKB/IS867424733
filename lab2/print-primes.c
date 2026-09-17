/* LAB AUTHOR DECLARATION: Replace this with the truthful person(s) who typed this code. */
/* Implementation generated/revised with OpenAI Codex; student authorship is not asserted. */
/*
 print-primes.c
 By David Broman.
 Last modified: 2015-09-15
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
    // Should print out all prime numbers less than 'n'
    // with the following formatting. Note that
    // the number of columns is stated in the define
    // COLUMNS
    // The 2026 PDF overrides "less than": include n when it is prime.
    int i;

    for(i = 2; i <= n; i++){
        if(is_prime(i))
            print_number(i);
        if(i == n)  // Stop before i++ could overflow at INT_MAX.
            break;
    }
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
    if(argc == 2)
    {
        print_primes(atoi(argv[1]));
    }
  else
    printf("Please state an integer number.\n");
  return 0;
}
