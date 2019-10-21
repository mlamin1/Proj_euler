#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h> /* defines types used by sys/stat.h */
#include <sys/stat.h> /* defines S_IREAD & S_IWRITE */
#include <gmp.h>
#include <math.h>
#include <limits.h>

//Receives fully concatenated number and its length.
unsigned long contiguous_Int(mpz_t str, size_t length){
	mpz_t sum, full_Int, bufsize, j;
	mpz_init(sum);
	mpz_init(full_Int);
	mpz_init_set_ui(bufsize, 1);
	mpz_init_set_ui(j, 0); // used in for loops
	mpz_t strcpy, conditional, lengthplusone;
	mpz_t exponent; // will hold 1 concat of n
	mpz_init(exponent); // init exponent value to 0
	mpz_init(conditional); // loop conditional
// 	mpz_ui_pow_ui(exponent, 10, mpz_get_ui(length)); 
	mpz_init_set(strcpy, str);//copy of str
	mpz_init_set(lengthplusone, length);//copy of length
	mpz_add_ui(lengthplusone, lengthplusone, 1);//add 1
	mpz_t lenminbsize;//length - bufsize
	while ((mpz_cmp(bufsize, lengthplusone)) < 0){ // while buffer size does not exceed length of C(N,k)
		mpz_init_set(strcpy, str);//copy of str
		mpz_init_set(lenminbsize, length);
		mpz_sub(lenminbsize, lenminbsize, bufsize);
		mpz_add_ui(conditional, lenminbsize, 1);
		for (j; (mpz_cmp(j, conditional)) < 0; mpz_add_ui(j, j, 1)){
			mpz_set_ui(full_Int, 0);
			mpz_sub(lenminbsize, lenminbsize, j);
			// fullint += str/(10^(length-j-bufsize))
			mpz_ui_pow_ui(exponent, 10, lenminbsize); 
			mpz_tdiv_q(strcpy, strcpy, exponent);
			mpz_add(full_Int, full_Int, strcpy);
			
// 			sum += full_int; // add this integer to the sum
			mpz_add(sum, sum, full_Int);
// 			printf("SUM IS: %lu \n", sum);

		}
		mpz_add_ui(bufsize, bufsize, 1); // increase bufsize by 1
	}
	mpz_t modres, div;
	mpz_init_set_ui(div, 1000000007); //sets divisor to 1000000007
	mpz_init(modres); //initialize value that will hold modulus result to 0
// 	printf("The following is the sum mod 1000000007\n");
	mpz_tdiv_r(modres, sum, div); // divide n by div, store remainder rounded down to 0 in modres
// 	mpz_out_str(stdout, 10, modres);//output result of modulus
	mpz_clear(sum);
	mpz_clear(full_Int);
	mpz_clear(bufsize);
	mpz_clear(j);
	mpz_clear(strcpy);
	mpz_clear(conditional);
	mpz_clear(lengthplusone);
	mpz_clear(exponent);
	mpz_clear(lenminbsize);
	mpz_clear(div);
	mpz_clear(sum);
	
	//AT END CONVERT MPZ INTO ULONG
	unsigned long result = mpz_get_ui(modres);
	mpz_clear(modres);
	return result;
}

//Uses Sieve of Erostosthenes algorithm to find first 1M primes and store in array.
void concat_Prime(unsigned long n, unsigned long *temp_arr, unsigned long *return_arr)
{
    int i,j;
    int k = 0;
    //populating array with naturals numbers
    for(i = 2; i<=n; i++)
        temp_arr[i] = i;

    i = 2;
    while ((i*i) <= n){//calculate primality of #s until reach millionth prime
        if (temp_arr[i] != 0){
            for(j=2; j<n; j++){
                if (temp_arr[i]*j > n) // out of bounds check
                    break;
                else
                    temp_arr[temp_arr[i]*j]=0; // Change all multiples of i to 0
            }
        }
        i++;
    }
    for(i = 2; i<=n; i++)
    {
        if (temp_arr[i] != 0){ // if current value is not 0, then it is prime.
//             printf("%ld\n",temp_arr[i]);
	    return_arr[k] = temp_arr[i]; // add current prime to return_arr
	    k++; // increment count of primes
	}
    }
}

int main(int argc, char **argv)
{
// 	clock_t start_t;
// 	start_t = clock();
	unsigned long number = 15485864;//atoi(argv[1]);
// 	unsigned long kopies = 1;//atoi(argv[2]);
	unsigned long vim = 1000000;
	unsigned long i;
	unsigned long *prime = malloc(number * sizeof(unsigned long));
	unsigned long *primes = malloc(vim * sizeof(unsigned long));//now contains only first 1000000 primes
	mpz_t n, div, modres;
	mpz_init(n); // initialize to 0
	concat_Prime(number, prime, primes);
// 	printf("Prime Numbers:: \n");
// 	for(i = 0; i < 1000000; i++)
// 	{
// 		printf("%lu ", primes[i]);
// 	}
// 	printf("\n");
// 	printf("\n");
// 	printf("\n");
	char holdConcat[128]; // this will only ever hold a string of max size 8 characters, because it only holds
				//one prime at a time and max prime size in this case is 8 digits.
	for(i = 0; i < vim; i++) // P(N): converts array to single int by concatenating all calculated prime numbers
	{
		sprintf(holdConcat, "%ld", primes[i]);
		double conlen = strlen(holdConcat);
		mpz_mul_ui(n, n, (unsigned long)pow(10.0, conlen));// n = n * 10
		mpz_add_ui(n, n, (unsigned long)atoi(holdConcat));// n = n + x
	}
// 	unsigned long long helpme = (unsigned long long)mpz_get_ui(n);
// 	printf("concat answer in unsigned long long form: %lld\n", helpme);
	printf("The following is the first 1000000 primes concatenated into a single integer in base 10\n");
	mpz_out_str(stdout, 10, n);
	printf("\n");
	printf("\n");
	printf("\n");
	
	mpz_t concatprim, exponent, loopstart, looplimit, concatlength; // will hold 1 concat of n
	mpz_init_set(concatprim, n); // set concatprim = to n
	mpz_init_set_ui(concatlength, mpz_sizeinbase(concatprim, 10));//finds length of concatprim and stores it
	mpz_init(exponent); // init exponent value to 0
	mpz_ui_pow_ui(exponent, 10, mpz_get_ui(concatlength)); 
	mpz_init(loopstart);//sets start of for loop to 0
	mpz_init_set_ui(looplimit, 1000000000000); // set for loop limit to 1 trillion
	
	for (loopstart; (mpz_cmp(loopstart, looplimit)) < 0; mpz_add_ui(loopstart, loopstart, 1)){ // this takes P(N) and concatenates it onto itself 10^12 times, finding C(N, k)
	  mpz_mul(concatprim, concatprim, exponent); // make room in dblprim to concat n to dblprim
	  mpz_add(concatprim, concatprim, n); // add n to dblprim to concatenate
	}
	unsigned long answer;
	answer = contiguous_Int(concatprim, mpz_sizeinbase(concatprim, 10));
	printf("The final answer is %ld\n", answer);

	mpz_clear(n);
	mpz_clear(div);
	mpz_clear(modres);
	mpz_clear(concatprim);
	mpz_clear(exponent);
	mpz_clear(loopstart);
	mpz_clear(looplimit);
	mpz_clear(concatlength);
	free(prime);
	free(primes);
	return 0;
}
