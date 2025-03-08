#include "answer.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    // prints out the students section
    // this message prints out on Gradescope too
    printf("Section: %d\n", get_section());
    return EXIT_SUCCESS;
}