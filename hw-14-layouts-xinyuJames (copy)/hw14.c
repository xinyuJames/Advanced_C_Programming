#include "hw14.h"

// 0->none 1->vertical 2->horizontal
void layout_helper(struct DOMNode * root, float width, float height, int dir, FILE* target)
{
  // base case: is NULL or empty

  // calculate coordinate according to parameter
  // write in file: id left_pix top_pix right_pix bottom_pix (.2f)
  // calculate children width and height
  // recursive call children, use calculated width and height
}

void layout(struct DOMNode *root, float width, float height, FILE *target) {
  // write in window width and height first...
  // use layout_helper()
}

void free_DOMTree(struct DOMNode *root) {
  // base case: is NULL or empty
  
  // recursive call children
  // free nodelist
  // free node
}
