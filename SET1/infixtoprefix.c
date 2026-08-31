//
//  main.c
//  InfixToPrefix
//
//  Created by Apoorv Krishan on 24/08/26.
//

#include <stdio.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char x)
{
    stack[++top] = x;
}

char pop(void)
{
    return stack[top--];
}

char peek(void)
{
    return stack[top];
}

int precedence(char x)
{
    if (x == '/' || x == '*')
        return 2;
    if (x == '+' || x == '-')
        return 1;

    return 0;
}

void infixToPostfix(char infix[], char postfix[])
{
    int i, j = 0;
    char ch;

    for (i = 0; infix[i] != '\0'; i++)
    {
        ch = infix[i];

        // If operand, add directly to postfix
        if (isdigit(ch))
        {
            postfix[j++] = ch;
        }

        // If opening parenthesis, push it
        else if (ch == '(')
        {
            push(ch);
        }

        // If closing parenthesis
        else if (ch == ')')
        {
            while (top != -1 && peek() != '(')
            {
                postfix[j++] = pop();
            }

            pop();  // Remove '('
        }

        // If operator
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        {
            while (top != -1 &&
                   peek() != '(' &&
                   precedence(peek()) >= precedence(ch))
            {
                postfix[j++] = pop();
            }

            push(ch);
        }
    }

    // Pop remaining operators
    while (top != -1)
    {
        postfix[j++] = pop();
    }

    postfix[j] = '\0';
}

int main(void)
{
    char infix[MAX], postfix[MAX];

    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);

    return 0;
}

