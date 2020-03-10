#include <gmp.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <malloc.h>
#include "quick_sort.h"
#include "thread_info.h"



void quicksort(mpz_t * array_of_numbers,int low,int high)
{
 if (low < high)
 {
   int p = partition(array_of_numbers,low,high);

   quicksort(array_of_numbers,low,p-1);
   quicksort(array_of_numbers,p+1,high);
 }
}

int partition(mpz_t * array_of_numbers,int low,int high)
{
  mpz_t pivot;
  mpz_init(pivot);
  mpz_set(pivot,array_of_numbers[high]);

  int i = (low - 1);

  for (int j = low; j <= high - 1; j++)
  {
     // If current element is smaller than the pivot
     if (call(array_of_numbers[j],pivot)==-1)
     {
         i++; // increment index of smaller element
         call1(array_of_numbers[i], array_of_numbers[j]);  //swap_numbers
     }
   }
   call1(array_of_numbers[i + 1], array_of_numbers[high]);
   mpz_clear(pivot);
   return (i + 1);
}




void quick_sort(mpz_t * array_of_numbers, long int total_Numbers_In_List)
{

call = &compare_numbers;
call1 = &swap_numbers;
t1 = clock();
quicksort(array_of_numbers,0,total_Numbers_In_List-1);
t2 = clock();
for(int i=0; i<total_Numbers_In_List; i++)
gmp_printf("The value after sort at %d = %Zd\n",i,array_of_numbers[i]);
printf("Time taken = %.8f\n", (t2-t1)/(double)CLOCKS_PER_SEC);

}
