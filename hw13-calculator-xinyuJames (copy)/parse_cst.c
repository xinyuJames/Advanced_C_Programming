#include "cst.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void free_expr(struct CST_node *cst);
void free_term(struct CST_node *cst);
void free_expr_rest(struct CST_node *cst);
void free_factor(struct CST_node *cst);
void free_term_rest(struct CST_node *cst);
int token_to_literal(struct token token_literal);

struct CST_node *parse_expr(struct stream *s)
{
    //printf("Start expr\n");
    // use parse_term() and parse_expr_rest() to *s, and return combined result
    struct CST_node* term = parse_term(s);

    if (term == NULL)
    {
        return NULL;

    }
    struct CST_node* expr_rest = parse_expr_rest(s);
    if (expr_rest == NULL)
    {
        free_cst(term);
    }
    // TODO: supposing expr_rest could return null
    // TODO: for all return NULL -> free up specific TYPE!!

    struct CST_node* expr_node = malloc(sizeof(struct CST_node));
    expr_node->type = NODE_EXPR;
    expr_node->expr.expr_rest = expr_rest;
    expr_node->expr.term = term;
    //printf("Finish expr\n");

    return expr_node;
}

struct CST_node *parse_expr_rest(struct stream *s)
{
    //printf("Start expr_rest\n");
    struct CST_node* node_expr_rest = malloc(sizeof(struct CST_node));
    node_expr_rest->type = NODE_EXPR_REST;
    struct token token_term_rest = peek(s);

    // + expr
    if (token_term_rest.type == TOK_ADD)
    {
        next(s); // return +
        node_expr_rest->expr_rest.op = '+';
        node_expr_rest->expr_rest.expr = parse_expr(s);
    } else
    { // {}
        //printf("expr_rest {} case\n");
        node_expr_rest->expr_rest.expr = NULL;
        //node_expr_rest->expr_rest.op = ' ';
    }

    return node_expr_rest;
}

struct CST_node *parse_term(struct stream *s)
{
    //printf("Start term\n");
    // parse_factor() and parse_term_rest(), if not NULL, return combined term
    struct CST_node* factor = parse_factor(s);

    if (factor == NULL)
    {
        return NULL;
    }

    struct CST_node* term_rest = parse_term_rest(s);

    if (term_rest == NULL)
    {
	    free_cst(factor);
	    return NULL;
    }
    struct CST_node* term_node = malloc(sizeof(struct CST_node));
    term_node->type = NODE_TERM;
    term_node->term.factor = factor;
    term_node->term.term_rest = term_rest;

    return term_node;

}

struct CST_node *parse_term_rest(struct stream *s)
{
    struct CST_node* node_term_rest = malloc(sizeof(struct CST_node));
    node_term_rest->type = NODE_TERM_REST;
    struct token token_term_rest = peek(s);

    // * term
    if (token_term_rest.type == TOK_MUL)
    {
        node_term_rest->term_rest.op = '*';
        next(s); // return *
        node_term_rest->term_rest.term = parse_term(s);
    } else
    { // {}
        //node_term_rest->term_rest.op = NULL;
        node_term_rest->term_rest.term = NULL;
    }

    return node_term_rest;
}

struct CST_node *parse_factor(struct stream *s)
{
    //printf("Start factor -> ");
    struct CST_node* node_factor = malloc(sizeof(struct CST_node));
    node_factor->type = NODE_FACTOR;
    node_factor->factor.expr = NULL;
    node_factor->factor.literal = 0;
    node_factor->factor.negated = false;
    struct token token_factor = peek(s);
    
    // literal case
    if (token_factor.type == TOK_LITERAL)
    {
        node_factor->factor.expr = NULL;
        //printf("Start parsing literal\n");
        node_factor->factor.literal = token_to_literal(token_factor);
        node_factor->factor.negated = false;
        //printf("Literal: %d\n", node_factor->factor.literal);
        next(s);
    }

    // (expr) case
    else if (token_factor.type == TOK_LPAREN)
    {
        next(s); // return (

        //node_factor->factor.literal = NULL; // set literal to NULL
        node_factor->factor.expr = parse_expr(s);
        node_factor->factor.negated = false;
        struct token token_next_one = peek(s); // next token need to be )
        if (token_next_one.type != TOK_RPAREN)
        {
            // if not )
            free_cst(node_factor);
	        return NULL;
        } else
        {
            next(s); // return )
        }
    }

    // negative sign case
    else if (token_factor.type == TOK_NEG)
    {
        next(s); // return -

       	// free up the original malloc
	    free_cst(node_factor);
        node_factor = parse_factor(s);
        node_factor->factor.negated = true; 
    } else
    {
	    free_cst(node_factor);
        return NULL;
    }

    return node_factor;
}

// FREE CST
void free_expr(struct CST_node *cst)
{
    //printf("Free expr\n");
    if (cst->expr.term != NULL)
    {
        free_term(cst->expr.term);
    }
    
    if (cst->expr.expr_rest != NULL)
    {
        free_expr_rest(cst->expr.expr_rest);
    }

    free(cst);
    cst = NULL;
}

void free_term(struct CST_node *cst)
{
    //printf("Free term\n");
    if (cst->term.factor != NULL)
    {
        free_factor(cst->term.factor);
    }
    
    if (cst->term.term_rest != NULL)
    {
        free_term_rest(cst->term.term_rest);
    }
    free(cst);
    cst = NULL;
}

void free_expr_rest(struct CST_node *cst)
{
    //printf("Free expr_rest\n");
    if (cst->expr_rest.expr != NULL)
    {
        free_expr(cst->expr_rest.expr);
    }
    free(cst);
    cst = NULL;
}

void free_factor(struct CST_node *cst)
{
    //printf("Free factor\n");
    if (cst->factor.expr != NULL)
    {
        free_expr(cst->factor.expr);
    }
    free(cst);
    cst = NULL;
}

void free_term_rest(struct CST_node *cst)
{
    //printf("Free term_rest\n");
    if (cst->term_rest.term != NULL)
    {
        free_term(cst->term_rest.term);
    }
    free(cst);
    cst = NULL;
}

void free_cst(struct CST_node *cst)
{
    if (cst == NULL)
    {
        return;
    }

    switch (cst->type)
    {
    case NODE_EXPR:
        free_expr(cst);
        break;
    
    case NODE_EXPR_REST:
        free_expr_rest(cst);
        break;

    case NODE_FACTOR:
        free_factor(cst);
        break;

    case NODE_TERM:
        free_term(cst);
        break;

    case NODE_TERM_REST:
        free_term_rest(cst);
        break;
    }
}
// FREE END

// convert literal token to int
int token_to_literal(struct token token_literal)
{
    int rtn_val;

    // check if valid first
    if (token_literal.type != TOK_LITERAL || token_literal.start == NULL)
    {
        return 0;
    }

    char buffer[32];

    // the literal is too long
    if (token_literal.length >= sizeof(buffer))
    {
        //printf("Literal too long\n");
        return 0;
    }

    memcpy(buffer, token_literal.start, token_literal.length);
    buffer[token_literal.length] = '\0';

    char *endptr;
    rtn_val = strtol(buffer, &endptr, 10);

    // if buffer is not totally literal
    // if (endptr == buffer || *endptr != '\0')
    // {
    //     printf("Not totally literal\n");
    //     return 0;
    // }

    return rtn_val;
}
