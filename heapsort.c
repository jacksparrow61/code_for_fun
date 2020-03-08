#include <gmp.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#define nums_in_list 10000000

mpz_t array_of_numbers[nums_in_list];

void heapSort(mpz_t arr[], int n);
void heapify(mpz_t arr[], int n, int i);
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

typedef int (*callback_compare)(mpz_t,mpz_t);
typedef void (*callback_swap)(mpz_t,mpz_t);
callback_compare call;
callback_swap call1;


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
  rndBit = 3;
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

void heapSort(mpz_t arr[], int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i=n-1; i>=0; i--)
    {
        // Move current root to end
        call1(arr[0], arr[i]);

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

// To heapify a subtree rooted with node i which is
// an index in arr[]. n is size of heap
void heapify(mpz_t arr[], int n, int i)
{
    int largest = i; // Initialize largest as root
    int l = 2*i + 1; // left = 2*i + 1
    int r = 2*i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && (call(arr[l],arr[largest])==1))
        largest = l;

    // If right child is larger than largest so far
    if (r < n && (call(arr[r],arr[largest])==1))
        largest = r;

    // If largest is not root
    if (largest != i)
    {
        call1(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

void main()
{
  call = &compare_numbers;
  call1 = &swap_numbers;
  create_random_array();
  heapSort(array_of_numbers,nums_in_list);
  for(int i=0; i<nums_in_list; i++)
  gmp_printf("The value after sort at %d = %Zd\n",i,array_of_numbers[i]);

}
