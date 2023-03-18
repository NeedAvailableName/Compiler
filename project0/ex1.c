#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
int main()
{
    char intMax[20];
    char newstr[16] = "";
    sprintf(intMax, "%d", INT_MAX);
    char str[16];
    printf("Enter a string: ");
    scanf("%s", str);
    printf("Your string: %s \n", str);
    for (int i = 0; i < strlen(str); i++)
    {
        if (isdigit(str[i]) == 0)
        {
            printf("Error: Not a number! \n");
            return 0;
        }
    }

    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] != '0')
        {
            strcat(newstr, str + i);
            break;
        }
    }
    if (strcmp(newstr, intMax) > 0)
    {
        printf("Error: Number too long! \n");
        return 0;
    }
    else
        printf("Number value: %d \n", atoi(newstr));
    return 0;
}
