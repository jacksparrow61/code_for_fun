


void merge(mpz_t * array_of_numbers,int l, int m, int r);
void mergeSort(mpz_t * array_of_numbers,int l, int r);
void merge_sort(mpz_t * array_of_numbers,long int total_Numbers_In_List);

void merge_sections_of_array(int number, int aggregation,mpz_t * array_of_numbers,long int arr_block_len, long int total_Numbers_In_List);
void * mergesort_thread(void *arg);
void merge_sort_w_thread(mpz_t * array_of_numbers,long int total_Numbers_In_List);
