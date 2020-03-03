#include <gmp.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#define nums_in_list 5

mpz_t array_of_numbers[nums_in_list];

void create_random_array();
void quick_sort(mpz_t arr[],int low,int high);
int partition(mpz_t arr[],int low,int high,int (*)(mpz_t,mpz_t),void (*)(mpz_t,mpz_t));

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
callback_compare call;
callback_swap call1;


int main ()
{

call = &compare_numbers;
call1 = &swap_numbers;
create_random_array();
quick_sort(array_of_numbers,0,nums_in_list-1);
for(int i=0; i<nums_in_list; i++)
  gmp_printf("The value after sort at %d = %Zd\n",i,array_of_numbers[i]);

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
  gmp_printf("The value at 0 = %Zd\n",array_of_numbers[2]);
  gmp_printf("The value at 1 = %Zd\n",array_of_numbers[3]);
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
  rndBit = 125;
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
 at 4
  /* Clean up resources occupied by compensated */
  gmp_randclear(gmpRandState);

  /* Clean up resources occupied by our mpz_t variables */
  mpz_clear(randNum);

  return;

}


void quick_sort(mpz_t arr[],int low,int high)
{
 if (low < high)
 {
   int p = partition(arr,low,high,call,call1);

   quick_sort(arr,low,p-1);
   quick_sort(arr,p+1,high);
 }
}

int partition(mpz_t arr[],int low,int high,callback_compare call,callback_swap call1)
{
  mpz_t pivot;
  mpz_init(pivot);
  mpz_set(pivot,arr[high]);

  int i = (low - 1);

  for (int j = low; j <= high - 1; j++)
  {
     // If current element is smaller than the pivot
     if (call(arr[j],pivot)==-1)
     {
         i++; // increment index of smaller element
         call1(arr[i], arr[j]);  //swap_numbers
     }
   }
   call1(arr[i + 1], arr[high]);
   mpz_clear(pivot);
   return (i + 1);
}
