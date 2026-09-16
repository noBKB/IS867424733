/* LAB AUTHOR DECLARATION: Replace this with the truthful person(s) who typed this code. */
/* Sieve of Eratosthenes using a local stack array. */

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

    {
        size_t limit = (size_t)n;
        char arr[limit + 1U];
        size_t p;
        size_t next;
        size_t i;

        for(i = 2U; i <= limit; i++)
            arr[i] = 0;

        p = 2U;
        while(p != 0U){
            for(i = p + p; i <= limit; i += p)
                arr[i] = 1;

            next = 0U;
            for(i = p + 1U; i <= limit; i++){
                if(arr[i] == 0){
                    next = i;
                    break;
                }
            }
            p = next;
        }

        for(i = 2U; i <= limit; i++){
            if(arr[i] == 0)
                print_number((int)i);
        }
    }
}

int main(int argc, char *argv[]){
    if(argc == 2)
        print_sieves(atoi(argv[1]));
    else
        printf("Please state an integer number.\n");
    return 0;
}
