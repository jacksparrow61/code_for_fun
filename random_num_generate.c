#include <stdlib.h>             /* Standard Lib    ISOC  */
#include <stdio.h>              /* I/O lib         ISOC  */
#include <stdarg.h>             /* Variable args   ISOC  */
#include <gmp.h>                /* GNU GMP Library       */
#include <time.h>

int main (void) {
  int             i;            /* Loop variable */
  mpz_t           randNum;      /* Hold our random numbers */
  int             rndBit;       /* Bound for mpz_urandomb */
  // mpz_t           rndBnd;       /* Bound for mpz_urandomm */
  int nums_in_list = 10000;
  gmp_randstate_t gmpRandState; /* Random generator state object */
  FILE * fptr;
  fptr = fopen("mpz_integer_list.txt","w");
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

  printf("%d random numbers in U[0, -1+2^%d]: are in the txt file mpz_integer_list.txt\n",nums_in_list,rndBit);
  for(i=0; i<nums_in_list; i++) {
    /* mpz_get_ui() can convert randNum to unsigned long int... */
    mpz_urandomb(randNum, gmpRandState, rndBit);
    mpz_out_str(fptr, 10, randNum);
    if(i!=(nums_in_list-1))
    fputc('\n', fptr);
  } /* end for */
  fclose(fptr);
  // printf("10 random numbers in U[0, ");
  // mpz_out_str(stdout, 10, rndBnd);
  // printf("]:\n");
  // for(i=0; i<10; i++) {
  //   /* mpz_get_ui() can convert randNum to unsigned long int... */
  //   mpz_urandomm(randNum, gmpRandState, rndBnd);
  //   mpz_out_str(stdout, 10, randNum);
  //   printf("\n");
  // } /* end for */

  /* Clean up resources occupied by compensated */
  gmp_randclear(gmpRandState);

  /* Clean up resources occupied by our mpz_t variables */
  mpz_clear(randNum);
  // mpz_clear(rndBnd);
  return 0;
} /* end func main */
