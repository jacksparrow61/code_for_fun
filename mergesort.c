#include <gmp.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#define nums_in_list 10000

mpz_t array_of_numbers[nums_in_list];

void merge(mpz_t arr[], int l, int m, int r);
void mergeSort(mpz_t arr[], int l, int r);
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

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(mpz_t arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(mpz_t arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    mpz_t L[n1];
    mpz_t R[n2];
    for (int i=0;i<n1;i++)
    mpz_init(L[i]);

    for (int i=0;i<n2;i++)
    mpz_init(R[i]);

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        mpz_set(L[i],arr[l + i]);
    for (j = 0; j < n2; j++)
        mpz_set(R[j],arr[m + 1+ j]);

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (call(L[i],R[j])<=0)
        {
            mpz_set(arr[k],L[i]);
            i++;
        }
        else
        {
            mpz_set(arr[k],R[j]);
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        mpz_set(arr[k],L[i]);
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        mpz_set(arr[k],R[j]);
        j++;
        k++;
    }
    for (int i=0;i<n1;i++)
    mpz_clear(L[i]);

    for (int i=0;i<n2;i++)
    mpz_clear(R[i]);
}

void main()
{
  call = &compare_numbers;
  call1 = &swap_numbers;
  create_random_array();
  mergeSort(array_of_numbers, 0, nums_in_list - 1);
  for(int i=0; i<nums_in_list; i++)
  gmp_printf("The value after sort at %d = %Zd\n",i,array_of_numbers[i]);

}
