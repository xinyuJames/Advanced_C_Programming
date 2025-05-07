#include "hw08.h"

#include <string.h>

/**
 * Grammar:
 *
 * expr := term expr_rest
 * expr_rest := '+' expr | '-' expr | {}
 *
 * term := factor term_rest
 * term_rest = '*' term | {}
 *
 * factor := int | '(' expr ')'
 */

#ifndef INSTRUCTOR_EXPR
enum parse_result parse_expr(struct stream *s) 
{ 
  if (parse_term(s) == PARSE_FAILURE)
  {
    return PARSE_FAILURE;
  }

  if (parse_expr_rest(s) == PARSE_FAILURE)
  {
    return PARSE_FAILURE;
  }

  return PARSE_SUCCESS; 
}

// expr_rest := '+' expr | '-' expr | {}
enum parse_result parse_expr_rest(struct stream *s) 
{ 
  struct token nextTK = peek(s);

  if (nextTK.type == TOK_BINOP)
  {
    if (nextTK.start[0] == '+' || nextTK.start[0] == '-')
    {
      next(s);
      if (parse_expr(s) == PARSE_FAILURE)
      {
        //printf("%s\n", "expr test fail 1");
        return PARSE_FAILURE;
      }
      return PARSE_SUCCESS;
    } else
    {
      //printf("%s\n", "expr test fail 2");
      return PARSE_FAILURE;
    }
  }

  return PARSE_SUCCESS; 
}
#endif

#ifndef INSTRUCTOR_TERM
// term := factor term_rest
enum parse_result parse_term(struct stream *s) 
{
  if (parse_factor(s) == PARSE_FAILURE)
  {
    //printf("%s\n", "term fail 1");
    return PARSE_FAILURE;
  }

  if (parse_term_rest(s) == PARSE_FAILURE)
  {
    //printf("%s\n", "term fail 2");
    return PARSE_FAILURE;
  }

  return PARSE_SUCCESS; 
}

// term_rest = '*' term | {}
enum parse_result parse_term_rest(struct stream *s) 
{
  struct token nextTK = peek(s);
  if (nextTK.type == TOK_BINOP)
  {

    if (nextTK.start[0] == '*')
    {
      next(s);
      if (parse_term(s) == PARSE_FAILURE)
      {
        //printf("%s\n", "term rest fail");
        return PARSE_FAILURE;
      }
      return PARSE_SUCCESS;
    }
    
  }
  
  return PARSE_SUCCESS; 

}
#endif

#ifndef INSTRUCTOR_FACTOR
// factor := int | '(' expr ')'
enum parse_result parse_factor(struct stream *s) 
{ 
  struct token nextTK = peek(s);
  if (nextTK.type == TOK_LITERAL)
  {
    next(s);
    //printf("%s\n", "factor success 1");
    return PARSE_SUCCESS;
  }

  if (nextTK.type == TOK_LPAREN)
  {
    next(s);
    if (parse_expr(s) == PARSE_FAILURE)
    {
      //printf("%s\n", "factor fail 1");
      return PARSE_FAILURE;
    }

    struct token afterTK = peek(s);

    if (afterTK.type == TOK_RPAREN)
    {
      next(s);
      //printf("%s\n", "factor success 2");
      return PARSE_SUCCESS;
    }
  }
  //printf("%s\n", "factor fail 2");
  return PARSE_FAILURE; 
}
#endif

// You do NOT need to modify this function!
enum parse_result is_valid_expr(const char *expr) {
  // Create the stream
  struct stream s = {.text = expr, .pos = 0, .length = strlen(expr)};

  // Try to parse an expr and make sure there's nothing left to parse
  if (parse_expr(&s) == PARSE_SUCCESS && next(&s).type == TOK_EOF) {
    return PARSE_SUCCESS;
  }
  return PARSE_FAILURE;
}