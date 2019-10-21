#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include<unistd.h>

unsigned long contiguous_Int(unsigned long *str, unsigned long length, unsigned long *counter){
	unsigned long sum = 0;
	unsigned long full_int;
	unsigned long bufsize = 1;
	unsigned long  *buffer = malloc(length * bufsize*sizeof(unsigned long)); //bufer RECEIVES added ints
	unsigned long j, k,i;
	while (bufsize < length+1){ // while loop is correct
		for (j = 0; j < length-bufsize+1; j++){
			full_int = 0;
			for (k = 0; k < bufsize; k++)
			{
				buffer[k] = str[j+k];
			}
/*
			//Test purpose to see what is in buffer.
			for(i = 0; i < bufsize; i++)
			{
				printf("%lu", buffer[i]);
			}
			printf("\n");
*/

			for(i = 0; i < bufsize; i++)
			{		
				full_int = 10 * full_int + buffer[i];
				counter++;
			}
			printf("FULL INT %lu  + %lu \n", sum, full_int);

			sum += full_int;
			counter++;
			printf("SUM IS: %lu \n", sum);

		}
		bufsize++;
//		sum = sum * 10;
	}

	unsigned long mod_num = 1000000007;
//	printf("%ld \n", mod_num);
	free(buffer);
	sum = (sum % mod_num);
	return sum;
}


unsigned long count(unsigned long i)
{	
	unsigned long counter = 0;
	while(i % 10 != 0)
	{
		i = i / 10;
		counter++;
	}
	return counter;
}

unsigned long *get_bufInt(unsigned long num)
{
//	printf("IN GET BUF INT \n");
	unsigned long amount_num = count(num);
	unsigned long temp_arr[amount_num];
//	printf("num: %lu \n", num);
	unsigned long temp, temp2 = num;
	unsigned long temp_amount = amount_num;
//	printf("Temp_AMOUNT: %d \n", temp_amount);
	while(amount_num > 0)
	{	
		temp = temp2 % 10;
//		printf("Temp: %lu \n", temp);
		temp_arr[(temp_amount - 1)] = temp;
		temp2 = temp2 / 10;
		amount_num--;
		temp_amount--;
	}
	return temp_arr;
}



unsigned long  big_integer(unsigned long length, unsigned long *arr, unsigned long *new_arr, unsigned long *counter_op)
{
	
	unsigned long temp_num;
	unsigned long i, j;
//	int size = sizeof(new_arr) / sizeof(new_arr[0]);
	unsigned long *temp_arr, curr = 0, currsize;
	unsigned long counter = 0;
	for(i = 0; i < length; i++)
	{
//		printf("In for loop \n");
//		printf("arr[i]: %d \n", arr[i]);
		int size_of_num = count(arr[i]);				//Gets the size of the amount of numbers in array at the moment.
//		int ano = size_of_num;
//		printf("size_of_num: %d \n", size_of_num);
		temp_num = arr[i];
		temp_arr = get_bufInt(temp_num);
//		printf("MAIN TEMP ARR %d \n", temp_arr[0]);
		curr += size_of_num;
		counter_op++;
		currsize = size_of_num;
		for(j = 0; j < size_of_num; j++)
		{	
//		printf("MAIN TEMP ARR22 %d \n", temp_arr[j]);
			new_arr[curr - currsize] = temp_arr[j];
			currsize--;
			counter++;
		}
		size_of_num = 0;
	}
	return counter;
}




//Used to convert integer to string
unsigned long convIntToStr(char *str, unsigned long x){
	sprintf(str, "%lu", x);
	return(strlen(str));
}


//P(n): The integer formed by concatenating the first n primes together.
void concat_Prime(unsigned long n, unsigned long *temp_arr, unsigned long *counter)
{
	unsigned long i, index, count = 3, temp_count = 0;

	if(n >= 1)				//	if theres only one or more prime being requested, start with the first prime number 2.
	{	
		counter++;
		int num = 2;
		temp_arr[temp_count] = num;	//put the first prime number in a temp array
		temp_count++;
	}
	for(i = 2; i <= n;)			//from 2(first prime) to the amount being requested, do steuff below to get others
	{
		for(index = 2; index <= count -1; index++)		//comparison if the index is evenly divisible
		{
			if((count % index) == 0)			//if it is continue to increment index.
			{
				break;
			}
		}
		if(index == count)				// if index is equal to the next prime number, add it to the temp array
		{
			counter++;
			temp_arr[temp_count] = count;
			i++;
			temp_count++;
		}
		count++;
	}
}


//C(n,k): the integer formed by concatenating k copies of P(n) together.
void concat_Copies(unsigned long number, unsigned long kopies, unsigned long *new_Copies, unsigned long *prime, unsigned long *counter)
{
	unsigned long i, j, k = 0;
	for(i = 0; i < kopies; i++)			//goes through and copies the amount of primes to be copied in new_copies function
	{
		for(j = 0; j < number; j++)
		{
			new_Copies[k] = prime[j];
			k++;
		}
	}
}



int main(int argc, char **argv)
{
	unsigned long number = atoi(argv[1]);
	unsigned long kopies = atoi(argv[2]);
	unsigned long *prime;
	unsigned long i;
	unsigned long numbop_prime = 0, numbop_catcopies = 0, numbop_bigint = 0, numbop_cont = 0;
	prime  = malloc(number * sizeof(unsigned long));
	unsigned long *prime_cat = malloc((number * kopies) * sizeof(unsigned long));
	unsigned long *big_Int = malloc((number * kopies) * (number) * sizeof(unsigned long));
	unsigned long big_Int_size;
	
	concat_Prime(number, prime, &numbop_prime);
	printf("Prime Numbers:: \n");
	for(i = 0; i < number; i++)
	{
		printf("%lu ", prime[i]);
	}
	printf("\n");
	printf("\n");
	printf("\n");

	concat_Copies(number, kopies, prime_cat, prime, &numbop_catcopies);
	printf("CONCAT PRIME NUMBERS:: \n");

	for(i = 0; i < (number * kopies); i++)
	{	
		printf("%lu ", prime_cat[i]);
	}
	printf("\n");
	printf("\n");

	big_Int_size = big_integer((number * kopies), prime_cat, big_Int, &numbop_bigint);

	printf("BIG INTEGER:: \n");
	for(i = 0; i < big_Int_size; i++)
	{	
		printf("%lu", big_Int[i]);
	}
	printf("\n");
	printf("\n");
	

	unsigned long answer;
	answer = contiguous_Int(big_Int,(big_Int_size), &numbop_cont);
	
	printf("numb op for cat_prime: %lu \n", numbop_prime);
	printf("numb op for cat_prime: %lu \n", numbop_catcopies);
	printf("numb op for cat_prime: %lu \n", numbop_bigint);
	printf("numb op for cat_prime: %lu \n", numbop_cont);
	
	printf("Answer: %ld \n", answer);

	free(prime);
	free(prime_cat);
	return 0;
}
