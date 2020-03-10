#include <time.h>

#define THREAD_MAX 4

clock_t t1, t2;

struct tsk {
    int tsk_no;
    int tsk_low;
    int tsk_high;
    mpz_t * arr;
};


int compare_numbers(mpz_t a ,mpz_t b);
void swap_numbers(mpz_t a, mpz_t b);
typedef int (*callback_compare)(mpz_t,mpz_t);
typedef void (*callback_swap)(mpz_t,mpz_t);
callback_compare call;
callback_swap call1;
