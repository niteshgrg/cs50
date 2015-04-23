#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main()
{
    int len, i;
    string name;
    char initials[10];
    name = GetString();
    len=strlen(name);
    if(name[0] >= 'a' && name[0] <= 'z')
    {
        initials[0]=name[0]-'a'+'A';
    }
    else
    {
        initials[0]=name[0];
    }
    int k=1;
    for(i=0;i<len;i++)
    {
        if(name[i]==' ')
        {
            if((name[i+1]>='a') && (name[i+1] <= 'z'))
            {
                initials[k]=name[i+1]-'a'+'A';
            }
            else
            {
                initials[k]=name[i+1];
            }
            k++;
        }
    }
    for(i=0;i<k;i++)
    {
        printf("%c",initials[i]);
    }
    printf("\n");
    return 0;    
    
}
