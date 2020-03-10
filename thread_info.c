#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include "thread_info.h"



int compare_numbers(mpz_t a ,mpz_t b)
{
return mpz_cmp(a,b);
}


void swap_numbers(mpz_t a, mpz_t b)
{
mpz_swap(a,b);
return;
}
