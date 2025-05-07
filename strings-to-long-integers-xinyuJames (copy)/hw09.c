#include "hw09.h"
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stddef.h>

#define INV_SYMBOL 36

// useful static helper functions
static int char_to_int(char c);
const char *skip_whitespace(const char *ptr);

long string_to_long(const char *string, const char **endptr, int base) {
  // checking that the first argument is not null, as specified in hw09.h
  assert(string != NULL);
  // if (*endptr != NULL)
  // {
  //   *endptr = NULL;
  // }

  // setting errno to zero before function body starts
  errno = 0;
  //char issign = 0;
  //int backtrack = 0;
  char sign = '+';
  char isZero = 0;
  long ret_value = 0;

  // Check if the base provided is invalid, i.e. it is less than 2 or more than
  // 36. Remember that base 0 is valid, and you need to check the string to see
  // if it is octal or hexadecimal.
  //
  // If the base is invalid, set errno to EINVAL and return

  if (base == 0) 
  {
    isZero = 1;
  } else if (base < 2 || base > 36) 
  {
    errno = EINVAL;
    // if (endptr != NULL)
    // {
    //   *endptr = string;
    // }
    return ret_value;
  }
  //TRY: at the beginning of string
  if (endptr != NULL)
  {
    *endptr = string;
  }
  // Skip over any whitespace present

  string = skip_whitespace(string);

  // Find the sign before the start of the number, if any
  
  if (string[0] == '-') 
  {
    //issign = 1;
    if (char_to_int(string[1]) == INV_SYMBOL)
    {
      // if (endptr != NULL)
      // {
      //   *endptr = string;
      // }
      return ret_value;
    }
    string++;
    sign = '-';
  } else if (string[0] == '+') 
  {
    //issign = 1;
    if (char_to_int(string[1]) == INV_SYMBOL)
    {
      // if (endptr != NULL)
      // {
      //   *endptr = string;
      // }
      return ret_value;
    }
    string++;
  }

  //fulfill base == 16, and start with 0x or 0X
  if (base == 16)
  {
    if (string[0] == '0' && (string[1] == 'x' || string[1] == 'X')) 
    {
      string ++;
      if (char_to_int(string[1]) == INV_SYMBOL || char_to_int(string[1]) >= base)
      {
        if (endptr != NULL)
        {
          *endptr = string;
        }
        return ret_value;
      }
      string++;
    }
  }

  //fulfill base == 8, and start with 0
  //actually chilling

  //fulfill base == 0
  if (isZero)
  {
    if (string[0] == '0') 
    {
      string++;
      if (endptr != NULL)
      {
        *endptr = string;
      }
      if (string[0] == 'x' || string[0] == 'X') 
      {
        base = 16;
        if (char_to_int(string[1]) == INV_SYMBOL || char_to_int(string[1]) >= base)
        {
          if (endptr != NULL)
          {
            *endptr = string;
          }
          return ret_value;
        }
        string ++;
      } else 
      {
        base = 8;
      }
    } else
    {
      base = 10;
    }
    
  }

  //deal with 

  // Continue conversion while
  // 1) the string has not ended
  // 2) the current symbol is valid
  // 3) the current symbol is not a numeric value more than the base
  while (*string != '\0' && char_to_int(*string) != INV_SYMBOL && char_to_int(*string) < base)
  {
    int digit = char_to_int(*string);
    //check if out of range


    if (sign == '+' && ret_value > (LONG_MAX - digit) / base) 
    {
      errno = ERANGE;
      if (endptr != NULL)
      {
        while (*string != '\0' && char_to_int(*string) != INV_SYMBOL && char_to_int(*string) < base)
        {
          string++;
        }
        *endptr = string;
      }
      return LONG_MAX;
    }

    if (sign == '-' && -ret_value < (LONG_MIN + digit) / base)
    {
      errno = ERANGE;
      if (endptr != NULL)
      {
        while (*string != '\0' && -ret_value < (LONG_MIN + digit) / base)
        {
          string++;
        }
        *endptr = string;
      }
      return LONG_MIN;
    }
    //update the return value
    ret_value = ret_value * base + digit;
    string++;
    if (endptr != NULL)
    {
      *endptr = string;
    }
  }
  
  //directly after sign
  // if (issign == 1)
  // {
  //   string--;
  //   if ((string[0] == '-' || string[0] == '+') && char_to_int(string[1]) >= base)
  //   {
  //     if (endptr != NULL)
  //     {
  //       *endptr = string;
  //     }
  //     return ret_value;
  //   } else
  //   {
  //     string++;
  //   }
    
  // }


  return sign == '-' ? -ret_value : ret_value;
}

static int char_to_int(char c) {
  // what if c is '0' -- '9'
  if (isdigit(c)) {
    return c - '0';
  }

  // what if c is 'a' -- 'z'
  if (islower(c)) {
    // only deal with one alphabetic case
    c = toupper(c);
  }

  if (isupper(c)) {
    // 'A' becomes 65 - 65 + 10 = 10, 'B' becomes 11 and so on
    return c - 'A' + 10;
  }

  return INV_SYMBOL;
}

const char *skip_whitespace(const char *ptr) {
  while (isspace(*ptr)) {
    ptr++;
  }

  return ptr;
}
