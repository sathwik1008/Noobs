#include <stdio.h>
#include <string.h>

int main()
{
    int key;
    char Text[100];

    printf("Text: ");
    scanf("%s", &Text);
    printf("Shift: ");
    scanf("%d", &key);

    if (key > 25)
    {
        printf("Pls enter a shift less than or equal to 25.");
    }
    else
    {
        int len, i;
        len = strlen(Text);

        printf("Cipher: ");

        char t;
        for (i = 0; i < len; i++)
        {
            t = (Text[i] - 'A' + key) % 26 + 'A';
            printf("%c", t);
        }
    }

    return 0;
}
