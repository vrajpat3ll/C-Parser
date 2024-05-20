#ifndef TREE_H
#define TREE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define node types
typedef enum NodeType{
    NODE_SWITCH_STATEMENT,
    NODE_CASE_STATEMENT,
    NODE_DEFAULT_STATEMENT,
    NODE_GOTO_STATEMENT,
    NODE_CONTINUE_STATEMENT,
    NODE_BREAK_STATEMENT,
    NODE_RETURN_STATEMENT,
    NODE_IDENTIFIER,
    NODE_CONSTANT,
    NODE_STRING_LITERAL,
    NODE_ASSIGNMENT_STATEMENT,
    NODE_TYPE_SPECIFIER,
    NODE_STATEMENT_LIST,
} NodeType;

char* NodeTypeToStr(NodeType type){
    switch (type)
    {
    case NODE_SWITCH_STATEMENT: return "switch";
    case NODE_CASE_STATEMENT: return "case";
    case NODE_DEFAULT_STATEMENT: return "deault";
    case NODE_GOTO_STATEMENT: return "goto";
    case NODE_CONTINUE_STATEMENT: return "continue";
    case NODE_BREAK_STATEMENT: return "break";
    case NODE_RETURN_STATEMENT: return "return";
    case NODE_IDENTIFIER: return "identifier";
    case NODE_CONSTANT: return "constant";
    case NODE_STRING_LITERAL: return "string literal";
    case NODE_ASSIGNMENT_STATEMENT: return "assignment statement";
    case NODE_TYPE_SPECIFIER: return "type specifier";
    case NODE_STATEMENT_LIST: return "statement list";
    
    default:
        break;
    }
}

// Define node structure
typedef struct TreeNode {
    NodeType type;
    char *value;                 // For identifier, constant, string literal, type values
    struct TreeNode *expression; // For expressions
    struct TreeNode *left;       // For left child (e.g., for switch_statement, assignment_statement)
    struct TreeNode *right;      // For right child (e.g., for assignment_statement)
} TreeNode;


TreeNode *create_switch_statement_node(TreeNode *expression, TreeNode *statement) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->type = NODE_SWITCH_STATEMENT;
    node->expression = expression;
    node->left = statement;
    node->right = NULL;
    return node;
}

TreeNode *create_case_statement_node(TreeNode *expression, TreeNode *statement) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->type = NODE_CASE_STATEMENT;
    node->expression = expression;
    node->left = statement;
    node->right = NULL;
    return node;
}

TreeNode *create_default_statement_node(TreeNode *statement) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->type = NODE_DEFAULT_STATEMENT;
    node->left = statement;
    node->right = NULL;
    return node;
}

TreeNode *create_goto_statement_node(char *identifier) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->type = NODE_GOTO_STATEMENT;
    node->value = strdup(identifier);
    node->left = node->right = node->expression = NULL;
    return node;
}

TreeNode *create_continue_statement_node() {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->type = NODE_CONTINUE_STATEMENT;
    node->left = node->right = node->expression = NULL;
    return node;
}

TreeNode *create_break_statement_node() {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->type = NODE_BREAK_STATEMENT;
    node->left = node->right = node->expression = NULL;
    return node;
}

TreeNode *create_return_statement_node(TreeNode *expression) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->type = NODE_RETURN_STATEMENT;
    node->expression = expression;
    node->left = node->right = NULL;
    return node;
}

TreeNode *create_identifier_node(char *identifier) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->type = NODE_IDENTIFIER;
    node->value = strdup(identifier);
    node->left = node->right = node->expression = NULL;
    return node;
}

TreeNode *create_constant_node(char *constant) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->type = NODE_CONSTANT;
    node->value = strdup(constant);
    node->left = node->right = node->expression = NULL;
    return node;
}

TreeNode *create_string_literal_node(char *string_literal) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->type = NODE_STRING_LITERAL;
    node->value = strdup(string_literal);
    node->left = node->right = node->expression = NULL;
    return node;
}

TreeNode *create_assignment_statement_node(TreeNode *type, char *identifier, TreeNode *expression) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->type = NODE_ASSIGNMENT_STATEMENT;
    node->left = type;
    node->right = expression;
    node->value = strdup(identifier);
    return node;
}

TreeNode *create_type_node(char *type) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->type = NODE_TYPE_SPECIFIER;
    node->value = strdup(type);
    node->left = node->right = node->expression = NULL;
    return node;
}

TreeNode *create_statement_list_node(TreeNode *statement) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->type = NODE_STATEMENT_LIST;
    node->left = statement;
    node->right = NULL;
    return node;
}

void free_tree(TreeNode *root) {
    if (root == NULL)
        return;
    free_tree(root->left);
    free_tree(root->right);
    free(root->value);
    free(root);
}

void print_tree_helper(struct TreeNode *node, int level) {
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < level; i++) {
        printf("  ");
    }

    printf("%s", NodeTypeToStr(node->type));

    if (node->value != NULL) {
        printf(": %s", node->value);
    }

    printf("\n");

    if (node->expression != NULL) {
        for (int i = 0; i < level; i++) {
            printf("  ");
        }
        printf("  Expression: \n");
        print_tree_helper(node->expression, level + 1);
    }

    if (node->left != NULL) {
        for (int i = 0; i < level; i++) {
            printf("  ");
        }
        printf("  Left: \n");
        print_tree_helper(node->left, level + 1);
    }

    if (node->right != NULL) {
        for (int i = 0; i < level; i++) {
            printf("  ");
        }
        printf("  Right: \n");
        print_tree_helper(node->right, level + 1);
    }
}

void print_tree(struct TreeNode *root) {
    if (root == NULL) {
        printf("Parse tree is empty.\n");
        return;
    }

    print_tree_helper(root, 0);
}

#endif // TREE_H