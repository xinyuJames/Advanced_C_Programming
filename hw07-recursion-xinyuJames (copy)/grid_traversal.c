#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grid_traversal.h"

char** read_grid_from_file(const char* filename, int* rows, int* cols) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error opening file");
        return NULL;
    }

    fscanf(file, "%d %d", rows, cols);


    char** grid; 
    
    // Allocate memory for the grid here with the correct dimensions
    grid = (char**) malloc(*rows * sizeof(char*));
    for (int i = 0; i < *rows; i++)
    {
        grid[i] = (char*) malloc(*cols * sizeof(char));
    }

    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            fscanf(file, " %c", &grid[i][j]);
        }
    }

    fclose(file);
    return grid;
}

void free_grid(char **grid, int rows) {
    
    int i;
    for (i = 0; i < rows; i++) 
    {
        free(grid[i]);
    }
    free(grid);
}


bool lexicographically_smallest_path_util(char **grid, int rows, int cols, int x, int y, char* path, int pos) {
    //mark visited as '/'
    // First write your base case : If the destination is reached return an appriopriate value
    //printf("info: %d %d\n",x,y);

    if (grid[x][y] == 'e')
    {
        //printf("%s\n", "End Reach");
        path[pos] = '\0';
        return 1;
    } else
    {
        //printf("%s\n", "Mark visited");
        grid[x][y] = '/';
        //marked as visited
    }

    //try move right
    char moved = 0;
    
    if (y + 1 < cols)
    {
        //printf("Right condition: %c\n", grid[x][y+1]);
        if (grid[x][y+1] != '/' && grid[x][y+1] != '#' )
        {
            //printf("%s\n", "Move right");
            y++;
            moved = 1;
            path[pos] = 'e';
            pos++;

        }
    }
    //try move down
    if (x + 1 < rows && !moved)
    {
        //printf("Down condition: %c\n", grid[x+1][y]);
        if (grid[x+1][y] != '/' && grid[x+1][y] != '#')
        {
            //printf("%s\n", "Move down");
            x++;
            moved = 1;
            path[pos] = 's';
            pos++;
        }
    }
    //if not moved, backtrack 1 step
    if (!moved)
    {
        //printf("%s\n", "backtrack");
        //if stuck at origin
        if (x == 0 && y == 0)
        {
            return 0;
        }

        if (path[pos - 1] == 's')
        {
            //if last step move down
            x--;
            pos--;
            
        } else
        {
            //if move right
            y--;
            pos--;
            
        }
    }
    // printf("x, y after iteration: %d %d\n",x,y);
    // printf("%s\n\n", "end of one iteration");
    return lexicographically_smallest_path_util(grid, rows, cols, x, y, path, pos);

    

    // Implement the recursive step here.
    
    /*
    Below is the description of this function from the readme. You should think about how to implement this logic.

    This function uses recursion to find the lexicographically smallest path 
    from the START cell to the END cell, and print the path as a sequence of moves. 
    Only moves to the right (East) and down (South) are allowed. 
    Since we are travelling from the upper leftmost square to the lower rightmost 
    square and we can only move south or east, any valid path will have the 
    same number of south and east moves regardless of obstacles in the grid. Thus, 
    the lexicographical smallest path is the valid path where we always move east when 
    we can, and move south only when we have to. Thus, using recursion, you need to find 
    the path where you move east until you cannot move east anymore (because of an obstacle 
    or because you reached the boudanries of your grid), then move south just enoough until 
    you can move east again (if you can), until you reach the END square. 
    */

    /* Hint :
    You should first check if you can move east, then check if you can move south.
    If a path in invalid because of an obstacle, you should cancel this path.
    Cancelling the path is equivalent to cancelling the last move you made, 
    or cancelling the last 2 moves, or 3... etc, as many as you need. This is called backtracking.
    */
   
    //add \0 at the back of path
    // If no path is valid, return appropriate value (think about what would be 
    // useful for`lexicographically_smallest_path` to know when no path is found)
}



void lexicographically_smallest_path(char **grid, int rows, int cols) {
    // Initialize an array of characters of size 100 to store the path
    char* path = (char*) malloc(100);
    // Intialize a position tracker to append characters to the path correctly
    int pos = 0;
    // Make sure the START and the END squares are in the grid. If they are not print NA and return
    SquareType type = START;
    if (grid[0][0] != type)
    {
        printf("%s", "NA");
        return;
    }
    
    int i, j;
    char isEnd = 0;
    type = END;
    for (i = 0; i < rows; i++)
    {
        if (isEnd)
        {
            continue;
        }
        for (j = 0; j < cols; j++)
        {
            if (grid[i][j] == type)
            {
                isEnd = 1;
                continue;
            }
        }
    }

    if (!isEnd)
    {
        printf("%s", "NA");
        return;
    }


    // Call the utility function `lexicographically_smallest_path_util` with the correct parameters 
    // You can either look for the START square or hardcode it since we always start from the top left corner
    char isValid = lexicographically_smallest_path_util(grid, rows, cols, 0, 0, path, pos);
    // Check if the utility function found a path, and print the path if it did
    // If no path is found, print -1
    // Reminder for printing : To use printf("%s", ...) to print an array of characters in C, 
    // you need to add a null character at the end of the array to make it a string
    if (isValid)
    {
        printf("%s", path);
        free(path);
    } else
    {
        printf("%d", -1);
        free(path);
        return;
    }
}
