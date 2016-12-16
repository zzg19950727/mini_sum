#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX1    1000
#define MAX2    100

long mini_table[MAX1][MAX2];
long state_table[MAX1][MAX2];
int add_pos[MAX2];

void init_mini_table()
{
    for(int i=0; i<MAX1; i++)
        for(int j=0; j<MAX2; j++)
        mini_table[i][j] = -1;
}

long search_table(int pos, int add)
{
    return mini_table[pos][add];
}

long str2num(const char* str, int len)
{
    long num = 0;
    for(int i=0; i<len; i++)
    {
        num *= 10;
        num += str[i]-'0';
    }

    return num;
}

long mini_sum(int pos, const char* str, int add_left)
{
    long mini = 0x0fffffff;
    long num1, num2,sum;
    int len = strlen(str);
    int add_pos = 0;

    if(add_left == 0)
    {
        mini = atoi(str);
        goto quit;
    }

    for(int i=1; i<=len+1-add_left; i++)
    {
        if(i > 9)
            continue;

        num1 = str2num(str, i);

        num2 = search_table(pos+i, add_left-1);

        if(num2 < 0)//not have history
            num2 = mini_sum(pos+i, str+i, add_left-1);

        if(num2 < 0)//overflow
            continue;

        sum = num1 + num2;
        if( sum < mini )
        {
            mini = sum;
            add_pos = pos+i;
        }

    }
    mini_table[pos][add_left] = mini;
    state_table[pos][add_left] = add_pos;

quit:
    return mini;
}

void cal_result(int add)
{
    int pos=0, add_left=add;
    for(int i=0; i<add; i++)
    {
        add_pos[i] = state_table[pos][add_left];
        pos = add_pos[i];
        add_left--;
    }
}

int main(void)
{
    char*  str = "12311567567890123456789098765432123456123456756789012345678909876543212345612345675678901234567890987654321234561234567567890123456789098765432123456";
    int add = 60;

    init_mini_table();

    long mini = mini_sum(0,str, add);

    cal_result(add);

    long pos=0;

    for(int i=0; i<add; i++)
    {
        for(; pos<add_pos[i]; pos++)
            printf("%c",str[pos]);
        printf("+");
    }

    for(; pos<strlen(str); pos++)
            printf("%c",str[pos]);

    printf(" = %ld\n", mini);

    return 0;
}
