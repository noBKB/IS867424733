/* LAB AUTHOR DECLARATION: Replace this with the truthful person(s) who typed this code. */
/* Sieve of Eratosthenes using a heap array. */

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
    char *arr;
    size_t limit;
    size_t p;
    size_t next;
    size_t i;

    if(n < 2)
        return;

    limit = (size_t)n;
    arr = malloc((limit + 1U) * sizeof(*arr));
    if(arr == NULL){
        fprintf(stderr, "Unable to allocate sieve array.\n");
        return;
    }

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

    free(arr);
}

int main(int argc, char *argv[]){
    if(argc == 2)
        print_sieves(atoi(argv[1]));
    else
        printf("Please state an integer number.\n");
    return 0;
}
