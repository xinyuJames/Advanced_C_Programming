#include "hw09.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

// suggested testing function declaration
static void check_string_to_long(const char *string);

int main(int argc, char **argv)
{
  errno = 0;
  // const char* endptr;
  fprintf(stderr, "Welcome to ECE264, we are working on HW09!\n\n");

  // test here
  // two error
  printf("Test 1\n");
  check_string_to_long("12345678");
  printf("Test 2\n");
  check_string_to_long("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
  // about base 16
  printf("Test 17\n");
  check_string_to_long("0xfff3");
  printf("Test 17.5\n");
  check_string_to_long("0xz");
  printf("Test 17.6\n");
  check_string_to_long("0x");
  printf("Test 17.7\n");
  check_string_to_long("0x ");
  // printf("Test 17.8\n");
  // check_string_to_long("0");
  // about sign
  printf("Test 18\n");
  check_string_to_long("+     -334234");
  printf("Test 18.1\n");
  check_string_to_long("+0xfff3");
  printf("Test 18.5\n");
  check_string_to_long("+     - 334234");
  printf("Test 18.6\n"); //TODO: fix this
  check_string_to_long(" +      334234");
  printf("Test 18.7\n");
  check_string_to_long("+      334234");
  printf("Test 18.8\n");
  check_string_to_long("+zz");
  printf("Test 18.9\n");
  check_string_to_long("-0xzz");
  check_string_to_long("-0xzz");
  // printf("Test 18.10\n");
  // check_string_to_long("-0z");
  printf("Test 18.11\n");
  check_string_to_long("-z");
  // about base 8
  printf("Test 19\n");
  check_string_to_long("07773");
  // printf("Test 19.5\n");
  check_string_to_long("0z");
  // printf("Test 19.6\n");
  check_string_to_long("0");
  // printf("Test 19.7\n");
  check_string_to_long("0 ");
  printf("Test 19.8\n");
  check_string_to_long("0 12 3");
  printf("Test 19.9\n");
  check_string_to_long("-0000000008     ");
  printf("Test 20\n");
  check_string_to_long("-");
  printf("Test 21\n");
  check_string_to_long("+");
  printf("Test 21.1\n");
  check_string_to_long("-0xaz");
  // other fail
  // printf("Test 21.9\n");
  // check_string_to_long("\t\t\n\n-0000008000000000000000\t\t\n\n");
  // printf("Test 22\n");
  // check_string_to_long("AAF");
  // printf("Test 22.1\n");
  // check_string_to_long("-0xzzzzzzzzzzzzzz");
  // printf("Test 22.2\n");
  // check_string_to_long("-0000000008     ");
  // printf("Test 22.3\n");
  // check_string_to_long("+-2342349723479zzzzfsdf     ");
  // printf("Test 22.4\n");
  // check_string_to_long(",,");
  // printf("Test 22.5\n");
  // check_string_to_long("!@^#%!&#@%");
  // printf("Test 22.6\n");
  // check_string_to_long("asdl3234!!!94");
  // printf("Test 22.7\n"); //TODO: fix this
  // check_string_to_long(" -345345aa+  ");
  printf("Test 22.8\n");
  check_string_to_long("-345345aa+  ");
  check_string_to_long("-!@#");
  check_string_to_long("-zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
  return EXIT_SUCCESS;
}

static void check_string_to_long(const char *string)
{
  // error detect init
  errno = 0;
  char isERANGE = 0;
  char isEINVAL = 0;
  const char *testendptr = NULL;
  char *expectedendptr = NULL;
  int base;
  for (base = -5; base < 50; base++)
  {
    printf("Base: %d\n", base);
    errno = 0;
    isERANGE = 0;
    isEINVAL = 0;
    // test const init
    testendptr = NULL;
    expectedendptr = NULL;
    // set test and expected value and catch errors
    long test = string_to_long(string, &testendptr, base);
    if (errno == ERANGE)
    {
      isERANGE = 1;
      errno = 0;
    }
    else if (errno == EINVAL)
    {
      isEINVAL = 1;
      errno = 0;
    }

    long expected = strtol(string, &expectedendptr, base);
    if (errno == ERANGE)
    {
      if (isERANGE == 1)
      {
        printf("%s\n", "ERANGE Pass\n");
      }
      else
      {
        printf("%s\n", "ERANGE Fail\n");
      }

      if (testendptr == expectedendptr)
      {
        printf("%s\n", "Endptr Pass");
      }
      else
      {
        printf("%s\n", "Endptr Fail");
        printf("Expected: %s ; value: %c\n", expectedendptr, *expectedendptr);
        printf("Test: %s ; value: %c\n", testendptr, *testendptr);
      }
      errno = 0;
      continue;
    }
    else if (errno == EINVAL)
    {
      if (isEINVAL == 1)
      {
        printf("%s\n", "EINVAL Pass\n");
      }
      else
      {
        printf("%s\n", "EINVAL Fail\n");
      }
      errno = 0;
      continue;
    }
    // compare value and endptr
    if (test == expected)
    {
      printf("%s\n", "Return Value Pass");
      // printf("Expected: %ld\n", expected);
      // printf("Test: %ld\n", test);
    }
    else
    {
      printf("%s\n", "Return Value Fail");
    }

    if (testendptr == expectedendptr)
    {
      printf("%s\n", "Endptr Pass");
      printf("Expected: %s ; value: %c\n", expectedendptr, *expectedendptr);
      printf("Test: %s ; value: %c\n", testendptr, *testendptr);
    }
    else
    {
      printf("%s\n", "Endptr Fail");
      printf("Expected: %s ; value: %c\n", expectedendptr, *expectedendptr);
      printf("Test: %s ; value: %c\n", testendptr, *testendptr);
    }

    printf("\n");
  
  }
  
}
