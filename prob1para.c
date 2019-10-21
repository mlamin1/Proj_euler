#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
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
  int i;
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
  int i;
  for (i = strlen; i > 0; i--){
    retval = 10 * retval + (testval[j] - '0');
    j--;
  }
  
  return retval;
}




int main(int argc, char** argv){
  clock_t start_t, avg_t;
  start_t = clock();
  
  int rank, size;
  int globalsum = 0;
  int sum = 0;
  int reverse, result;
  int i; // for for loops
  char *str = malloc(24*sizeof(char)); //mult by 24 arbitrary, stops invalid read and write. research?
  //   char *str2 = malloc(sizeof(char));
  int strlen, resultLength; //string length and result length (# of digits)
   
  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  if (rank+1 == size){
    for (i = 1 + ((1000000000/size) * rank); i < ((1000000000/size) * (rank+1)) + (1000000000%size); i++){
      strlen = convIntToStr(str, i);
      reverse = reversible(str, strlen);
      
      if (strlen == convIntToStr(str, reverse)){ // this check eliminates all values that end with 0, as per the instructions
	// this works because if 990 is converted and reversed, 99 is returned. 990 obviously is not the same length as 99.
	//       printf("reverse of %d is %d\n", i, reverse);
	if ((i + reverse) % 2 == 1){
	  
	  result = i + reverse;
	  resultLength = convIntToStr(str, result);
	  if (checkDigits(str, resultLength) == 0)
	    sum++;
	}
      }
    }
  
  }
  else{
  for (i = 1 + ((1000000000/size) * rank); i < ((1000000000/size) * (rank+1)); i++){
    strlen = convIntToStr(str, i);
    reverse = reversible(str, strlen);
    
    if (strlen == convIntToStr(str, reverse)){ // this check eliminates all values that end with 0, as per the instructions
      // this works because if 990 is converted and reversed, 99 is returned. 990 obviously is not the same length as 99.
      //       printf("reverse of %d is %d\n", i, reverse);
      if ((i + reverse) % 2 == 1){
	
	result = i + reverse;
	resultLength = convIntToStr(str, result);
	if (checkDigits(str, resultLength) == 0)
	  sum++;
	}
      }
    }
  }
//   int *sendbuf = malloc(sizeof(int));
//   int *recbuf = malloc(size*sizeof(int));

  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Reduce(&sum, &globalsum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  start_t = clock() - start_t;
  MPI_Reduce(&start_t, &avg_t, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  
  if (rank == 0){
    printf("%d\n", globalsum);
    printf("average time taken by CPU: %2.5f\n", ((float)avg_t/CLOCKS_PER_SEC)/size  );
  }
  MPI_Finalize();

  //debug print statements
  if (rank+1 == size){
    printf("Range of elements checked by node %d: %d - %d \n", rank, (1 + ((1000000000/size) * rank)), ((1000000000/size) * (rank+1))+(1000000000%size)  );
    printf("Total time taken by CPU in node %d: %2.5f\n", rank, (float)start_t/CLOCKS_PER_SEC  );
  }
  else{
    printf("Range of elements checked by node %d: %d - %d \n", rank, (1 + ((1000000000/size) * rank)), ((1000000000/size) * (rank+1))  );
    printf("Total time taken by CPU in node %d: %2.5f\n", rank, (float)start_t/CLOCKS_PER_SEC  );
  }



  free(str);
  return 0;
}