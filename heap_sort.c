#include <gmp.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <malloc.h>
#include "heap_sort.h"
#include "thread_info.h"


void heapSort(mpz_t * array_of_numbers, int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(array_of_numbers, n, i);

    // One by one extract an element from heap
    for (int i=n-1; i>=0; i--)
    {
        // Move current root to end
        call1(array_of_numbers[0], array_of_numbers[i]);

        // call max heapify on the reduced heap
        heapify(array_of_numbers, i, 0);
    }
}

// To heapify a subtree rooted with node i which is
// an index in arr[]. n is size of heap
void heapify(mpz_t * array_of_numbers, int n, int i)
{
    int largest = i; // Initialize largest as root
    int l = 2*i + 1; // left = 2*i + 1
    int r = 2*i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && (call(array_of_numbers[l],array_of_numbers[largest])==1))
        largest = l;

    // If right child is larger than largest so far
    if (r < n && (call(array_of_numbers[r],array_of_numbers[largest])==1))
        largest = r;

    // If largest is not root
    if (largest != i)
    {
        call1(array_of_numbers[i], array_of_numbers[largest]);

        // Recursively heapify the affected sub-tree
        heapify(array_of_numbers, n, largest);
    }
}

void heap_sort(mpz_t * array_of_numbers,long int total_Numbers_In_List)
{
  clock_t t1, t2;
  call = &compare_numbers;
  call1 = &swap_numbers;
  t1 = clock();
  heapSort(array_of_numbers,total_Numbers_In_List);
  t2 = clock();
  for(int i=0; i<total_Numbers_In_List; i++)
  gmp_printf("The value after sort at %d = %Zd\n",i,array_of_numbers[i]);
  printf("Time taken = %.8f\n", (t2-t1)/(double)CLOCKS_PER_SEC);
}

void heap_sort_w_thread(mpz_t * array_of_numbers,long int total_Numbers_In_List)
{



}
