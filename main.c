#include <gmp.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "main.h"
#include "merge_sort.h"
#include "heap_sort.h"
#include "quick_sort.h"

char file_name[30];
long int total_Numbers_In_List;
mpz_t * array_of_numbers;
FILE * list_of_Numbers;
int algorithm=100; //Error Value
int thread_Mode=100; //Error Value

void main(int argc, char* argv[])
{

printf("\n..............Programm to Use Sorting Algorithms......MergeSort, HeapSort, Quicksort..........With/Without threading\n\n ");
printf("................Enter the name of txt file having the massive list of very long number................................. \n ");

input_file();
allocate_memory();
store_numbers_in_memory();
getMinMax();
choose_Algorithm();
choose_Thread_Mode();
    if(thread_Mode == ThreadOFF)
    {
      if(algorithm == MergeSort)
        merge_sort(array_of_numbers,total_Numbers_In_List);
      else if (algorithm == HeapSort)
        heap_sort(array_of_numbers,total_Numbers_In_List);
      else if (algorithm == QuickSort)
        quick_sort(array_of_numbers,total_Numbers_In_List);
      else
      printf("Error Wrong Algorithm");
    }
    else if (thread_Mode == ThreadON)
    {
      if(algorithm == MergeSort)
        merge_sort_w_thread(array_of_numbers,total_Numbers_In_List);
    }

}

void choose_Thread_Mode(void)
{
 printf("Enter Thread Mode:.......... Type..........ON => Thread Mode ON............OF => Thread Mode OFF\n ");
 char thread_input[2];
 scanf("%s",thread_input);
  if(strcmp(thread_input,"ON")==0)
    thread_Mode = ThreadON;
  else if (strcmp(thread_input,"OF")==0)
    thread_Mode = ThreadOFF;
  else
    thread_Mode =100;

  if(thread_Mode==4)
  printf("Thread mode = ThreadOFF\n");
  else if(thread_Mode==3)
  printf("Thread mode = ThreadON\n");
  else if (thread_Mode=100)
  printf("ERROR\n");
}


void choose_Algorithm(void)
{
  printf("Enter which Algorithm is to be used\n.......Type........\nm for (m)ergesort\nq for (q)uicksort\nh for (h)eapsort\n ");
  char algorithm_selection;
  scanf("%s",&algorithm_selection);
  switch(algorithm_selection)
  {
    case 'q':
      algorithm = QuickSort;
      break;
    case 'm':
      algorithm = MergeSort;
      break;
    case 'h':
      algorithm = HeapSort;
      break;
    default:
      algorithm = 100;
      printf("ERROR: Invalid Input\n");
  }
  printf("Selected algorithm is %d\n", algorithm);
}


void getMinMax()
{
  int i;
  Min_Max_Struct list_min_max;
  mpz_init(list_min_max.min);
  mpz_init(list_min_max.max);
  /*If there is only one element then return it as min and max both*/
  if (total_Numbers_In_List == 1)
  {
     mpz_set(list_min_max.max,*(array_of_numbers));
     mpz_set(list_min_max.min,*(array_of_numbers));
     gmp_printf("Maximum Number in the list is = %Zd\n",list_min_max.max);
     gmp_printf("Minimum Number in the list is = %Zd\n", list_min_max.min);
     return;
  }
  /* If there are more than one elements, then initialize min
      and max*/
  if (mpz_cmp(*(array_of_numbers),*(array_of_numbers+1))==0)
  {
    mpz_set(list_min_max.max,*(array_of_numbers+1));
    mpz_set(list_min_max.min,*(array_of_numbers+1));
  }
  else if (mpz_cmp(*(array_of_numbers),*(array_of_numbers+1))>0)
  {
    mpz_set(list_min_max.max,*(array_of_numbers));
    mpz_set(list_min_max.min,*(array_of_numbers+1));
  }
  else if (mpz_cmp(*(array_of_numbers),*(array_of_numbers+1))<0)
  {
    mpz_set(list_min_max.max,*(array_of_numbers+1));
    mpz_set(list_min_max.min,*(array_of_numbers));
  }

  for (i = 2; i<total_Numbers_In_List; i++)
  {
    if (mpz_cmp(*(array_of_numbers+i),list_min_max.max)>0)
      mpz_set(list_min_max.max,*(array_of_numbers+i));

    else if (mpz_cmp(*(array_of_numbers+i),list_min_max.min)<0)
      mpz_set(list_min_max.min,*(array_of_numbers+i));
  }
  gmp_printf("Maximum Number in the list is = %Zd\n",list_min_max.max);
  gmp_printf("Minimum Number in the list is = %Zd\n", list_min_max.min);
  mpz_clear(list_min_max.min);
  mpz_clear(list_min_max.max);
}

void allocate_memory(void)
{
  array_of_numbers = (mpz_t *)malloc(total_Numbers_In_List*sizeof(mpz_t));
  if (NULL == array_of_numbers) {
      printf("ERROR: Out of memory\n");
      return;
  }
  for(int i =0;i<total_Numbers_In_List;i++)
  mpz_init(*(array_of_numbers+i));
}

void store_numbers_in_memory(void)
{
  list_of_Numbers = fopen(file_name,"r");

  if(total_Numbers_In_List>0)
  {
    for(int i =0;i<total_Numbers_In_List;i++)
    {
    mpz_inp_str(*(array_of_numbers+i),list_of_Numbers,10);
    gmp_printf("%Zd \n",*(array_of_numbers+i));
    }
    fclose(list_of_Numbers);
   }
}


void input_file(void)
{
  scanf("%s",file_name);
  printf("Received File : %s \n",file_name);

  if(file_name == NULL)
  {
    printf("..............No txt file with numbers entered..........Application Exit......\n");
    return;
  }


  list_of_Numbers = fopen(file_name,"r");
  if (list_of_Numbers == NULL)
  {
    printf(".......................TXT file is empty or invalid...............Application Exit......\n");
    return;
  }
  fclose(list_of_Numbers);
  total_Numbers_In_List = count_numbers_in_list(file_name);
  printf("Total Numbers in the list = %ld\n",total_Numbers_In_List);

}



long int count_numbers_in_list(char * filename)
{
  // count the number of lines in the file which is equal to numebrs in list
    FILE *fp = fopen(filename,"r");
    int ch=0;
    long int lines=0;

    if (fp == NULL)
    return 0;
    while ((ch = fgetc(fp)) != EOF)
      {
        if (ch == '\n')
      lines++;
      }
    fclose(fp);
    return lines;
}
