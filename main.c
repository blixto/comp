#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define ERR -1
#define NARGS 3
#define A 1
#define B 2

typedef enum {
    FALSE,
    TRUE
} bool;

typedef enum {
    LT,
    LE,
    EQ,
    GE,
    GT
} relop;

typedef struct {
    relop type;
    char *sym;
} Operation;

#define foreach(c,el,L,T) for (c = 0, el = *L; c < (sizeof(L)/sizeof(T)); el = *(L + ++c))

bool comp(int, int, relop);

int
main(int argc, char **argv)
{
    if (argc != NARGS) {
        printf("%s: Fatal input error.\n", *argv);
        printf("Wrong number of arguments\nargc = %d\n", argc);
        printf("Arg. count must be exactly %d.\n", NARGS);
        return ERR;
    }
    int c;
    Operation op;
    Operation REL[] = {{LT, "<"}, {LE, "<="}, {EQ, "=="}, {GE, ">="}, {GT, ">"}};
    bool result;
    int a = atoi(*(argv+A));
    int b = atoi(*(argv+B));
    foreach(c,op,REL,Operation) {
        if (comp(c, LT, GE) && comp(c, GT, LE))
            result = comp(a, b, op.type);
        else
            break;
        if (result != ERR)
            printf("%d %s %d is %s\n", a, op.sym, b, result?"true":"false");
        else
            return ERR;
    }
    return OK;
}

bool
comp(int a, int b, relop type)
{
    switch (type) {
        case LT:
            return (a < b)?TRUE:FALSE;
        case LE:
            return (a <= b)?TRUE:FALSE;
        case EQ:
            return (a == b)?TRUE:FALSE;
        case GE:
            return (a >= b)?TRUE:FALSE;
        case GT:
            return (a > b)?TRUE:FALSE;
        default:
            return ERR;
    }
}
