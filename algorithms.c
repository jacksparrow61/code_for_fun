#include <gmp.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#define nums_in_list 4

mpz_t array_of_numbers[nums_in_list];

void create_random_array();

int compare_numbers(mpz_t a ,mpz_t b);
int compare_numbers(mpz_t a ,mpz_t b)
{
return mpz_cmp(a,b);
}

void swap_numbers(mpz_t a, mpz_t b);
void swap_numbers(mpz_t a, mpz_t b)
{
mpz_swap(a,b);
return;
}

void test_call_back(int (*)(mpz_t,mpz_t), void (*)(mpz_t,mpz_t));
typedef int (*callback_compare)(mpz_t,mpz_t);
typedef void (*callback_swap)(mpz_t,mpz_t);


int main ()
{

callback_compare call;
callback_swap call1;
create_random_array();
call = compare_numbers;
call1= swap_numbers;
test_call_back(call,call1);

}

void test_call_back(callback_compare call, callback_swap call1)
{
  mpz_t a,b;
  mpz_init(a);
  mpz_init(b);
  mpz_set(a,array_of_numbers[0]);
  mpz_set(b,array_of_numbers[1]);
  int i = call(array_of_numbers[0],array_of_numbers[1]);
  printf("The value of i is %d\n",i);
  gmp_printf("The value at 0 = %Zd\n",array_of_numbers[0]);
  gmp_printf("The value at 1 = %Zd\n",array_of_numbers[1]);
  call1(array_of_numbers[0],array_of_numbers[1]);
  gmp_printf("The value at 0 = %Zd\n",array_of_numbers[0]);
  gmp_printf("The value at 1 = %Zd\n",array_of_numbers[1]);
  return;
}


void create_random_array()
{

  for(int i =0;i<nums_in_list;i++)
  {
    mpz_init(array_of_numbers[i]);
  }
  int             i;            /* Loop variable */
  mpz_t           randNum;      /* Hold our random numbers */
  int             rndBit;       /* Bound for mpz_urandomb */
  // mpz_t           rndBnd;       /* Bound for mpz_urandomm */
  gmp_randstate_t gmpRandState; /* Random generator state object */

  /* Initialize randNum before we use it. */
  mpz_init(randNum);
  time_t current_time = time(NULL);
  /* Initialize Bounds */
  rndBit = 128;
  // mpz_init_set_str(rndBnd, "1000", 10);

  /* Initialize the random state with default algorithm... */
  gmp_randinit_default(gmpRandState);

  /* Seed the state with an unsigned long int before we begin.. */
  gmp_randseed_ui(gmpRandState, current_time);
  for(i=0; i<nums_in_list; i++) {
    /* mpz_get_ui() can convert randNum to unsigned long int... */
    mpz_urandomb(randNum, gmpRandState, rndBit);
    mpz_set(array_of_numbers[i],randNum);
    gmp_printf("The value at %d = %Zd\n",i,array_of_numbers[i]);
  } /* end for */

  /* Clean up resources occupied by compensated */
  gmp_randclear(gmpRandState);

  /* Clean up resources occupied by our mpz_t variables */
  mpz_clear(randNum);

  return;

}


quick_sort(mpz_t * arr, s)
      
