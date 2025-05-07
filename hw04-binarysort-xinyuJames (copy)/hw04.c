#include <stdlib.h>
#include <stdio.h>
#include "hw04.h"

/* The first function you write counts the numbers of vectors
(that is, the number of triads of 32-bit integers) found in the
file with name 'filename'.  It assigns this value to the location
pointed to by 'vector_count'.  If it is unable to open the file,
OR if the file cannot be interpreted as a binary file of vectors
(that is, it does not contain a multiple of three integers' worth of data), it returns
EXIT_FAILURE.  Else, it returns EXIT_SUCCESS.  */
int count_vectors_in_file(char * filename, int * vector_count) {
    // Open the file in "rb" (read binary) mode
    FILE* fptr;
    fptr = fopen(filename, "rb");

    if (fptr == NULL)
    {
        return EXIT_FAILURE;
    }
    // Set up a buffer of three integers to read to,
    // a count of how many integers are read in on the last pass,
    // and a count of how many times three integers have been read in
    int buffer[3];
    int numIn = 0;
    *vector_count = 0;
    while ((numIn = (fread(buffer, sizeof(int), 3, fptr))) == 3)
    {
        (*vector_count)++;
    }

    if (!feof(fptr) || numIn != 0)
    {
        fclose(fptr);
        return EXIT_FAILURE;
    }

    //printf("%d\n", *vector_count);
    fclose(fptr);

    // While not encountering the end of the file or receiving an error,
    // call f_read with the buffer to retrieve three integers.  Update
    // the counts.
    // If the last pass reached the end of the file and retrieved no integers
    // (rather than a stray one or two) and didn't throw an error, return EXIT_SUCCESS
    // Else, return EXIT_FAILURE
    return EXIT_SUCCESS;
}

/* The second function you write allocates space for the vectors
counted before - there are vector_count vectors stored in the file at
filename.  It reads in those vector_count vectors from the file 'filename'
to the space it allocates and returns a pointer to that space.

That space will need to be freed - though, of course, not before
the program is done using it.  Free it in an appropriate place (hint: not in this function.)

In the event of a file read failure or memory allocation failure (both
are unlikely), you can return NULL.*/
struct vector * read_vectors_from_file(char * filename, int vector_count) {
    // Open the file in "rb" (read binary) mode
    FILE* fptr;
    fptr = fopen(filename, "rb");

    if (fptr == NULL)
    {
        return NULL;
    }
    // Allocate sufficient space for all of the vector structs
    struct vector* buffer = (struct vector*) malloc(vector_count * sizeof(struct vector));
    int intBuffer[3];

    int index = 0;
    while (vector_count--)
    {
        if (fread(intBuffer, sizeof(int), 3, fptr) != 3)
        {
            fclose(fptr);
            free(buffer);
            return NULL;
        }
        buffer[index].x = intBuffer[0];
        buffer[index].y = intBuffer[1];
        buffer[index].z = intBuffer[2];
        index++;
    }
    fclose(fptr);

    //remember to free buffer
    return buffer;

    // Read in all the integers from the file.  Place each
    // set into the x-, y-, and z-coordinates of a vector in the list

    // Return the list of vectors
}

/* The third function you write takes in two pointers of type
const void*, casts them to access the attributes of the 
structs to which they point, and returns a positive value if the
first is greater, a negative value if the second is greater,
and 0 if they are equal.  Being greater is determined by the 
x-coordinate's being greater, or, those being equal, by the
y-coordinate's being greater, or, those also being equal, by 
the z-coordinate's being greater.

This function is meant to be sent to qsort - see 
https://en.cppreference.com/w/c/algorithm/qsort for an example
of using qsort and a warning about comparison functions.*/
int compare_vectors(const void* a, const void* b) {
    struct vector *vector1 = (struct vector *) a;
    struct vector *vector2 = (struct vector *) b;
    long long difference;

    difference = (long long) (vector1->x) - (long long) (vector2->x);
    if (difference > 0) return 1;
    if (difference < 0) return -1;

    difference = (long long) (vector1->y) - (long long) (vector2->y);
    if (difference > 0) return 1;
    if (difference < 0) return -1;

    difference = (long long) (vector1->z) - (long long) (vector2->z);
    if (difference > 0) return 1;
    if (difference < 0) return -1;

    return 0;

}

/* The fourth function calls qsort with the appropriate
parameters, including the function above. */
void call_qsort(struct vector * vector_list, int vector_count) {
    qsort(vector_list, vector_count, sizeof(struct vector), compare_vectors);
}

/* The fifth function writes the vectors in 'vector_list' (which
has length 'vector_count') to a binary file at 'filename'.  If the
file cannot be opened, it returns EXIT_FAILURE. */
int write_vectors_to_file(char * filename, struct vector * vector_list, int vector_count) {
    // Open the file in "wb" (write binary) mode
    FILE* fptr;
    fptr = fopen(filename, "wb");

    if (fptr == NULL)
    {
        return EXIT_FAILURE;

    }
    // Write the coordinates of each vector to the binary file

    if (fwrite(vector_list, sizeof(struct vector), vector_count, fptr) != vector_count)
    {
        fclose(fptr);
        free(vector_list);
        return EXIT_FAILURE;
    }
    
    fclose(fptr);
    free(vector_list);
    return EXIT_SUCCESS;
}