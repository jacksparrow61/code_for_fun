



typedef struct pair
{
  mpz_t min;
  mpz_t max;
}Min_Max_Struct;

enum selection{
  QuickSort =0,
  MergeSort,
  HeapSort,
  ThreadON,
  ThreadOFF
};

void getMinMax(void);
long int count_numbers_in_list(char * filename);
void input_file(void);
void allocate_memory(void);
void store_numbers_in_memory(void);
void choose_Algorithm(void);
void choose_Thread_Mode(void);
