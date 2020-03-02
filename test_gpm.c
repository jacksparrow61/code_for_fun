#include <gmp.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


typedef struct pair
{
  mpz_t min;
  mpz_t max;
}min_max_struct;

void getMinMax(mpz_t arr[], int n);
int count_numbers_in_list(char *filename);

void main(int argc, char *argv[]){

    int nums_in_list =0;
    FILE * file_ptr = fopen(argv[1],"r");

    if(1==argc)
    {
    printf("Provide the filename with the list of numbers \n ");
    return ;
    }
    nums_in_list = count_numbers_in_list(argv[1]);
    printf("Total Numbers in the list = %d\n",nums_in_list);


    mpz_t array_of_numbers[nums_in_list];
    for(int i =0;i<nums_in_list;i++)
    {
      mpz_init(array_of_numbers[i]);
    }
    for(int i =0;i<nums_in_list;i++)
    {
    mpz_inp_str(array_of_numbers[i],file_ptr,10);
    gmp_printf("%Zd \n",array_of_numbers[i]);
    }

    getMinMax(array_of_numbers,nums_in_list);


    /* initialization of array_of_numbers */
    // array_of_numbers = (mpz_t *) malloc(nums_in_list * sizeof(mpz_t));
    // if (NULL == array_of_numbers) {
    //     printf("ERROR: Out of memory\n");
    //     return;
    // }
    // // for (int i = 0;i<nums_in_list-1;i++)
    // // {
    //  mpz_inp_str(*array_of_numbers[0],file_ptr,10);
    // gmp_printf("Array of numbers: %d = %Zd",0,array_of_numbers[0]);
    // }
    //When o longer need array_of_numbers
    // mpz_clear(max_num);
    // mpz_clear(max_num);
    // for(int i =0;i<nums_in_list;i++)
    // {
    //   mpz_clear(array_of_numbers[i]);
    // }
    /* no longer need A */
    // free(array_of_numbers);
}

int count_numbers_in_list(char * filename)
{
  // count the number of lines in the file which is equal to numebrs in list
    FILE *fp = fopen(filename,"r");
    int ch=0;
    int lines=0;

    if (fp == NULL)
    return 0;

    lines++;
    while ((ch = fgetc(fp)) != EOF)
      {
        if (ch == '\n')
      lines++;
      }
    fclose(fp);
    return lines;
}



void getMinMax(mpz_t arr[], int n)
{
  int i;
  min_max_struct list_min_max;
  mpz_init(list_min_max.min);
  mpz_init(list_min_max.max);
  /*If there is only one element then return it as min and max both*/
  if (n == 1)
  {
     mpz_set(list_min_max.max,arr[0]);
     mpz_set(list_min_max.min,arr[0]);
     gmp_printf("Maximum Number in the list is = %Zd\n",list_min_max.max);
     gmp_printf("Minimum Number in the list is = %Zd\n", list_min_max.min);
     return;
  }
  /* If there are more than one elements, then initialize min
      and max*/
  if (mpz_cmp(arr[0],arr[1])==0)
  {
    mpz_set(list_min_max.max,arr[1]);
    mpz_set(list_min_max.min,arr[1]);
  }
  else if (mpz_cmp(arr[0],arr[1])>0)
  {
    mpz_set(list_min_max.max,arr[0]);
    mpz_set(list_min_max.min,arr[1]);
  }
  else if (mpz_cmp(arr[0],arr[1])<0)
  {
    mpz_set(list_min_max.max,arr[1]);
    mpz_set(list_min_max.min,arr[0]);
  }

  for (i = 2; i<n; i++)
  {
    if (mpz_cmp(arr[i],list_min_max.max)>0)
      mpz_set(list_min_max.max,arr[i]);

    else if (mpz_cmp(arr[i],list_min_max.min)<0)
      mpz_set(list_min_max.min,arr[i]);
  }
  gmp_printf("Maximum Number in the list is = %Zd\n",list_min_max.max);
  gmp_printf("Minimum Number in the list is = %Zd\n", list_min_max.min);
}
