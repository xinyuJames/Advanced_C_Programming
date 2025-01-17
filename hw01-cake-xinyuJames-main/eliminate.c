// ***
// *** You MUST modify this file
// ***

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <string.h> 

void eliminate(int n, int k)
{
  // allocate an arry of n elements
  int * arr = malloc(sizeof(* arr) * n);
  // check whether memory allocation succeeds.
  // if allocation fails, stop
  if (arr == NULL)
    {
      fprintf(stderr, "malloc fail\n");
      return;
    }

  // initialize all elements
  int i;
  int totNum = n;
  int eleNum = n; //number of elements
  int kickNum = k; //when to kick
  int count = 0;
  int location = 0;
  
  //init each element to their index
  for (i = 0; i < eleNum; i++)
  {
    arr[i] = i;
  }
  
  // count and mark and print
  while (eleNum > 1)
  {
    count++;
    count %= kickNum;

    if (count == 0)
    {
      printf("%d\n", arr[location]);
      arr[location] = -1;
      eleNum--;
    }

    location++;
    location %= totNum;
    while (arr[location] == -1)
    {
      location++;
      location %= totNum;
    }
    
  }

  // print the last remaining index
  printf("%d\n", arr[location]);

  // release the memory of the array
  free (arr);
}

