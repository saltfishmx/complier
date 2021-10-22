
#include"semantic.h"

extern Snode *symboltable;
int equals(char *s1, char *s2)
{
    if (strcmp(s1, s2) == 0)
    {
        return 1;
    }
    else
        return 0;
}
int matchproduction(Node *root, int num, ...)
{
    va_list valist;
    va_start(valist, num);
    int res = 1;
    for (int i = 0; i < num; i++)
    {
        if (root->childlist[i] == NULL)
        {
            res = 0;
            break;
        }
        char *name = va_arg(valist, char *);
        if (!equals(name, root->childlist[i]->name))
        {
            res = 0;
            break;
        }
    }
    va_end(valist);
    if (root->childlist[num] != NULL)
    {
        res = 0;
    }
    return res;
}
Type translatespecifier(Node *root)
{
    if (matchproduction(root, 1, "Type"))
    {
        return translatetype(root->childlist[0]);
    }
    else if (matchproduction(root, 1, "StructSpecifier"))
    {
        return translateStructspecifier(root->childlist[0]);
    }
    else
    {
        printf("translate specifier error\n");
        return NULL;
    }
}
Type translatetype(Node *root)
{
    if (equals(root->val.s, "int"))
    {
        Type res = (Type)malloc(sizeof(struct Type_));
        res->kind = BASIC;
        res->u.basic = INT;
        return res;
    }
    else if (equals(root->val.s, "float"))
    {
        Type res = (Type)malloc(sizeof(struct Type_));
        res->kind = BASIC;
        res->u.basic = FLOAT;
        return res;
    }
    else
    {
        printf("translate type error\n");
    }
}
Type translateStructspecifier(Node *root)
{//比如struct Complex {…}，那么之后可以直接使用该结构体来定义变量，例如struct Complex a, b;
    if (matchproduction(root, 2, "STRUCT", "Tag"))
    {

    }
}