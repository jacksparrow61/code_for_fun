#include <gmp.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define nums_in_list 100000
// int THREAD_MAX; //Number of threads that would be created

// thread control parameters
struct tsk {
    int tsk_no;
    int tsk_low;
    int tsk_high;
};

mpz_t * array_of_numbers;

void * mergesort_thread(void *arg);
void merge(long int l, long int m, long int r);
void mergeSort(int l, int r);
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

  // for(int i =0;i<nums_in_list;i++)
  // {
  //   mpz_init(array_of_numbers[i]);
  // }
  array_of_numbers = (mpz_t *) malloc(nums_in_list * sizeof(mpz_t));
  if (NULL == array_of_numbers) {
      printf("ERROR: Out of memory\n");
      return;
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
  rndBit = 12;
  // mpz_init_set_str(rndBnd, "1000", 10);

  /* Initialize the random state with default algorithm... */
  gmp_randinit_default(gmpRandState);

  /* Seed the state with an unsigned long int before we begin.. */
  gmp_randseed_ui(gmpRandState, current_time);
  for(i=0; i<nums_in_list; i++) {
    /* mpz_get_ui() can convert randNum to unsigned long int... */
    mpz_urandomb(randNum, gmpRandState, rndBit);
    mpz_set(*(array_of_numbers+i),randNum);
    gmp_printf("The value at %d = %Zd\n",i,*(array_of_numbers+i));
  } /* end for */
  /* Clean up resources occupied by compensated */
  gmp_randclear(gmpRandState);

  /* Clean up resources occupied by our mpz_t variables */
  mpz_clear(randNum);

  return;
}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;

        // Sort first and second halves
        mergeSort(l, m);
        mergeSort(m+1, r);

        merge(l, m, r);
    }
}

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(long int l, long int m, long int r)
{
    long int i, j, k;
    long int n1 = m - l + 1;
    long int n2 =  r - m;

    /* create temp arrays */
    mpz_t L[n1];
    mpz_t R[n2];
    for (int i=0;i<n1;i++)
    mpz_init(L[i]);

    for (int i=0;i<n2;i++)
    mpz_init(R[i]);

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        mpz_set(L[i],*(array_of_numbers+l + i));
    for (j = 0; j < n2; j++)
        mpz_set(R[j],*(array_of_numbers + m + 1+ j));

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (call(L[i],R[j])<=0)
        {
            mpz_set(*(array_of_numbers+k),L[i]);
            i++;
        }
        else
        {
            mpz_set(*(array_of_numbers+k),R[j]);
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        mpz_set(*(array_of_numbers+k),L[i]);
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        mpz_set(*(array_of_numbers+k),R[j]);
        j++;
        k++;
    }
    for (int i=0;i<n1;i++)
    mpz_clear(L[i]);

    for (int i=0;i<n2;i++)
    mpz_clear(R[i]);
}


// thread function for multi-threading
void * mergesort_thread(void *arg)
{
    struct tsk *tsk = arg;
    int low;
    int high;
    // calculating low and high
    low = tsk->tsk_low;
    high = tsk->tsk_high;

    // evaluating mid point
    int mid = low + (high - low) / 2;

    if (low < high) {
        mergeSort(low, mid);
        mergeSort(mid + 1, high);
        merge(low, mid, high);
    }
    return 0;
}


void main()
{
  call = &compare_numbers;
  call1 = &swap_numbers;

  // t1 and t2 for calculating time for
  // merge sort
  clock_t t1, t2;


  create_random_array();
  t1 = clock();
  mergeSort(0, nums_in_list - 1);
  t2 = clock();
  for(int i=0; i<nums_in_list; i++)
  gmp_printf("The value after sort at %d = %Zd\n",i,*(array_of_numbers+i));
  printf("Time taken = %.8f", (t2-t1)/(double)CLOCKS_PER_SEC);

//   int THREAD_MAX=10;
//   pthread_t threads[THREAD_MAX];
//   struct tsk tsklist[THREAD_MAX];
//   struct tsk *tsk;
//   int len = nums_in_list / THREAD_MAX;
//   printf("THREADS:%d Nums_in_list:%d LEN:%d\n", THREAD_MAX, nums_in_list, len);
//
//   int low = 0;
//   for (int i = 0; i < THREAD_MAX; i++, low += len) {
//       tsk = &tsklist[i];
//       tsk->tsk_no = i;
//       tsk->tsk_low = low;
//       tsk->tsk_high = low + len - 1;
//         if (i == (THREAD_MAX - 1))
//             tsk->tsk_high = nums_in_list - 1;
//         printf("RANGE %d: %d %d\n", i, tsk->tsk_low, tsk->tsk_high);
//   }
//    t1 = clock();
// //   // creating threads
//   for (int i = 0; i < THREAD_MAX; i++) {
//       tsk = &tsklist[i];
//       pthread_create(&threads[i], NULL, mergesort_thread, tsk);
//   }
// //
// //   // joining all threads
//   for (int i = 0; i < THREAD_MAX; i++)
//       pthread_join(threads[i], NULL);
// //
// // // show the array values for each thread
//   for (int i = 0; i < THREAD_MAX; i++) {
//         tsk = &tsklist[i];
//         printf("SUB %d:", tsk->tsk_no);
//         for (int j = tsk->tsk_low; j <= tsk->tsk_high; ++j)
//             gmp_printf(" %Zd", *(array_of_numbers+j));
//         printf("\n");
//       }
// //
// //   //merge all data blocks of thread
//   struct tsk *tskm = &tsklist[0];
//   for (int i = 1; i < THREAD_MAX; i++) {
//         struct tsk *tsk = &tsklist[i];
//         merge(tskm->tsk_low, tsk->tsk_low - 1, tsk->tsk_high);
//     }
//     t2 = clock();
//     for(int i=0; i<nums_in_list; i++)
//     gmp_printf("The value after sort at %d = %Zd\n",i,*(array_of_numbers+i));
//     printf("Time taken = %.8f", (t2-t1)/(double)CLOCKS_PER_SEC);
free(array_of_numbers);
}
