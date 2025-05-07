#include "tree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

    if (argc != 3)
    {
        printf("Need 2 Arguments");
        return EXIT_FAILURE;
    }

    Tree* tree_read = read_from_file(argv[1]);
    Tree* tree_inv = invert_tree(tree_read);
    preorder_print(tree_inv, argv[2]);
    free_tree(tree_read);
    free_tree(tree_inv);

    return 0;
}
