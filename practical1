#include<stdio.h>

int isAccepted(char *str)
{
    int i=0;

    if (str[0] == '\0') {
        return 0;
    }

    while(str[i] == 'a')
    {
        i++;
    }

    if (str[i] == 'b' && str[i + 1] == 'b' && str[i + 2] == '\0') {
        return 1;
    }

    return 0;
}

int main()
{
    char string[100];
    printf("Enter your string: ");
    scanf("%s",string);

    if(isAccepted(string))
    {
        printf("Valid String");
    }
    else
    {
        printf("Invalid String");
    }
}


