#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
int main()
{
	char *num1endptr = NULL;
	char *num2endptr = NULL;

	long num1 = strtol(" +      334234", &num1endptr ,0);
	long num2 = strtol("+      334234", &num2endptr, 0);

	printf("num1: %p, and value is: %c\n", (void *) num1endptr, *num1endptr);
	printf("num2: %p, and value is: %c\n", (void *) num2endptr, *num2endptr);
	
	num1endptr = NULL;
	num2endptr = NULL;
	
	errno = 0;
	num1 = strtol("-0z", &num1endptr ,0);
	//num2 = strtol("\n\t-0000008000000000000000\n\t", &num2endptr, 10);

	printf("num1: %ld, and value is: %d\n", num1, *num1endptr);
	//printf("num2: %ld, and value is: %d\n", num2, *num2endptr);
	printf("errno: %d\n", errno);

	num1endptr = NULL;
	num2endptr = NULL;

	num1 = strtol("     +zz", &num1endptr ,16); //either at tthe end of white space or at the beginning of string
	num2 = strtol("+zz", &num2endptr, 16);

	printf("num1: %p, and value is: %c\n", (void *) num1endptr, *num1endptr);
	printf("num2: %p, and value is: %c\n", (void *) num2endptr, *num2endptr);

	return 0;
}

