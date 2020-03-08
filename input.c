#include <gmp.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

mpz_t *A;

int main (void) {
  int num =10;
  int             rndBit;       /* Bound for mpz_urandomb */
  gmp_randstate_t gmpRandState;



  /* initialization of A */
A = (mpz_t *) malloc(num * sizeof(mpz_t));
if (NULL == A) {
    printf("ERROR: Out of memory\n");
    return 1;
}


time_t current_time = time(NULL);
/* Initialize Bounds */
rndBit = 128;
// mpz_init_set_str(rndBnd, "1000", 10);

/* Initialize the random state with default algorithm... */
gmp_randinit_default(gmpRandState);

/* Seed the state with an unsigned long int before we begin.. */
gmp_randseed_ui(gmpRandState, current_time);

printf("%d random numbers in U[0, -1+2^%d]:are \n",num,rndBit);
for(int i=0; i<num; i++) {
  /* mpz_get_ui() can convert randNum to unsigned long int... */
  mpz_urandomb(*(A+i), gmpRandState, rndBit);
gmp_printf("%Zd", *(A+i));
  if(i!=(num-1))
  printf("\n");
} /* end for */

} /* end func main */
