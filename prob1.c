#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
// #include <mpi.h>
#include <time.h>
#include <string.h>

/**********************************************
 * The checkDigits function receives a string
 * and its length as an integer. The function
 * parses through each character of the string,
 * converts it to an integer, and checks if
 * the integer is odd. If at any point an even
 * integer is detected, the function returns 1,
 * which is the fail state. If no even integers
 * are detected, this means that the received
 * string, containing an integer, has no even
 * digits, and the number is reversible. The
 * function returns 0, meaning it is successful.
 **********************************************/

int checkDigits(char *str, int strlen){
  int i; // for for loops
  for (i = 0; i < strlen; i++)// read through array
    if ((str[i] - '0') % 2 == 0) // if any digit of the number is even...
      return 1;
  
  return 0;
}


/**********************************************
 * The convIntToStr function recieves a pointer
 * to a string and an integer, and using sprintf,
 * converts the target integer x into a string.
 * The function returns the new string's length,
 * and the str in the main function now becomes
 * the target integer x.
 * 
 **********************************************/

int convIntToStr(char *str, int x){
  sprintf(str, "%d", x);
  return(strlen(str));
}


/**********************************************
 * This function receives an integer that has been
 * converted to a string via convIntToStr, and
 * that string's length. The function reads backwards
 * through the string, converting its digits to
 * integers and adding them to an int total.
 * This total equals the original number with its
 * digits reversed. This number is then returned.
 * 
 **********************************************/

int reversible(char *testval, int strlen){
  int retval = 0;
  int j = strlen-1;
  int i; // for for loops
  for (i = strlen; i > 0; i--){
    retval = 10 * retval + (testval[j] - '0');
    j--;
  }
  
  return retval;
}

//addition has to be of an even and an odd in order to get an odd result.
//START BY FINDING REVERSIBLE NUMBERS UNDER 1000 (ADDS UP TO 120)
int main(int argc, char** argv){
  clock_t start_t;
  start_t = clock();
  //take num
  //find reverse
  //if (num+reverse) % 2 == 0
  //	do nothing
  //else
  // check the digits to see if they are odd
  //NOTE: trailing 0's are not accepted, keep this in mind after reverse
  int i; // for for loops
  int sum = 0;
  int reverse, result;
  char str[1];
//   char *str2 = malloc(sizeof(char));
  int strlen, resultLength; //string length and result length (# of digits)
  for (i = 1; i < 1000000000; i++){
    strlen = convIntToStr(str, i);
    reverse = reversible(str, strlen);
    
    if (strlen == convIntToStr(str, reverse)){ // this check eliminates all values that end with 0, as per the instructions
						// this works because if 990 is converted and reversed, 99 is returned. 990 obviously is not the same length as 99.
//       printf("reverse of %d is %d\n", i, reverse);
      if ((i + reverse) % 2 == 1){
	//convert result of i + reverse into a string
	//parse through and convert each digit into an int
	//if any digit is even, return 1 when encountered
	//else, increment sum like below
	result = i + reverse;
	resultLength = convIntToStr(str, result);
	if (checkDigits(str, resultLength) == 0)
	  sum++;
      }
    }
  }
  start_t = clock() - start_t;
  printf("Total time taken by CPU: %2.5f\n", (float)start_t/CLOCKS_PER_SEC  );
  printf("Exiting program...\n");
  printf("Answer: %d\n", sum); // prints the answer to the Euler problem
  
  return 0;
}