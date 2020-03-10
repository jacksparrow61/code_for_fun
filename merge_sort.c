#include <gmp.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "merge_sort.h"
#include <malloc.h>

#define THREAD_MAX 4

long int arr_block_len =0;

struct tsk {
    int tsk_no;
    int tsk_low;
    int tsk_high;
    mpz_t * arr;
};

// void merge_sections_of_array(int number, int aggregation);
// void * mergesort_thread(void *arg);



int compare_numbers(mpz_t a ,mpz_t b)
{
return mpz_cmp(a,b);
}


void swap_numbers(mpz_t a, mpz_t b)
{
mpz_swap(a,b);
return;
}


callback_compare call;
callback_swap call1;

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(mpz_t * array_of_numbers,int l, int r)
{
   if (l < r)
   {
       // Same as (l+r)/2, but avoids overflow for
       // large l and h
       int m = l+(r-l)/2;
       // Sort first and second halves
       mergeSort(array_of_numbers,l, m);
       mergeSort(array_of_numbers,m+1, r);
       merge(array_of_numbers,l, m, r);
   }
}


// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(mpz_t * array_of_numbers,int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    mpz_t *L;
    mpz_t *R;
    L = (mpz_t *)malloc(n1*sizeof(mpz_t));
    for (int i=0;i<n1;i++)
    mpz_init(L[i]);

    R = (mpz_t *)malloc(n2*sizeof(mpz_t));
    for (int i=0;i<n2;i++)
    mpz_init(R[i]);

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        mpz_set(L[i],array_of_numbers[l + i]);
    for (j = 0; j < n2; j++)
        mpz_set(R[j],array_of_numbers[m + 1+ j]);

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (call(L[i],R[j])<=0)
        {
            mpz_set(array_of_numbers[k],L[i]);
            i++;
        }
        else
        {
            mpz_set(array_of_numbers[k],R[j]);
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        mpz_set(array_of_numbers[k],L[i]);
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        mpz_set(array_of_numbers[k],R[j]);
        j++;
        k++;
    }
    // for (int i=0;i<n1;i++)
    // mpz_clear(L[i]);

    // for (int i=0;i<n2;i++)
    // mpz_clear(R[i]);
    free(L);
    free(R);
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
        mergeSort(tsk->arr,low, mid);
        mergeSort(tsk->arr,mid + 1, high);
        merge(tsk->arr,low, mid, high);
    }
    return 0;
}
/* merge locally sorted sections */
void merge_sections_of_array(int number, int aggregation,mpz_t * array_of_numbers,long int arr_block_len, long int total_Numbers_In_List) {
    for(int i = 0; i < number; i = i + 2) {
        int left = i * (arr_block_len * aggregation);
        int right = ((i + 2) * arr_block_len * aggregation) - 1;
        int middle = left + (arr_block_len * aggregation) - 1;
        if (right >= total_Numbers_In_List) {
            right = total_Numbers_In_List - 1;
        }
        merge(array_of_numbers,left, middle, right);
    }
    if (number / 2 >= 1) {
        merge_sections_of_array(number / 2, aggregation * 2,array_of_numbers,arr_block_len,total_Numbers_In_List);
    }
}


void merge_sort(mpz_t * array_of_numbers,long int total_Numbers_In_List)
{
  clock_t t1, t2;
  call = &compare_numbers;
  call1 = &swap_numbers;
  t1 = clock();
  mergeSort(array_of_numbers,0, total_Numbers_In_List - 1);
  t2 = clock();
  for(int i=0; i<total_Numbers_In_List; i++)
  gmp_printf("The value after sort at %d = %Zd\n",i,array_of_numbers[i]);
  printf("Time taken = %.8f\n", (t2-t1)/(double)CLOCKS_PER_SEC);
}

void merge_sort_w_thread(mpz_t * array_of_numbers,long int total_Numbers_In_List)
{
    call = &compare_numbers;
    call1 = &swap_numbers;
    arr_block_len = total_Numbers_In_List/THREAD_MAX;
    clock_t t1, t2;
    pthread_t threads[THREAD_MAX];
    struct tsk tsklist[THREAD_MAX];
      // for(int i=0;i<THREAD_MAX;i++){
      //   tsklist[i].arr = (mpz_t *)malloc(1*sizeof(mpz_t));
      //   mpz_init(*(tsklist[i].arr));
      // }

    struct tsk *tsk;
    // for(int i=0;i<THREAD_MAX;i++){
    //   tsk->.arr = (mpz_t *)malloc(1*sizeof(mpz_t));
    //   mpz_init(*(tsk->arr));
    // }
    printf("THREADS:%d Numbers_in_list:%ld LENGTH OF BLOCK:%ld\n", THREAD_MAX, total_Numbers_In_List, arr_block_len);

    int low = 0;
    for (int i = 0; i < THREAD_MAX; i++, low += arr_block_len) {
        tsk = &tsklist[i];
        tsk->tsk_no = i;
        tsk->tsk_low = low;
        tsk->tsk_high = low + arr_block_len - 1;
          if (i == (THREAD_MAX - 1))
              tsk->tsk_high = total_Numbers_In_List - 1;
          printf("RANGE %d: %d %d\n", i, tsk->tsk_low, tsk->tsk_high);
        tsk->arr = array_of_numbers;
    }
     t1 = clock();
  //   // creating threads
    for (int i = 0; i < THREAD_MAX; i++) {
        tsk = &tsklist[i];
        pthread_create(&threads[i], NULL, mergesort_thread, tsk);
    }
  //
  //   // joining all threads
    for (int i = 0; i < THREAD_MAX; i++)
        pthread_join(threads[i], NULL);
  //
  // // show the array values for each thread
    // for (int i = 0; i < THREAD_MAX; i++) {
    //       tsk = &tsklist[i];
    //       printf("SUB %d:", tsk->tsk_no);
    //       for (int j = tsk->tsk_low; j <= tsk->tsk_high; ++j)
    //           gmp_printf(" %Zd", *(array_of_numbers+j));
    //       printf("\n");
    //     }
  //
  //   //merge all data blocks of thread
    // struct tsk *tskm = &tsklist[0];
    // for (int i = 1; i < THREAD_MAX; i++) {
    //       struct tsk *tsk = &tsklist[i];
    //       merge(tskm->tsk_low, tsk->tsk_low - 1, tsk->tsk_high);
    //   }
    merge_sections_of_array(THREAD_MAX,1,array_of_numbers,arr_block_len,total_Numbers_In_List);
      t2 = clock();
      for(int i=0; i<total_Numbers_In_List; i++)
      gmp_printf("The value after sort at %d = %Zd\n",i,*(array_of_numbers+i));
      printf("Time taken = %.8f\n", (t2-t1)/(double)CLOCKS_PER_SEC);

      // for(int i=0;i<THREAD_MAX;i++){
      // free(tsklist[i].arr);
      // }

}
