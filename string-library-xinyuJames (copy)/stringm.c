/*
** -----------------------------------------------------------------
** IMPORTANT NOTE: For this assignment, you are not allowed to use
** string.h or any header file other than what is defined below
** -----------------------------------------------------------------
*/
#include "stringm.h"

/*
** strlen_m calculates the length of a string
** const char *string - string to calculate length of
** return the size of the string
**
** note: you can assume string is not NULL
*/
size_t strlen_m(const char *string)
{
    int count = 0;
    while (string[count] != '\0')
    {
        count++;
    }
    return count;
}

/*
** strncpy_m copies n characters of string and returns it
** const char *string - string to copy
** size_t n - number of characters to copy (not including null character)
** return a copy of first n characters of string
**
** note: you can assume string is not NULL
** hint: you will need to malloc a size n + 1 string to accomodate the null character
*/
char *strncpy_m(const char *string, size_t n)
{
    char* cystring = (char*) malloc(n + 1);
    if (cystring == NULL)
    {
        return NULL;
    }

    size_t strlen = strlen_m(string);
    int i;

    if (strlen < n)
    {
        for (i = 0; i < strlen; i++)
        {
            cystring[i] = string[i];
        }
        cystring[i+1] = '\0';
    } else
    {
        for (i = 0; i < n; i++)
        {
            cystring[i] = string[i];
        }
        cystring[n] = '\0';
    }

    return cystring;
}

/*
** join_m joins an array of strings separated by a delimiter
** Strings strings - structure that stores an array of strings
** const char *delimiter - delimiter string which joins each string
** return the string created by joining all strings with the delimiter
**
** note: you can assume delimiter is not NULL
** hint: return NULL if strings.num_strings is 0
*/
char *join_m(Strings strings, const char *delimiter)
{
    int i;
    size_t totsize = 0;

    if (strings.num_strings == 0)
    {
        return NULL;
    }

    for (i = 0; i < strings.num_strings; i++)
    {
        totsize += strlen_m(strings.strings[i]);
    }

    totsize += strlen_m(delimiter) * (strings.num_strings - 1);
    
    char* joinstrs;
    joinstrs = (char*) malloc(totsize + 1);
    if (joinstrs == NULL)
    {
        return NULL;
    }

    int j;
    int pos = 0;
    for (i = 0; i < 2 * strings.num_strings - 1; i++)
    {
        if (i % 2 == 0)
        {
            for (j = 0; j < strlen_m(strings.strings[i/2]); j++)
            {
                joinstrs[pos] = strings.strings[i/2][j];
                pos++;
            }
        } else
        {
            for (j = 0; j < strlen_m(delimiter); j++)
            {
                joinstrs[pos] = delimiter[j];
                pos++;
            }
        }
    }
    joinstrs[pos] = '\0';
    return joinstrs;


}

/*
** free_strings frees all allocated elements in strings
** String strings - free each string in strings.strings and strings.strings itself
*/
void free_strings(Strings strings)
{
    int i;
    for (i = 0; i < strings.num_strings; i++)
    {
        free(strings.strings[i]);
    }
    free(strings.strings);
}

/*
** split_m splits a string at any occurence of pattern
** const char *string - string that is searched for the pattern
** const char *pattern - pattern which string should be split
** return a String structure which contains an array of each string
**
** note: you may assume string and pattern are not NULL
** hint 1: TA solution uses strlen_m, strstr_m, and strncpy_m
** hint 2: first calculate how many strings are needed, which is: 
**         (the number of times the delimiter appears + 1)
** hint 3: when trying to store a substring, think about how the length of 
**         that substring might be calculated in terms of pointer arithmetic
**         - what is the outcome of adding or subtract pointers?
** hint 3.5: strstr_m will return a pointer to the first character of the next occurence 
**           or NULL if not found
**          
*/
Strings split_m(const char *string, const char *pattern)
{
    Strings result = { .num_strings = 0, .strings = NULL };
    size_t matchcount = 0;
    //length of string and pattern
    size_t strlen = strlen_m(string);
    size_t patternlen = strlen_m(pattern);
    //have two pointers point to beginning of string
    const char* backupstr = string;
    const char* countmatchstr = string;
    size_t i;

    if (patternlen == 0)
    {
        result.num_strings = 1;
        result.strings = malloc(sizeof(char*) * 1);
        result.strings[0] = strncpy_m(string, strlen);
        return result;
    }
    //to count how many matches
    while ((countmatchstr = strstr_m(countmatchstr, pattern)) != NULL)
    {
        matchcount++;
        countmatchstr += patternlen;
    }
    //to get len for each segment of match
    size_t* len_arr = malloc((matchcount + 1) * sizeof(size_t));
    if (len_arr == NULL)
    {
        free(len_arr);
        return result;
    }

    size_t lenleft;
    for (i = 0; i < matchcount; i++)
    {
        lenleft = strlen_m(backupstr);
        backupstr = strstr_m(backupstr, pattern);
        len_arr[i] = lenleft - strlen_m(backupstr);
        backupstr += patternlen;
    }
    len_arr[matchcount] = strlen_m(backupstr);

    result.num_strings = matchcount+1;
    result.strings = malloc((matchcount + 1) * sizeof(char*));
    for (i = 0; i < matchcount + 1; i++)
    {
        result.strings[i] = strncpy_m(string, len_arr[i]);
        string += len_arr[i];
        if (i < matchcount)
        {
            string += patternlen;
        }
    }

    free(len_arr);

    return result;



}

/*
** find_and_replace_all_m finds each occurence of the pattern in the string and replaces it
** const char *string - string to search through
** const char *pattern - pattern to search for in the string
** const char *replacement - replacement string for each occurence of the pattern in the string
** return a string in which every occurence of pattern is replaced replacement
**
** note: you may assume string, pattern, and replacement are all not NULL
** hint: there are two main ways of implementing this function, one involves many lines, one involves four
*/
char *find_and_replace_all_m(const char *string, const char *pattern, const char *replacement)
{
    Strings strsplit = split_m(string, pattern);
    char* result = join_m(strsplit, replacement);
    free_strings(strsplit);
    return result;

}

/*
** The strstr function is implemented for you to use -- DO NOT MODIFY
** If you are curious about the algorithm used, look up the Knuth-Morris-Pratt (KMP)
** algorithm that can find a substring inside another string 'blazingly fast'
*/
const char *strstr_m(const char *haystack, const char *needle)
{
    size_t haystack_len = 0, needle_len = 0;
    for (const char *h = haystack; *h; h++)
        haystack_len++;
    for (const char *n = needle; *n; n++)
        needle_len++;

    if (needle_len > haystack_len)
        return NULL;

    char *lps_str = malloc(haystack_len + needle_len + 1);
    size_t i = 0;
    for (const char *n = needle; *n; n++, i++)
        lps_str[i] = *n;
    lps_str[i++] = '\1';
    for (const char *h = haystack; *h; h++, i++)
        lps_str[i] = *h;

    int *lps_arr = calloc((haystack_len + needle_len + 1), sizeof *lps_arr);
    size_t l = 0, r = 1;
    bool success = false;

    while (r < haystack_len + needle_len + 1)
    {
        if (lps_str[l] == lps_str[r])
        {
            l++;
            lps_arr[r] = l;
            r++;
        }
        else if (l)
            l = lps_arr[l - 1];
        else
        {
            lps_arr[r] = 0;
            r++;
        }

        if (l == needle_len)
        {
            success = true;
            break;
        }
    }

    free(lps_arr);
    free(lps_str);
    if (success)
        return haystack + (r - l - needle_len - 1);
    return NULL;
}
