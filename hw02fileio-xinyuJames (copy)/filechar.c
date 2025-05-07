#include <stdio.h>
#include <stdbool.h>


bool countChar(char * filename, int * counts, int size)
{
  // open a file whose name is filename for reading
  // if fopen fails, return false. Do NOT fclose
  // if fopen succeeds, read every character from the file
  //
  // if a character (call it onechar) is between
  // 0 and size - 1 (inclusive), increase
  // counts[onechar] by one
  // You should *NOT* assume that size is 256
  // reemember to call fclose
  // you may assume that counts already initialized to zero
  // size is the size of counts
  // you may assume that counts has enough memory space
  //
  // hint: use fgetc
  // Please read the document of fgetc carefully, in particular
  // when reaching the end of the file
  //

  FILE * fptr;
  fptr = fopen(filename, "r");

  if (fptr == NULL)
  {
    return false;
  }

  int ch;

  while ((ch = fgetc(fptr)) != EOF)
  {
    if (ch >= size)
    {
      continue;
    } else
    {
      counts[ch]++;
    }

  }


  fclose(fptr);
  return true;
}


void printCounts(int * counts, int size)
{
  // print the values in counts in the following format
  // each line has three items:
  // ind, onechar, counts[ind]
  // ind is between 0 and size - 1 (inclusive)
  // onechar is printed if ind is between 'a' and 'z' or
  // 'A' and 'Z'. Otherwise, print space
  // if counts[ind] is zero, do not print
  int i;
  char ch;
  for (i = 0; i < size; i++)
  {
    
    if ('A' <= i && i <= 'z')
    {
      ch = (char) i;
    } else
    {
      ch = ' ';
    }

    if (counts[i] == 0)
    {
      continue;
    } else
    {
      printf("%d, %c, %d\n",i, ch, counts[i]);
    }
  }

  // int count;
  // count = 0;
  // for (i = 0; i < size; i++)
  // {
  //   if (counts[i] == 0)
  //   {
  //   } else
  //   {
  //     count++;
  //   }
  // }
  
  // printf("%d\n",count);
  
}
