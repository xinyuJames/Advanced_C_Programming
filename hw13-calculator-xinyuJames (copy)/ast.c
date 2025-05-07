#include "ast.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

struct AST_node *to_ast_expr(struct CST_node *cst);
struct AST_node *to_ast_term(struct CST_node *cst);
struct AST_node *to_ast_literal(int literal);
struct AST_node *to_ast_factor(struct CST_node *cst);

struct AST_node *to_ast(struct CST_node *cst)
{
    return to_ast_expr(cst);
}

struct AST_node *to_ast_expr(struct CST_node *cst)
{
    //printf("ast_expr: start \n");
    if ((cst->expr.expr_rest)->expr_rest.expr == NULL)
    {
        //printf("ast_expr: no expr\n");
        return to_ast_term(cst->expr.term);
    }
    //printf("ast_expr: yes expr\n");

    struct AST_node* node_expr = malloc(sizeof(struct AST_node));

    node_expr->type = NODE_ADD;
    node_expr->left = to_ast_term(cst->expr.term);
    node_expr->right = to_ast_expr((cst->expr.expr_rest)->expr_rest.expr);

    return node_expr;
}

struct AST_node *to_ast_term(struct CST_node *cst)
{
    if ((cst->term.term_rest)->term_rest.term == NULL)
    {
        return to_ast_factor(cst->term.factor);
    }

    struct AST_node* node_term = malloc(sizeof(struct AST_node));

    node_term->type = NODE_MUL;
    node_term->left = to_ast_factor(cst->term.factor);
    node_term->right = to_ast_term((cst->term.term_rest)->term_rest.term);

    return node_term;

}

struct AST_node *to_ast_literal(int literal)
{
    struct AST_node* node_literal = malloc(sizeof(struct AST_node));
    node_literal->type = NODE_LITERAL;
    node_literal->literal = literal;

    return node_literal;
}

struct AST_node *to_ast_factor(struct CST_node *cst)
{
    if (cst->factor.negated)
    {
        struct AST_node* node_factor = malloc(sizeof(struct AST_node));
        node_factor->type = NODE_NEG;
        if ((cst->factor.expr) == NULL)
        {
            node_factor->left = to_ast_literal(cst->factor.literal);
            node_factor->right = NULL;
        } else
        {
            node_factor->left = to_ast_expr(cst->factor.expr);
            node_factor->right = NULL;
        }

        return node_factor;
    } else
    {
        if (cst->factor.expr == NULL)
        {
            return to_ast_literal(cst->factor.literal);
        } else
        {
            return to_ast_expr(cst->factor.expr);
        }
    }
}


void free_ast(struct AST_node *ast)
{
    if (ast == NULL)
    {
        return;
    }

    if (ast->type == NODE_LITERAL)
    {
        free(ast);
        return;
    }

    free_ast(ast->left);
    free_ast(ast->right);

    free(ast);
}



int interpret(struct AST_node *ast)
{
    if (ast == NULL)
    {
        return 0;
    }

    if (ast->type == NODE_LITERAL)
    {
        return ast->literal;
    }

    if (ast->type == NODE_ADD)
    {
        return interpret(ast->left) + interpret(ast->right);
    }

    if (ast->type == NODE_MUL)
    {
        return interpret(ast->left) * interpret(ast->right);
    }

    if (ast->type == NODE_NEG)
    {
        return -1 * interpret(ast->left);
    }

    return 0;
}
