//
//  main.c
//  ExpressionEvaluation
//
//  Created by Apoorv Krishan on 31/08/26.
//

#include <stdio.h>
#include <ctype.h>

int val[50], vt = -1;
char op[50];
int ot = -1;

void calc(void)
{
    int b = val[vt--], a = val[vt--];
    char o = op[ot--];

    if (o == '+') val[++vt] = a + b;
    if (o == '-') val[++vt] = a - b;
    if (o == '*') val[++vt] = a * b;
    if (o == '/') val[++vt] = a / b;
}

int prec(char c)
{
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}

int main(int argc, char *argv[])
{
    int i;
    char c;

    for (i = 0; argv[1][i]; i++)
    {
        c = argv[1][i];

        if (isdigit(c))
            val[++vt] = c - '0';

        else if (c == '(')
            op[++ot] = c;

        else if (c == ')')
        {
            while (op[ot] != '(') calc();
            ot--;
        }

        else
        {
            while (ot >= 0 && op[ot] != '(' &&
                   prec(op[ot]) >= prec(c))
                calc();

            op[++ot] = c;
        }
    }

    while (ot >= 0)
        calc();

    printf("Result = %d\n", val[vt]);

    return 0;
}

